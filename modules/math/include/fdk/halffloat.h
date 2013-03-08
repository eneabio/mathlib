// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_HALFFLOAT_H__
#define __FDK_HALFFLOAT_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"

FDK_NS_BEGIN

//half

union uif32
{
	uif32() :
	i(0)
	{}
	
	uif32(float f) :
	f(f)
	{}
	
	uif32(unsigned int i) :
	i(i)
	{}
	
	float f;
	unsigned int i;
};

typedef uif32 uif;

typedef short F16;

//float toFloat32(F16 value);
//F16 toFloat16(float const & value);

class half
{
public:
	// Constructors
	half();
	half(half const & s);
	
	template <typename U>
	explicit half(U const & s);
	
	// Cast
	//template <typename U>
	//operator U() const;
	operator float() const;
	
	// Unary updatable operators
	half& operator= (half const & s);
	half& operator+=(half const & s);
	half& operator-=(half const & s);
	half& operator*=(half const & s);
	half& operator/=(half const & s);
	half& operator++();
	half& operator--();
	
	//float toFloat() const{return toFloat32(data);}
	
	F16 _data() const{return data;}
	
private:
	F16 data;
};

half operator+ (half const & s1, half const & s2);

half operator- (half const & s1, half const & s2);

half operator* (half const & s1, half const & s2);

half operator/ (half const & s1, half const & s2);

// Unary constant operators
half operator- (half const & s);

half operator-- (half const & s, int);

half operator++ (half const & s, int);

bool operator==(
		half const & x,
		half const & y);

bool operator!=(
		half const & x,
		half const & y);

bool operator<(
	       half const & x,
	       half const & y);

bool operator<=(
		half const & x,
		half const & y);

bool operator>(
	       half const & x,
	       half const & y);

bool operator>=(
		half const & x,
		half const & y);

FDK_NS_END

#include "fdk/halffloat_inl.h"

#endif
