// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_VEC3D_H__
#define __FDK_VEC3D_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"

FDK_NS_BEGIN

struct Vec3d {
	
	Vec3d(F64 _x,F64 _y,F64 _z) : x(_x),y(_y),z(_z) {}
	Vec3d() {}
	
	operator const F64*() const { return (const F64*)(void*)this; }
	operator F64* () const { return (F64*)(void*)this; }
	
	F64& operator()(int index) {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 3);
		return ((F64*)this)[index];
	}
	const F64& operator()(int index) const {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 3);
		return ((F64*)this)[index];
	}
	F64 x;
	F64 y;
	F64 z;
};

FDK_FORGE_API   void    Vec3dInit           (Vec3d* outVec);
FDK_FORGE_API   void    Vec3dInitWithValues (F64 x, F64 y, F64 z, Vec3d* outVec);
FDK_FORGE_API   F64     Vec3dGetLenght      (const Vec3d& FDK_RESTRICT  inVec3d);
FDK_FORGE_API   void    Vec3dNormalize      (const Vec3d& FDK_RESTRICT  inVec3d, Vec3d* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3dMultScalar     (const Vec3d& FDK_RESTRICT  inVec3d, const F64 scalar, Vec3d* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3dMult           (const Vec3d& FDK_RESTRICT  l, const Vec3d& FDK_RESTRICT r, Vec3d* FDK_RESTRICT outVec);
//maybe should go in the direction class
FDK_FORGE_API   void    Vec3dAddScale       (const Vec3d& FDK_RESTRICT  orgin, const Vec3d& FDK_RESTRICT  direction, const F64 scalar, Vec3d* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3dSum            (const Vec3d& FDK_RESTRICT  l, const Vec3d& FDK_RESTRICT r, Vec3d* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3dSub            (const Vec3d& FDK_RESTRICT  l, const Vec3d& FDK_RESTRICT r, Vec3d* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3dCross          (const Vec3d& FDK_RESTRICT  l, const Vec3d& FDK_RESTRICT r, Vec3d* FDK_RESTRICT outVec);
FDK_FORGE_API   F64     Vec3dDot            (const Vec3d& FDK_RESTRICT  l, const Vec3d& FDK_RESTRICT r);
FDK_FORGE_API   void    Vec3dAbs            (const Vec3d& FDK_RESTRICT  inVec3d, Vec3d* FDK_RESTRICT outVec);

//Inplace

FDK_FORGE_API   void    Vec3dMultScalarInplace (const F64 scalar, Vec3d* outVec);
FDK_FORGE_API   void    Vec3dMultInplace       (const Vec3d& FDK_RESTRICT r, Vec3d* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3dSumInplace        (const Vec3d& FDK_RESTRICT r, Vec3d* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3dSubInplace        (const Vec3d& FDK_RESTRICT r, Vec3d* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Vec3dNormalizeInplace  (Vec3d* FDK_RESTRICT outVec);


FDK_NS_END

#endif
