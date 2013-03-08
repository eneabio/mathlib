// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_VEC4D_H__
#define __FDK_VEC4D_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"

FDK_NS_BEGIN

struct Vec4d {
	
	Vec4d(F64 _x,F64 _y,F64 _z,F64 _w) : x(_x),y(_y),z(_z),w(_w) {}
	
	Vec4d() {}
	
	operator const F64*() const { return (const F64*)(void*)this; }
	operator F64* () const { return (F64*)(void*)this; }
	
	F64& operator()(int index) {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 4);
		return ((F64*)this)[index];
	}
	const F64& operator()(int index) const {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 4);
		return ((F64*)this)[index];
	}
	
	F64 x;
	F64 y;
	F64 z;
	F64 w;
	
};

FDK_FORGE_API  void  Vec4dInit           (Vec4d* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4dInitWithValues (F64 x, F64 y, F64 z, F64 w, Vec4d* FDK_RESTRICT outVec);
FDK_FORGE_API  F64   Vec4dGetLenght      (const Vec4d& FDK_RESTRICT inVec4d);
FDK_FORGE_API  void  Vec4dNormalize      (const Vec4d& FDK_RESTRICT  inVec4d, Vec4d* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4dMultScalar     (const Vec4d& FDK_RESTRICT inVec4d, const F64 scalar, Vec4d* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4dMult           (const Vec4d& FDK_RESTRICT l, const Vec4d& FDK_RESTRICT r, Vec4d* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4dSum            (const Vec4d& FDK_RESTRICT l, const Vec4d& FDK_RESTRICT r, Vec4d* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4dSub            (const Vec4d& FDK_RESTRICT l, const Vec4d& FDK_RESTRICT r, Vec4d* FDK_RESTRICT outVec);
FDK_FORGE_API  F64   Vec4dDot            (const Vec4d& FDK_RESTRICT l, const Vec4d& FDK_RESTRICT r);
FDK_FORGE_API  void  Vec4dAbs            (const Vec4d& FDK_RESTRICT inVec4d, Vec4d* FDK_RESTRICT outVec);

//Inplace

FDK_FORGE_API  void  Vec4dMultScalarInplace (const F64 scalar, Vec4d* outVec);
FDK_FORGE_API  void  Vec4dMultInplace       (const Vec4d& FDK_RESTRICT r, Vec4d* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4dSumInplace        (const Vec4d& FDK_RESTRICT r, Vec4d* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4dSubInplace        (const Vec4d& FDK_RESTRICT r, Vec4d* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4dNormalizeInplace  (Vec4d* FDK_RESTRICT outVec);

FDK_NS_END

#endif
