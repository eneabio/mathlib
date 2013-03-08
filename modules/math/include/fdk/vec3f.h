// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_VEC3F_H__
#define __FDK_VEC3F_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"

FDK_NS_BEGIN

struct Vec3f {
	
	Vec3f(F32 _x,F32 _y,F32 _z) : x(_x),y(_y),z(_z) {}
	Vec3f() {}
	
	operator const F32*() const { return (const F32*)(void*)this; }
	operator F32* () const { return (F32*)(void*)this; }
	
	F32& operator()(int index) {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 3);
		return ((F32*)this)[index];
	}
	const F32& operator()(int index) const {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 3);
		return ((F32*)this)[index];
	}
	
	F32 x;
	F32 y;
	F32 z;
};

FDK_FORGE_API   void    Vec3fInit           (Vec3f* outVec);
FDK_FORGE_API   void    Vec3fInitWithValues (F32 x, F32 y, F32 z, Vec3f* outVec);
FDK_FORGE_API   F32     Vec3fGetLenght      (const Vec3f& FDK_RESTRICT  inVec3f);
FDK_FORGE_API   void    Vec3fNormalize      (const Vec3f& FDK_RESTRICT  inVec3f, Vec3f* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3fMultScalar     (const Vec3f& FDK_RESTRICT  inVec3f, const F32 scalar, Vec3f* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3fMult           (const Vec3f& FDK_RESTRICT  l, const Vec3f& FDK_RESTRICT r, Vec3f* FDK_RESTRICT outVec);
//maybe should go in the direction class
FDK_FORGE_API   void    Vec3fAddScale       (const Vec3f& FDK_RESTRICT  orgin, const Vec3f& FDK_RESTRICT  direction, const F32 scalar, Vec3f* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3fSum            (const Vec3f& FDK_RESTRICT  l, const Vec3f& FDK_RESTRICT r, Vec3f* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3fSub            (const Vec3f& FDK_RESTRICT  l, const Vec3f& FDK_RESTRICT r, Vec3f* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3fCross          (const Vec3f& FDK_RESTRICT  l, const Vec3f& FDK_RESTRICT r, Vec3f* FDK_RESTRICT outVec);
FDK_FORGE_API   F32     Vec3fDot            (const Vec3f& FDK_RESTRICT  l, const Vec3f& FDK_RESTRICT r);
FDK_FORGE_API   void    Vec3fAbs            (const Vec3f& FDK_RESTRICT  inVec3f, Vec3f* FDK_RESTRICT outVec);

//Inplace

FDK_FORGE_API   void    Vec3fMultScalarInplace (const F32 scalar, Vec3f* outVec);
FDK_FORGE_API   void    Vec3fMultInplace       (const Vec3f& FDK_RESTRICT r, Vec3f* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3fSumInplace        (const Vec3f& FDK_RESTRICT r, Vec3f* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3fSubInplace        (const Vec3f& FDK_RESTRICT r, Vec3f* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3fNormalizeInplace  (Vec3f* FDK_RESTRICT outVec);

FDK_NS_END

#endif

