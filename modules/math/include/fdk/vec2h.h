// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt



#ifndef __FDK_VEC2H_H__
#define __FDK_VEC2H_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/mathf.h"
#include "fdk/vec2f.h"

FDK_NS_BEGIN

struct Vec2h {
	
	Vec2h(F16 _x, F16 _y) : x(_x), y(_y) {}
	
	Vec2h() {}
	
	operator const F16*() const { return (const F16*)(void*)this; }
	operator F16* () const { return (F16*)(void*)this; }
	
	F16& operator()(int index) {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 2);
		return ((F16*)this)[index];
	}
	const F16& operator()(int index) const {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 2);
		return ((F16*)this)[index];
	}
	F16 x;
	F16 y;
};


FDK_FORGE_API   void   Vec2hInit           (Vec2h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2hInitWithValues (F16 x, F16 y, Vec2h* FDK_RESTRICT outVec);
FDK_FORGE_API   F16    Vec2hGetLenght      (const Vec2h& FDK_RESTRICT  inVec2h);
FDK_FORGE_API   void   Vec2hNormalize      (const Vec2h& FDK_RESTRICT  inVec2h, Vec2h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2hMultScalar     (const Vec2h& FDK_RESTRICT  inVec2h, const F16 scalar, Vec2h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2hMult           (const Vec2h& FDK_RESTRICT  l, const Vec2h& FDK_RESTRICT r, Vec2h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2hSum            (const Vec2h& FDK_RESTRICT  l, const Vec2h& FDK_RESTRICT r, Vec2h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2hSub            (const Vec2h& FDK_RESTRICT  l, const Vec2h& FDK_RESTRICT r, Vec2h* FDK_RESTRICT outVec);
FDK_FORGE_API   F16    Vec2hCross          (const Vec2h& FDK_RESTRICT  l, const Vec2h& FDK_RESTRICT r);
FDK_FORGE_API   F16    Vec2hDot            (const Vec2h& FDK_RESTRICT  l, const Vec2h& FDK_RESTRICT r);
FDK_FORGE_API   void   Vec2hAbs            (const Vec2h& FDK_RESTRICT  inVec2h, Vec2h* FDK_RESTRICT outVec);

FDK_FORGE_API   void   Vec2hToVec2f        (const Vec2h& FDK_RESTRICT  inVec2h, Vec2f* FDK_RESTRICT outVec2f);
FDK_FORGE_API   void   Vec2fToVec2h        (const Vec2f& FDK_RESTRICT  inVec2f, Vec2h* FDK_RESTRICT outVec2h);

//Inplace

FDK_FORGE_API   void   Vec2hMultScalarInplace (const F16 scalar, Vec2h* outVec);
FDK_FORGE_API   void   Vec2hMultInplace       (const Vec2h& FDK_RESTRICT r, Vec2h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2hSumInplace        (const Vec2h& FDK_RESTRICT r, Vec2h* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2hSubInplace        (const Vec2h& FDK_RESTRICT r, Vec2h* FDK_RESTRICT outVec);

FDK_NS_END

#endif
