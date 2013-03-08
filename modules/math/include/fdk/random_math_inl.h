// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_RANDOM_MATH_INL_H__
#define __FDK_RANDOM_MATH_INL_H__

#include "fdk/mathf.h"
#include "fdk/mathd.h"

FDK_NS_BEGIN

// ::::: FLOAT :::::

// Return a random float between 0.0 (inclusive) and 1.0 (exclusive.)
FDK_FORCE_INLINE F32 Randomf() {
	//RandIntSetSeed((U32) time(NULL));
	return (RandInt() & 32767) / 32768.0f;
}

// Return a random float between 0.0 and range, inclusive.
FDK_FORCE_INLINE F32 Randomf(const F32 range) {
	//RandIntSetSeed((U32) time(NULL));
	return (RandInt() & 32767) * range / 32767.0f;
}

// Return a random integer between 0 and range, inclusive.
FDK_FORCE_INLINE I32 Randomf(const I32 range) {
	//RandIntSetSeed((U32) time(NULL));
	return ((RandInt() & 32767) * range + 16384) / 32767;
}

// Generate random numbers in the interval [Min, Max], according a linear distribution
FDK_FORCE_INLINE F32   LinearRandf      (F32 const & min, F32 const & max) {
	FDK_ASSERT(max > min);
	F32 ret = (F32) RandInt() / (F32) (FDK_F32_RAND_MAX) * (max - min) + min;
	return ret;
}

// Generate random numbers in the interval [Min, Max], according a gaussian distribution
FDK_FORCE_INLINE F32   GaussRandf       (F32 const & mean, F32 const & deviation) {
	F32 w, x1, x2;
	do {
		x1 = LinearRandf(-1.f, 1.f);
		x2 = LinearRandf(-1.f, 1.f);
		w = x1 * x1 + x2 * x2;
	} while(w > 1.f);
	
	return x2 * deviation * deviation * Sqrtf((-2.f * Logf(w)) / w) + mean;
}

// Generate a random 2D vector which coordinates are regulary distributed on a circle of a given radius
FDK_FORCE_INLINE void CircularRandf  (F32 const & radius, Vec2f* outVec) {
	F32 a = LinearRandf(0.f , 6.283185307179586476925286766559f);
	outVec->x = Cosf(a) * radius;
	outVec->y = Sinf(a) * radius;
}

// Generate a random 3D vector which coordinates are regulary distributed on a sphere of a given radius
FDK_FORCE_INLINE void SphericalRandf (F32 const & radius, Vec3f* outVec) {
	F32 z = LinearRandf(-1.f, 1.f);
	F32 a = LinearRandf(0.f, 6.283185307179586476925286766559f);
	F32 r = Sqrtf(1.f - z * z);
	F32 x = r * Cosf(a);
	F32 y = r * Sinf(a);
	
	outVec->x = x * radius;
	outVec->y = y * radius;
	outVec->z = z * radius;
}

// ::::: DOUBLE :::::

// Return a random double between 0.0 (inclusive) and 1.0 (exclusive.)
FDK_FORCE_INLINE F64 Randomd() {
	//RandIntSetSeed((U32) time(NULL));
	return (F64) ((RandInt() & 32767) / 32768.0);
}

// Return a random double between 0.0 and range, inclusive.
FDK_FORCE_INLINE F64 Randomd(const F64 range) {
	//RandIntSetSeed((U32) time(NULL));
	return (F64) ((RandInt() & 32767) * range / 32767.0);
}

// Return a random integer between 0 and range, inclusive.
FDK_FORCE_INLINE I64 Randomd(const I64 range) {
	//RandIntSetSeed((U32) time(NULL));
	return (I64) (((RandInt() & 32767) * range + 16384) / 32767);
}

// Generate random numbers in the interval [Min, Max], according a linear distribution
FDK_FORCE_INLINE F64   LinearRandd      (F64 const & min, F64 const & max) {
	FDK_ASSERT(max > min);
	F64 ret = (F64) RandInt() / (F64) (RAND_MAX) * (max - min) + min;
	return ret;
}

// Generate random numbers in the interval [Min, Max], according a gaussian distribution
FDK_FORCE_INLINE F64   GaussRandd       (F64 const & mean, F64 const & deviation) {
	F64 w, x1, x2;
	do {
		x1 = LinearRandd(-1, 1);
		x2 = LinearRandd(-1, 1);
		w = x1 * x1 + x2 * x2;
	} while(w > 1);
	
	return x2 * deviation * deviation * Sqrtd((-2 * Logd(w)) / w) + mean;
}

// Generate a random 2D vector which coordinates are regulary distributed on a circle of a given radius
FDK_FORCE_INLINE void CircularRandd  (F64 const & radius, Vec2d* outVec) {
	F64 a = LinearRandd(0.0 , 6.283185307179586476925286766559);
	outVec->x = Cosd(a) * radius;
	outVec->y = Sind(a) * radius;
}

// Generate a random 3D vector which coordinates are regulary distributed on a sphere of a given radius
FDK_FORCE_INLINE void SphericalRandd (F64 const & radius, Vec3d* outVec) {
	F64 z = LinearRandd(-1.0, 1.0);
	F64 a = LinearRandd(0.0, 6.283185307179586476925286766559);
	F64 r = Sqrtd(1.0 - z * z);
	F64 x = r * Cosd(a);
	F64 y = r * Sind(a);
	
	outVec->x = x * radius;
	outVec->y = y * radius;
	outVec->z = z * radius;
}

FDK_NS_END

#endif
