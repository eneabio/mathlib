// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_VEC4H_H__
#define __FDK_VEC4H_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/mathf.h"
#include "fdk/vec4f.h"


FDK_NS_BEGIN

struct Vec4h {
	
	Vec4h(F16 _x,F16 _y,F16 _z,F16 _w) : x(_x),y(_y),z(_z),w(_w) {}
	
	Vec4h() {}
	
	operator const F16*() const { return (const F16*)(void*)this; }
	operator F16* () const { return (F16*)(void*)this; }
	
	F16& operator()(int index) {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 4);
		return ((F16*)this)[index];
	}
	const F16& operator()(int index) const {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 4);
		return ((F16*)this)[index];
	}
	
	F16 x;
	F16 y;
	F16 z;
	F16 w;
	
};

FDK_FORGE_API  void  Vec4hInit           (Vec4h* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4hInitWithValues (F16 x, F16 y, F16 z, F16 w, Vec4h* FDK_RESTRICT outVec);
FDK_FORGE_API  F16   Vec4hGetLenght      (const Vec4h& FDK_RESTRICT inVec4h);
FDK_FORGE_API  void  Vec4hNormalize      (const Vec4h& FDK_RESTRICT  inVec4h, Vec4h* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4hMultScalar     (const Vec4h& FDK_RESTRICT inVec4h, const F16 scalar, Vec4h* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4hMult           (const Vec4h& FDK_RESTRICT l, const Vec4h& FDK_RESTRICT r, Vec4h* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4hSum            (const Vec4h& FDK_RESTRICT l, const Vec4h& FDK_RESTRICT r, Vec4h* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4hSub            (const Vec4h& FDK_RESTRICT l, const Vec4h& FDK_RESTRICT r, Vec4h* FDK_RESTRICT outVec);
FDK_FORGE_API  F16   Vec4hDot            (const Vec4h& FDK_RESTRICT l, const Vec4h& FDK_RESTRICT r);
FDK_FORGE_API  void  Vec4hAbs            (const Vec4h& FDK_RESTRICT inVec4h, Vec4h* FDK_RESTRICT outVec);

FDK_FORGE_API   void   Vec4hToVec4f        (const Vec4h& FDK_RESTRICT  inVec4h, Vec4f* FDK_RESTRICT outVec4f);
FDK_FORGE_API   void   Vec4fToVec4h        (const Vec4f& FDK_RESTRICT  inVec4f, Vec4h* FDK_RESTRICT outVec4h);

//Inplace

FDK_FORGE_API  void  Vec4hMultScalarInplace (const F16 scalar, Vec4h* outVec);
FDK_FORGE_API  void  Vec4hMultInplace       (const Vec4h& FDK_RESTRICT r, Vec4h* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4hSumInplace        (const Vec4h& FDK_RESTRICT r, Vec4h* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4hSubInplace        (const Vec4h& FDK_RESTRICT r, Vec4h* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4hNormalizeInplace  (Vec4h* FDK_RESTRICT outVec);

FDK_NS_END

#endif

