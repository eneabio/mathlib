// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt



#ifndef __FDK_VEC3H_H__
#define __FDK_VEC3H_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/mathf.h"
#include "fdk/vec3f.h"

FDK_NS_BEGIN

struct Vec3h {
	
	Vec3h(F16 _x, F16 _y,  F16 _z) : x(_x), y(_y), z(_z) {}
	
	Vec3h() {}
	
	operator const F16*() const { return (const F16*)(void*)this; }
	operator F16* () const { return (F16*)(void*)this; }
	
	F16& operator()(int index) {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 3);
		return ((F16*)this)[index];
	}
	const F16& operator()(int index) const {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 3);
		return ((F16*)this)[index];
	}
	F16 x;
	F16 y;
	F16 z;
};


FDK_FORGE_API   void   Vec3hInit           (Vec3h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec3hInitWithValues (F16 x, F16 y, F16 z, Vec3h* FDK_RESTRICT outVec);
FDK_FORGE_API   F16    Vec3hGetLenght      (const Vec3h& FDK_RESTRICT  inVec3h);
FDK_FORGE_API   void   Vec3hNormalize      (const Vec3h& FDK_RESTRICT  inVec3h, Vec3h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec3hMultScalar     (const Vec3h& FDK_RESTRICT  inVec3h, const F16 scalar, Vec3h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec3hMult           (const Vec3h& FDK_RESTRICT  l, const Vec3h& FDK_RESTRICT r, Vec3h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec3hSum            (const Vec3h& FDK_RESTRICT  l, const Vec3h& FDK_RESTRICT r, Vec3h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec3hSub            (const Vec3h& FDK_RESTRICT  l, const Vec3h& FDK_RESTRICT r, Vec3h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec3hCross          (const Vec3h& FDK_RESTRICT  l, const Vec3h& FDK_RESTRICT r, Vec3h* FDK_RESTRICT outVec);
FDK_FORGE_API   F16    Vec3hDot            (const Vec3h& FDK_RESTRICT  l, const Vec3h& FDK_RESTRICT r);
FDK_FORGE_API   void   Vec3hAbs            (const Vec3h& FDK_RESTRICT  inVec3h, Vec3h* FDK_RESTRICT outVec);

FDK_FORGE_API   void   Vec3hToVec3f        (const Vec3h& FDK_RESTRICT  inVec3h, Vec3f* FDK_RESTRICT outVec3f);
FDK_FORGE_API   void   Vec3fToVec3h        (const Vec3f& FDK_RESTRICT  inVec3f, Vec3h* FDK_RESTRICT outVec3h);

//Inplace

FDK_FORGE_API   void   Vec3hMultScalarInplace (const F16 scalar, Vec3h* outVec);
FDK_FORGE_API   void   Vec3hMultInplace       (const Vec3h& FDK_RESTRICT r, Vec3h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec3hSumInplace        (const Vec3h& FDK_RESTRICT r, Vec3h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec3hSubInplace        (const Vec3h& FDK_RESTRICT r, Vec3h* FDK_RESTRICT outVec);

FDK_NS_END

#endif
