// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_HALFFLOAT_INL_H__
#define __FDK_HALFFLOAT_INL_H__

FDK_NS_BEGIN

//
////}//namespace detail
//
FDK_FORCE_INLINE float overflow()
{
	volatile float f = 1e10;

	for(int i = 0; i < 10; ++i)
		f *= f;             // this will overflow before
	// the for≠loop terminates
	return f;
}


FDK_FORCE_INLINE float toFloat32(F16 value)
{
	int s = (value >> 15) & 0x00000001;
	int e = (value >> 10) & 0x0000001f;
	int m =  value        & 0x000003ff;

	if(e == 0)
	{
		if(m == 0)
		{
			//
			// Plus or minus zero
			//

			uif result;
			result.i = (unsigned int)(s << 31);
			return result.f;
		}
		else
		{
			//
			// Denormalized number -- renormalize it
			//

			while(!(m & 0x00000400))
			{
				m <<= 1;
				e -=  1;
			}

			e += 1;
			m &= ~0x00000400;
		}
	}
	else if(e == 31)
	{
		if(m == 0)
		{
			//
			// Positive or negative infinity
			//

			uif result;
			result.i = (unsigned int)((s << 31) | 0x7f800000);
			return result.f;
		}
		else
		{
			//
			// Nan -- preserve sign and significand bits
			//

			uif result;
			result.i = (unsigned int)((s << 31) | 0x7f800000 | (m << 13));
			return result.f;
		}
	}

	//
	// Normalized number
	//

	e = e + (127 - 15);
	m = m << 13;

	//
	// Assemble s, e and m.
	//

	uif Result;
	Result.i = (unsigned int)((s << 31) | (e << 23) | m);
	return Result.f;
}

FDK_FORCE_INLINE F16 toFloat16(float const & f)
{
	uif Entry;
	Entry.f = f;
	int i = (int)Entry.i;

	//
	// Our floating point number, f, is represented by the bit
	// pattern in integer i.  Disassemble that bit pattern into
	// the sign, s, the exponent, e, and the significand, m.
	// Shift s into the position where it will go in in the
	// resulting half number.
	// Adjust e, accounting for the different exponent bias
	// of float and half (127 versus 15).
	//

	register int s =  (i >> 16) & 0x00008000;
	register int e = ((i >> 23) & 0x000000ff) - (127 - 15);
	register int m =   i        & 0x007fffff;

	//
	// Now reassemble s, e and m into a half:
	//

	if(e <= 0)
	{
		if(e < -10)
		{
			//
			// E is less than -10.  The absolute value of f is
			// less than half_MIN (f may be a small normalized
			// float, a denormalized float or a zero).
			//
			// We convert f to a half zero.
			//

			return F16(s);
		}

		//
		// E is between -10 and 0.  F is a normalized float,
		// whose magnitude is less than __half_NRM_MIN.
		//
		// We convert f to a denormalized half.
		//

		m = (m | 0x00800000) >> (1 - e);

		//
		// Round to nearest, round "0.5" up.
		//
		// Rounding may cause the significand to overflow and make
		// our number normalized.  Because of the way a half's bits
		// are laid out, we don't have to treat this case separately;
		// the code below will handle it correctly.
		//

		if(m & 0x00001000)
			m += 0x00002000;

		//
		// Assemble the half from s, e (zero) and m.
		//

		return F16(s | (m >> 13));
	}
	else if(e == 0xff - (127 - 15))
	{
		if(m == 0)
		{
			//
			// F is an infinity; convert f to a half
			// infinity with the same sign as f.
			//

			return F16(s | 0x7c00);
		}
		else
		{
			//
			// F is a NAN; we produce a half NAN that preserves
			// the sign bit and the 10 leftmost bits of the
			// significand of f, with one exception: If the 10
			// leftmost bits are all zero, the NAN would turn
			// into an infinity, so we have to set at least one
			// bit in the significand.
			//

			m >>= 13;

			return F16(s | 0x7c00 | m | (m == 0));
		}
	}
	else
	{
		//
		// E is greater than zero.  F is a normalized float.
		// We try to convert f to a normalized half.
		//

		//
		// Round to nearest, round "0.5" up
		//

		if(m &  0x00001000)
		{
			m += 0x00002000;

			if(m & 0x00800000)
			{
				m =  0;     // overflow in significand,
				e += 1;     // adjust exponent
			}
		}

		//
		// Handle exponent overflow
		//

		if (e > 30)
		{
			overflow();        // Cause a hardware floating point overflow;

			return F16(s | 0x7c00);
			// if this returns, the half becomes an
		}   // infinity with the same sign as f.

		//
		// Assemble the half from s, e and m.
		//

		return F16(s | (e << 10) | (m >> 13));
	}
}

FDK_FORCE_INLINE half::half() :
data(0)
{}

FDK_FORCE_INLINE half::half(half const & s) :
data(s.data)
{}

template <typename U>
FDK_FORCE_INLINE half::half(U const & s) :
data(toFloat16(float(s)))
{}
///*
// template <typename U>
// half::operator U() const
// {
// return static_cast<U>(toFloat32(this->data));
// }
// */

FDK_FORCE_INLINE half::operator float() const
{
	return toFloat32(this->data);
}

//// Unary updatable operators
FDK_FORCE_INLINE half& half::operator= (half const & s)
{
	data = s.data;
	return *this;
}

FDK_FORCE_INLINE half& half::operator+=(half const & s)
{
	data = toFloat16(toFloat32(data) + toFloat32(s.data));
	return *this;
}

FDK_FORCE_INLINE half& half::operator-=(half const & s)
{
	data = toFloat16(toFloat32(data) - toFloat32(s.data));
	return *this;
}

FDK_FORCE_INLINE half& half::operator*=(half const & s)
{
	data = toFloat16(toFloat32(data) * toFloat32(s.data));
	return *this;
}

FDK_FORCE_INLINE half& half::operator/=(half const & s)
{
	data = toFloat16(toFloat32(data) / toFloat32(s.data));
	return *this;
}

FDK_FORCE_INLINE half& half::operator++()
{
	float Casted = toFloat32(data);
	this->data = toFloat16(++Casted);
	return *this;
}

FDK_FORCE_INLINE half& half::operator--()
{
	float Casted = toFloat32(data);
	this->data = toFloat16(--Casted);
	return *this;
}

////////////////////////////////////////
//// Binary arithmetic operators
//
FDK_FORCE_INLINE half operator+ (half const & s1, half const & s2)
{
	return half(float(s1) + float(s2));
}

FDK_FORCE_INLINE half operator- (half const & s1, half const & s2)
{
	return half(float(s1) - float(s2));
}

FDK_FORCE_INLINE half operator* (half const & s1, half const & s2)
{
	return half(float(s1) * float(s2));
}

FDK_FORCE_INLINE half operator/ (half const & s1, half const & s2)
{
	return half(float(s1) / float(s2));
}

// Unary constant operators
FDK_FORCE_INLINE half operator- (half const & s)
{
	return half(-float(s));
}

FDK_FORCE_INLINE half operator-- (half const & s, int)
{
	return half(float(s) - 1.0f);
}

FDK_FORCE_INLINE half operator++ (half const & s, int)
{
	return half(float(s) + 1.0f);
}

FDK_FORCE_INLINE bool operator==(half const & x, half const & y)
{
	return x._data() == y._data();
}

FDK_FORCE_INLINE bool operator!=(half const & x, half const & y)
{
	return x._data() != y._data();
}

FDK_FORCE_INLINE bool operator<(half const & x, half const & y)
{
	return float(x) < float(y);
}

FDK_FORCE_INLINE bool operator<=(half const & x, half const & y)
{
	return float(x) <= float(y);
}

FDK_FORCE_INLINE bool operator>(half const & x, half const & y)
{
	return float(x) > float(y);
}

FDK_FORCE_INLINE bool operator>=(half const & x, half const & y)
{
	return float(x) >= float(y);
}

FDK_NS_END

#endif