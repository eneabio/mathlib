// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_VEC2F_H__
#define __FDK_VEC2F_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"

FDK_NS_BEGIN

struct Vec2f {
	
	Vec2f(F32 _x, F32 _y) : x(_x), y(_y) {}
	
	Vec2f() {}
	
	operator const F32*() const { return (const F32*)(void*)this; }
	operator F32* () const { return (F32*)(void*)this; }
	
	F32& operator()(int index) {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 2);
		return ((F32*)this)[index];
	}
	const F32& operator()(int index) const {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 2);
		return ((F32*)this)[index];
	}
	F32 x;
	F32 y;
};


FDK_FORGE_API   void   Vec2fInit           (Vec2f* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2fInitWithValues (F32 x, F32 y, Vec2f* FDK_RESTRICT outVec);
FDK_FORGE_API   F32    Vec2fGetLenght      (const Vec2f& FDK_RESTRICT  inVec2f);
FDK_FORGE_API   void   Vec2fNormalize      (const Vec2f& FDK_RESTRICT  inVec2f, Vec2f* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2fMultScalar     (const Vec2f& FDK_RESTRICT  inVec2f, const F32 scalar, Vec2f* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2fMult           (const Vec2f& FDK_RESTRICT  l, const Vec2f& FDK_RESTRICT r, Vec2f* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2fSum            (const Vec2f& FDK_RESTRICT  l, const Vec2f& FDK_RESTRICT r, Vec2f* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2fSub            (const Vec2f& FDK_RESTRICT  l, const Vec2f& FDK_RESTRICT r, Vec2f* FDK_RESTRICT outVec);
FDK_FORGE_API   F32    Vec2fCross          (const Vec2f& FDK_RESTRICT  l, const Vec2f& FDK_RESTRICT r);
FDK_FORGE_API   F32    Vec2fDot            (const Vec2f& FDK_RESTRICT  l, const Vec2f& FDK_RESTRICT r);
FDK_FORGE_API   void   Vec2fAbs            (const Vec2f& FDK_RESTRICT  inVec2f, Vec2f* FDK_RESTRICT outVec);

//Inplace

FDK_FORGE_API   void   Vec2fMultScalarInplace (const F32 scalar, Vec2f* outVec);
FDK_FORGE_API   void   Vec2fMultInplace       (const Vec2f& FDK_RESTRICT r, Vec2f* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2fSumInplace        (const Vec2f& FDK_RESTRICT r, Vec2f* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2fSubInplace        (const Vec2f& FDK_RESTRICT r, Vec2f* FDK_RESTRICT outVec);

FDK_NS_END

#endif
