// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/quatf.h"
#include "fdk/mathf.h"
#include "fdk/vec3f.h"


FDK_NS_BEGIN

void QuatfInit(Quatf* outQuat) {
	outQuat->qX = 0.f;
	outQuat->qY = 0.f;
	outQuat->qZ = 0.f;
	outQuat->qW = 0.f;
}

void QuatfInitWithValues(F32 x, F32 y, F32 z, F32 w, Quatf* outQuat) {
	outQuat->qX = x;
	outQuat->qY = y;
	outQuat->qZ = z;
	outQuat->qW = w;
	
	F32 length = QuatfModulus(*outQuat);
	
	//to do with toll
	bool res = FdkEqf32(length, 1.f, FDK_F32_TOLL);
	FDK_ASSERT(res);
	
}

void   QuatfIdentity(Quatf* outQuat){
	outQuat->qX = 0.f;
	outQuat->qY = 0.f;
	outQuat->qZ = 0.f;
	outQuat->qW = 1.f;
}

void   QuatfInitWithEulerAngles(F32 yaw, F32 roll, F32 pitch, Quatf* outQuat) {
	//Set the quaternion using euler angles (YZX)
	F32 halfYaw   = yaw*0.5f;
	F32 halfPitch = pitch*0.5f;
	F32 halfRoll  = roll*0.5f;

	F32 c1 = Cosf(halfYaw);
	F32 c2 = Cosf(halfRoll);
	F32 c3 = Cosf(halfPitch);
	F32 s1 = Sinf(halfYaw);
	F32 s2 = Sinf(halfRoll);
	F32 s3 = Sinf(halfPitch);
	
	//set quaternion
	outQuat->qW = c1 * c2 * c3 - s1 * s2 * s3;
	outQuat->qX = s1 * s2 * c3 + c1 * c2 * s3;
	outQuat->qY = s1 * c2 * c3 + c1 * s2 * s3;
	outQuat->qZ = c1 * s2 * c3 - s1 * c2 * s3;

	QuatfNormalize(*outQuat, outQuat);
}

F32 QuatfModulus (const Quatf& inQuatf) {
	#if defined (FDK_USE_SIMD)
	#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
		return Sqrtf(QuatfDot(inQuatf, inQuatf));
	#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
		//to do
	#endif
	#else
		F32 inQuatfxQ = inQuatf.qX * inQuatf.qX;
		F32 inQuatfyQ = inQuatf.qY * inQuatf.qY;
		F32 inQuatfzQ = inQuatf.qZ * inQuatf.qZ;
		F32 inQuatfwQ = inQuatf.qW * inQuatf.qW;
		return Sqrtf(inQuatfxQ + inQuatfyQ + inQuatfzQ + inQuatfwQ);
	#endif
}


F32    QuatfSquaredModulus      (const Quatf& FDK_RESTRICT inQuatf) {
	#if defined (FDK_USE_SIMD)
	#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
		return QuatfDot(inQuatf, inQuatf);
	#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
		//to do
	#endif
	#else
		F32 inQuatfxQ = inQuatf.qX * inQuatf.qX;
		F32 inQuatfyQ = inQuatf.qY * inQuatf.qY;
		F32 inQuatfzQ = inQuatf.qZ * inQuatf.qZ;
		F32 inQuatfwQ = inQuatf.qW * inQuatf.qW;
		return (inQuatfxQ + inQuatfyQ + inQuatfzQ + inQuatfwQ);
	#endif
}

void   QuatfNormalize(const Quatf&  inQuatf, Quatf* outQuatf) {	
	F32 length2 = QuatfSquaredModulus(inQuatf);
	
	//lenght different from zero...
	if (Fabsf(length2) > FDK_F32_TOLL && Fabsf(length2 - 1.0f) > FDK_F32_TOLL) {
	//if (FdkEqf32(length2, 0.f, FDK_F32_TOLL)) {
		F32 length = Sqrtf(length2);
		#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
				__m128	vs = _mm_load_ss(&length);	//	(S 0 0 0)
				vs = _mm_shuffle_ps(vs, vs, 0x00);	//	(S S S S)
				outQuatf->mVec128 = _mm_div_ps(inQuatf.mVec128, vs);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
				//to do
		#endif
		#else
			outQuatf->qX = inQuatf.qX / length;
			outQuatf->qY = inQuatf.qY / length;
			outQuatf->qZ = inQuatf.qZ / length;
			outQuatf->qW = inQuatf.qW / length;
		#endif
		return;
	}
	
	outQuatf->qX = inQuatf.qX;
	outQuatf->qY = inQuatf.qY;
	outQuatf->qZ = inQuatf.qZ;
	outQuatf->qW = inQuatf.qW;
 }

void  QuatfConjugate(const Quatf&  inQuatf, Quatf* outQuatf) {
	#if defined (FDK_USE_SIMD)
	#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
		Quatf vQInv = Quatf(-0.0f, -0.0f, -0.0f, +0.0f);
		outQuatf->mVec128 = _mm_xor_ps(inQuatf.mVec128, vQInv.mVec128);
	#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
		//to do
	#endif
	#else
		outQuatf->qX = - inQuatf.qX;
		outQuatf->qY = - inQuatf.qY;
		outQuatf->qZ = - inQuatf.qZ;
		outQuatf->qW =  inQuatf.qW;
	#endif
}

void   QuatfInverse(const Quatf&  inQuatf, Quatf* outQuatf) {
	F32   mod  = QuatfModulus(inQuatf);
	Quatf temp;
	QuatfConjugate(inQuatf, &temp);
	//mod different from zero...
	if( mod != 0) {
		#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			__m128	den = _mm_load_ss(&mod);		//	(S 0 0 0)
			den = _mm_shuffle_ps(den, den, 0x00);	//	(S S S S)
			outQuatf->mVec128 = _mm_div_ps(temp.mVec128, _mm_mul_ps(den, den));
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
		#endif
		#else
			outQuatf->qX =  temp.qX / (mod * mod);
			outQuatf->qY =  temp.qY / (mod * mod);
			outQuatf->qZ =  temp.qZ / (mod * mod);
			outQuatf->qW =  temp.qW / (mod * mod);
		#endif
	}
}

F32     QuatfDot(const Quatf& l, const Quatf& r) {
	#if defined (FDK_USE_SIMD)
	#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
	#if defined (__SSE4_1__)
		__m128 result = _mm_dp_ps(l.mVec128, r.mVec128, 0xf3);
		return (F32) result[0];
	#elif defined (_M_IX86_FP )
		__m128 result = _mm_dp_ps(l.mVec128, r.mVec128, 0xf3);
		//return (F32) result[0];
		return _mm_cvtss_f32(result);
	#else
		__m128 m = _mm_mul_ps(l.mVec128, r.mVec128);
		__m128 t = _mm_add_ps(m, _mm_shuffle_ps(m, m, _MM_SHUFFLE(2, 3, 0, 1)));
		__m128 result = _mm_add_ps(t, _mm_shuffle_ps(t, t, _MM_SHUFFLE(1, 0, 3, 2)));
		return _mm_cvtss_f32(result);
	#endif
		
	#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
		//to do
		//float32x4_t vd = vmulq_f32(mVec128, v.mVec128);
		//float32x2_t x = vpadd_f32(vget_low_f32(vd), vget_low_f32(vd));
		//x = vadd_f32(x, vget_high_f32(vd));
		//return vget_lane_f32(x, 0);
	#endif
	#else
		F32 qXMul = l.qX * r.qX;
		F32 qYMul = l.qY * r.qY;
		F32 qZMul = l.qZ * r.qZ;
		F32 qWMul = l.qW * r.qW;
		F32 res = qXMul + qYMul + qZMul + qWMul;
		return res;
	#endif
}

void    QuatfMultScalar(const Quatf& inQuat, const F32 scalar, Quatf* outQuat) {
	#if defined (FDK_USE_SIMD)
	#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
		__m128	vs = _mm_load_ss(&scalar);	//	(S 0 0 0)
		vs = _mm_shuffle_ps(vs, vs, 0x00);	//	(S S S S)
		outQuat->mVec128 = _mm_mul_ps(inQuat.mVec128, vs);
	#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
		//to do
		//__m128 in  = (__m128) inVec4f[0];
		//__m128 out = vmulq_n_f32(mVec128, s);
	#endif
	#else
		outQuat->qX = scalar * inQuat.qX;
		outQuat->qY = scalar * inQuat.qY;
		outQuat->qZ = scalar * inQuat.qZ;
		outQuat->qW = scalar * inQuat.qW;
	#endif
}


void    QuatfMult(const Quatf& l, const Quatf& r, Quatf* outQuad) {
	outQuad->qX = l.qW * r.qX + l.qX * r.qW + l.qY * r.qZ - l.qZ * r.qY;
	outQuad->qY = l.qW * r.qY - l.qX * r.qZ + l.qY * r.qW + l.qZ * r.qX;
	outQuad->qZ = l.qW * r.qZ + l.qX * r.qY - l.qY * r.qX + l.qZ * r.qW;
	outQuad->qW = l.qW * r.qW - l.qX * r.qX - l.qY * r.qY - l.qZ * r.qZ;
}

void    QuatfSum(const Quatf& l, const Quatf& r, Quatf* outQuad) {
	#if defined (FDK_USE_SIMD)
	#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
		outQuad->mVec128 = _mm_add_ps(l.mVec128, r.mVec128);
	#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
		//to do
		outQuad->mVec128 = vaddq_f32(l.mVec128, r.mVec128);
	#endif
	#else
		outQuad->qX = r.qX + l.qX;
		outQuad->qY = r.qY + l.qY;
		outQuad->qZ = r.qZ + l.qZ;
		outQuad->qW = r.qW + l.qW;
	#endif
}

void    QuatfSub(const Quatf& l, const Quatf& r, Quatf* outQuad) {
	#if defined (FDK_USE_SIMD)
	#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
		outQuad->mVec128 = _mm_sub_ps(l.mVec128, r.mVec128);
	#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
		//to do
	#endif
	#else
		outQuad->qX = l.qX - r.qX;
		outQuad->qY = l.qY - r.qY;
		outQuad->qZ = l.qZ - r.qZ;
		outQuad->qW = l.qW - r.qW;
	#endif
}

void    QuatfAbs(const Quatf&  inQuatf, Quatf* outQuad) {
	#if defined (FDK_USE_SIMD)
	#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
		__m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF));
		outQuad->mVec128 = _mm_and_ps(inQuatf.mVec128,mask);
	#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
		//to do
	#endif
	#else
		outQuad->qX = Absf(inQuatf.qX);
		outQuad->qY = Absf(inQuatf.qY);
		outQuad->qZ = Absf(inQuatf.qZ);
		outQuad->qW = Absf(inQuatf.qW);
	#endif
}

void    QuatfLerp(const Quatf&  l, const Quatf& r, F32 t,  Quatf* outQuat) {
	//Linear interpolation 
	//q(t)=(1−t) * q1 + t * q2
	Quatf first;
	Quatf second;
	QuatfMultScalar(l, (1.f-t), outQuat);
	first = *outQuat;
	QuatfMultScalar(r, t, outQuat);
	second = *outQuat;
	QuatfSum(first, second , outQuat);
	
}

void   QuatfFromAxisAngle(const Vec3f& FDK_RESTRICT  inAxis,F32 angle,Quatf* FDK_RESTRICT outQuatf){
	Vec3f inAxisNorm;
	F32   halfAngle     = angle*0.5f;
	F32   sinHalfAngle  = Sinf(halfAngle);	
	Vec3fNormalize(inAxis,&inAxisNorm); //normalize the axis (since we don't know if it's normalized)	
	outQuatf->qX      = inAxisNorm.x * sinHalfAngle;
	outQuatf->qY      = inAxisNorm.y * sinHalfAngle;
	outQuatf->qZ      = inAxisNorm.z * sinHalfAngle;
	outQuatf->qW      = Cosf(halfAngle);
}

void   QuatfGetAxis             (const Quatf& FDK_RESTRICT inQuatf, Vec3f* FDK_RESTRICT outAxis) {
	F32 scale = Sinf(ArcCosf(inQuatf.qW));
	
	if ( scale < FDK_F32_TOLL && scale > -FDK_F32_TOLL ) {
		outAxis->x = 0.f;
		outAxis->y = 0.f;
		outAxis->z = 0.f;
	} else {
		outAxis->x = inQuatf.qX / scale;
		outAxis->y = inQuatf.qY / scale;
		outAxis->z = inQuatf.qZ / scale;
	}
}

void   QuatfGetAngle            (const Quatf& FDK_RESTRICT inQuatf, F32* outAngle) {
	*outAngle = 2.0f * ArcCosf(inQuatf.qW);
}


void   QuatfToAxisAngle         (const Quatf& FDK_RESTRICT inQuatf, F32* outAngle, Vec3f* outAxis) {
	QuatfGetAngle(inQuatf, outAngle);
	QuatfGetAxis(inQuatf, outAxis);
}

void   QuatfSlerp(const Quatf&  l, const Quatf& r, F32 t,  Quatf* outQuat) {
	Quatf start = Quatf(0.0f, 0.0f, 0.0f, 0.0f);
        F32 recipSinAngle, scale0, scale1, cosAngle, angle;
        cosAngle = QuatfDot(l, r);	//is it to normalize?
        if ( cosAngle < 0.0f ) {
		cosAngle = -cosAngle;
		QuatfSubInplace(l, &start);
        } else {
		start = l;
        }
        if ( cosAngle < 0.999f ) {
		angle = ArcCosf(cosAngle);
		recipSinAngle = ( 1.0f / Sinf(angle));
		scale0 = ( Sinf( ( ( 1.0f - t ) * angle ) ) * recipSinAngle );
		scale1 = ( Sinf( ( t * angle ) ) * recipSinAngle );
        } else {
		scale0 = ( 1.0f - t );
		scale1 = t;
        }
	QuatfMultScalar(start, scale0, outQuat);
        Quatf first = *outQuat;
	QuatfMultScalar(r, scale1, outQuat);
	Quatf second = *outQuat;
	QuatfSum(first, second, outQuat);

}

void QuatfSumInplace(const Quatf& r, Quatf* outQuad) {
	#if defined (FDK_USE_SIMD)
	#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
		outQuad->mVec128 = _mm_add_ps(outQuad->mVec128, r.mVec128);
	#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
		//to do
		//vaddq_f32(v1.mVec128, v2.mVec128);
	#endif
	#else
		outQuad->qX = outQuad->qX + r.qX;
		outQuad->qY = outQuad->qY + r.qY;
		outQuad->qZ = outQuad->qZ + r.qZ;
		outQuad->qW = outQuad->qW + r.qW;
	#endif
}

void    QuatfSubInplace(const Quatf& r, Quatf* outQuad) {
	#if defined (FDK_USE_SIMD)
	#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
		outQuad->mVec128 = _mm_sub_ps(outQuad->mVec128, r.mVec128);
	#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
		//to do
		//vaddq_f32(v1.mVec128, v2.mVec128);
	#endif
	#else
		outQuad->qX = outQuad->qX - r.qX;
		outQuad->qY = outQuad->qY - r.qY;
		outQuad->qZ = outQuad->qZ - r.qZ;
		outQuad->qW = outQuad->qW - r.qW;
	#endif
}

FDK_NS_END
