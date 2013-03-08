// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_VEC2D_H__
#define __FDK_VEC2D_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"

FDK_NS_BEGIN

struct Vec2d {
	
	Vec2d(F64 _x, F64 _y) : x(_x), y(_y) {}
	
	Vec2d() {}
	
	operator const F64*() const { return (const F64*)(void*)this; }
	operator F64* () const { return (F64*)(void*)this; }
	
	F64& operator()(int index) {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 2);
		return ((F64*)this)[index];
	}
	const F64& operator()(int index) const {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 2);
		return ((F64*)this)[index];
	}
	F64 x;
	F64 y;
};


FDK_FORGE_API   void   Vec2dInit           (Vec2d* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2dInitWithValues (F64 x, F64 y, Vec2d* FDK_RESTRICT outVec);
FDK_FORGE_API   F64    Vec2dGetLenght      (const Vec2d& FDK_RESTRICT  inVec2d);
FDK_FORGE_API   void   Vec2dNormalize      (const Vec2d& FDK_RESTRICT  inVec2d, Vec2d* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2dMultScalar     (const Vec2d& FDK_RESTRICT  inVec2d, const F64 scalar, Vec2d* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2dMult           (const Vec2d& FDK_RESTRICT  l, const Vec2d& FDK_RESTRICT r, Vec2d* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2dSum            (const Vec2d& FDK_RESTRICT  l, const Vec2d& FDK_RESTRICT r, Vec2d* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2dSub            (const Vec2d& FDK_RESTRICT  l, const Vec2d& FDK_RESTRICT r, Vec2d* FDK_RESTRICT outVec);
FDK_FORGE_API   F64    Vec2dCross          (const Vec2d& FDK_RESTRICT  l, const Vec2d& FDK_RESTRICT r);
FDK_FORGE_API   F64    Vec2dDot            (const Vec2d& FDK_RESTRICT  l, const Vec2d& FDK_RESTRICT r);
FDK_FORGE_API   void   Vec2dAbs            (const Vec2d& FDK_RESTRICT  inVec2d, Vec2d* FDK_RESTRICT outVec);

//Inplace

FDK_FORGE_API   void   Vec2dMultScalarInplace (const F64 scalar, Vec2d* outVec);
FDK_FORGE_API   void   Vec2dMultInplace       (const Vec2d& FDK_RESTRICT r, Vec2d* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2dSumInplace        (const Vec2d& FDK_RESTRICT r, Vec2d* FDK_RESTRICT outVec);
FDK_FORGE_API   void   Vec2dSubInplace        (const Vec2d& FDK_RESTRICT r, Vec2d* FDK_RESTRICT outVec);

FDK_NS_END

#endif