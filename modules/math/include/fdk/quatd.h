// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_QUATD_H__
#define __FDK_QUATD_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/vec4f.h"
#include "fdk/Vec3d.h"

FDK_NS_BEGIN

struct Vec3d;

struct Quatd {
	
	Quatd(F64 _qX,F64 _qY, F64 _qZ,F64 _qW) : qX(_qX), qY(_qY), qZ(_qZ), qW(_qW) {}
	
	Quatd(const Vec4f& _vec) : qX(_vec.x), qY(_vec.y), qZ(_vec.z), qW(_vec.w)  {}
	
	Quatd(const Vec3d& _axis, F64 _w) : qX(_axis.x), qY(_axis.y), qZ(_axis.z), qW(_w) {}
	
	Quatd() {}
	
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
	
	F64 qX;  //X component of the quaternion's vector (i)
	F64 qY;  //Y component of the quaternion's vector (j)
	F64 qZ;  //Z component of the quaternion's vector (k)
	F64 qW;  //W component
};

FDK_FORGE_API  void   QuatdInit                (Quatd* outQuat);
FDK_FORGE_API  void   QuatdIdentity            (Quatd* outQuat);
FDK_FORGE_API  void   QuatdInitWithValues      (F64 x, F64 y, F64 z, F64 w, Quatd* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatdInitWithEulerAngles (F64 yaw, F64 roll, F64 pitch, Quatd* FDK_RESTRICT outQuat);
FDK_FORGE_API  F64    QuatdModulus             (const Quatd& FDK_RESTRICT inQuatd);
FDK_FORGE_API  F64    QuatdSquaredModulus      (const Quatd& FDK_RESTRICT inQuatd);
FDK_FORGE_API  void   QuatdNormalize           (const Quatd& FDK_RESTRICT inQuatd, Quatd* FDK_RESTRICT outQuatd);
FDK_FORGE_API  void   QuatdConjugate           (const Quatd& FDK_RESTRICT inQuatd, Quatd* FDK_RESTRICT outQuatd);
FDK_FORGE_API  void   QuatdInverse             (const Quatd& FDK_RESTRICT inQuatd, Quatd* FDK_RESTRICT outQuatd);
FDK_FORGE_API  F64    QuatdDot                 (const Quatd& FDK_RESTRICT l, const Quatd& FDK_RESTRICT r);
FDK_FORGE_API  void   QuatdSum                 (const Quatd& FDK_RESTRICT l, const Quatd& FDK_RESTRICT r, Quatd* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatdSub                 (const Quatd& FDK_RESTRICT l, const Quatd& FDK_RESTRICT r, Quatd* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatdAbs                 (const Quatd& FDK_RESTRICT inQuatd, Quatd* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatdMultScalar          (const Quatd& FDK_RESTRICT inQuat, const F64 scalar, Quatd* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatdMult                (const Quatd& FDK_RESTRICT l, const Quatd& FDK_RESTRICT r, Quatd* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatdLerp                (const Quatd& FDK_RESTRICT l, const Quatd& FDK_RESTRICT r, F64 t, Quatd* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatdSlerp               (const Quatd& FDK_RESTRICT l, const Quatd& FDK_RESTRICT r, F64 t, Quatd* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatdFromAxisAngle       (const Vec3d& FDK_RESTRICT inAxis, F64 angle, Quatd* FDK_RESTRICT outQuatd);
FDK_FORGE_API  void   QuatdGetAxis             (const Quatd& FDK_RESTRICT inQuatd, Vec3d* outAxis);
FDK_FORGE_API  void   QuatdGetAngle            (const Quatd& FDK_RESTRICT inQuatd, F64* outAngle);
FDK_FORGE_API  void   QuatdToAxisAngle         (const Quatd& FDK_RESTRICT inQuatd, F64* outAngle, Vec3d* outAxis);

//Inplace
FDK_FORGE_API  void QuatdSumInplace (const Quatd& FDK_RESTRICT r, Quatd* FDK_RESTRICT outQuad);
FDK_FORGE_API  void QuatdSubInplace (const Quatd& FDK_RESTRICT r, Quatd* FDK_RESTRICT outQuad);


FDK_NS_END

#endif