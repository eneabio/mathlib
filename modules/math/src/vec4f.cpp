// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/vec4f.h"
#include "fdk/mathf.h"

FDK_NS_BEGIN

void Vec4fInit(Vec4f* outVec) {
	outVec->x = 0.f;
	outVec->y = 0.f;
	outVec->z = 0.f;
	outVec->w = 0.f;
}

void Vec4fInitWithValues(F32 x, F32 y, F32 z, F32 w, Vec4f* outVec) {
	outVec->x = x;
	outVec->y = y;
	outVec->z = z;
	outVec->w = w;
}

F32 Vec4fGetLenght(const Vec4f& FDK_RESTRICT inVec4f) {
	return Sqrtf(Vec4fDot(inVec4f, inVec4f));
}

void  Vec4fNormalize(const Vec4f&  inVec4f, Vec4f* outVec) {
	F32 lenght = Vec4fGetLenght(inVec4f);
	if (lenght != 0) {
		#if defined (FDK_USE_SIMD)
			#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
				__m128	vs = _mm_load_ss(&lenght);	//	(S 0 0 0)
				vs = _mm_shuffle_ps(vs, vs, 0x00);	//	(S S S S)
				outVec->mVec128 = _mm_div_ps(inVec4f.mVec128, vs);
			#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
				//to do
			#endif
		#else
			outVec->x = inVec4f.x / lenght;
			outVec->y = inVec4f.y / lenght;
			outVec->z = inVec4f.z / lenght;
			outVec->w = inVec4f.w / lenght;
		#endif
	}
}

void Vec4fMultScalar(const Vec4f& FDK_RESTRICT  inVec4f, const F32 scalar, Vec4f* outVec){
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			__m128	vs = _mm_load_ss(&scalar);	//	(S 0 0 0)
			vs = _mm_shuffle_ps(vs, vs, 0x00);	//	(S S S S)
			outVec->mVec128 = _mm_mul_ps(inVec4f.mVec128, vs);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//__m128 in  = (__m128) inVec4f[0];
			//__m128 out = vmulq_n_f32(mVec128, s);
		#endif
	#else
		outVec->x = scalar * inVec4f.x;
		outVec->y = scalar * inVec4f.y;
		outVec->z = scalar * inVec4f.z;
		outVec->w = scalar * inVec4f.w;
	#endif
	
}


void Vec4fMult(const Vec4f& FDK_RESTRICT l, const Vec4f& FDK_RESTRICT r, Vec4f* FDK_RESTRICT outVec) {
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			outVec->mVec128 = _mm_mul_ps(l.mVec128, r.mVec128);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//mVec128 = vmulq_n_f32(mVec128, s);
		#endif
	#else
		outVec->x = r.x * l.x;
		outVec->y = r.y * l.y;
		outVec->z = r.z * l.z;
		outVec->w = r.w * l.w;
	#endif
}


void Vec4fSum(const Vec4f& FDK_RESTRICT l, const Vec4f& FDK_RESTRICT r, Vec4f* FDK_RESTRICT outVec) {
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			outVec->mVec128 = _mm_add_ps(l.mVec128, r.mVec128);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//outVec->mVec128 = vaddq_f32(l.mVec128, r.mVec128);
		#endif
	#else
		outVec->x = r.x + l.x;
		outVec->y = r.y + l.y;
		outVec->z = r.z + l.z;
		outVec->w = r.w + l.w;
	#endif
}

void Vec4fSub(const Vec4f& FDK_RESTRICT l, const Vec4f& FDK_RESTRICT r, Vec4f* FDK_RESTRICT outVec) {
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			outVec->mVec128 = _mm_sub_ps(l.mVec128, r.mVec128);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
		#endif
	#else
		outVec->x = l.x - r.x;
		outVec->y = l.y - r.y;
		outVec->z = l.z - r.z;
		outVec->w = l.w - r.w;
	#endif
}

F32 Vec4fDot(const Vec4f& FDK_RESTRICT l, const Vec4f& FDK_RESTRICT r) {
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
		F32 xMul = l.x * r.x;
		F32 yMul = l.y * r.y;
		F32 zMul = l.z * r.z;
		F32 wMul = l.w * r.w;
		F32 res = xMul + yMul + zMul + wMul;
		return res;
	#endif
}

void Vec4fAbs(const Vec4f& FDK_RESTRICT  inVec4f, Vec4f* FDK_RESTRICT outVec) {
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			__m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF));
			outVec->mVec128 = _mm_and_ps(inVec4f.mVec128,mask);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
		#endif
	#else
		outVec->x = Absf(inVec4f.x);
		outVec->y = Absf(inVec4f.y);
		outVec->z = Absf(inVec4f.z);
		outVec->w = Absf(inVec4f.w);
	#endif
}

void Vec4fMultScalarInplace(const F32 scalar, Vec4f* outVec) {
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			__m128	vs = _mm_load_ss(&scalar);	//	(S 0 0 0)
			vs = _mm_shuffle_ps(vs, vs, 0x00);	//	(S S S S)
			outVec->mVec128 = _mm_mul_ps(outVec->mVec128, vs);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//__m128 in  = (__m128) inVec4f[0];
			//__m128 out = vmulq_n_f32(mVec128, s);
		#endif
	#else
		outVec->x = scalar * outVec->x;
		outVec->y = scalar * outVec->y;
		outVec->z = scalar * outVec->z;
		outVec->w = scalar * outVec->w;
	#endif
	
}


void Vec4fMultInplace(const Vec4f& FDK_RESTRICT r, Vec4f* FDK_RESTRICT outVec) {
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			outVec->mVec128 = _mm_mul_ps(outVec->mVec128, r.mVec128);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//mVec128 = vmulq_n_f32(mVec128, s);
		#endif
	#else
		outVec->x = outVec->x * r.x;
		outVec->y = outVec->y * r.y;
		outVec->z = outVec->z * r.z;
		outVec->w = outVec->w * r.w;
	#endif
}

void Vec4fSumInplace(const Vec4f& FDK_RESTRICT r, Vec4f* FDK_RESTRICT outVec) {
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			outVec->mVec128 = _mm_add_ps(outVec->mVec128, r.mVec128);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//vaddq_f32(v1.mVec128, v2.mVec128);
		#endif
	#else
		outVec->x = outVec->x + r.x;
		outVec->y = outVec->y + r.y;
		outVec->z = outVec->z + r.z;
		outVec->w = outVec->w + r.w;
	#endif

}

void Vec4fSubInplace(const Vec4f& FDK_RESTRICT r, Vec4f* FDK_RESTRICT outVec) {
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			outVec->mVec128 = _mm_sub_ps(outVec->mVec128, r.mVec128);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//vaddq_f32(v1.mVec128, v2.mVec128);
		#endif
	#else
		outVec->x = outVec->x - r.x;
		outVec->y = outVec->y - r.y;
		outVec->z = outVec->z - r.z;
		outVec->w = outVec->w - r.w;
	#endif
}

void  Vec4fNormalizeInplace(Vec4f* outVec) {
	F32 lenght = Vec4fGetLenght(*outVec);
	if (lenght != 0) {
		#if defined (FDK_USE_SIMD)
			#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
				__m128	vs = _mm_load_ss(&lenght);	//	(S 0 0 0)
				vs = _mm_shuffle_ps(vs, vs, 0x00);	//	(S S S S)
				outVec->mVec128 = _mm_div_ps(outVec->mVec128, vs);
			#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
				//to do	
			#endif
		#else
				outVec->x = outVec->x / lenght;
				outVec->y = outVec->y / lenght;
				outVec->z = outVec->z / lenght;
				outVec->w = outVec->w / lenght;
		#endif
	}

}

FDK_NS_END