// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_QUATH_H__
#define __FDK_QUATH_H__


#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/vec4h.h"
#include "fdk/vec3h.h"
#include "fdk/quatf.h"

FDK_NS_BEGIN

struct Vec3h;

struct Quath {
	
	Quath(F16 _qX,F16 _qY, F16 _qZ,F16 _qW) : qX(_qX), qY(_qY), qZ(_qZ), qW(_qW) {}
	
	Quath(const Vec4h& _vec) : qX(_vec.x), qY(_vec.y), qZ(_vec.z), qW(_vec.w)  {}
	
	Quath(const Vec3h& _axis, F16 _w) : qX(_axis.x), qY(_axis.y), qZ(_axis.z), qW(_w) {}
	
	Quath() {}
	
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
	
	F16 qX;  //X component of the quaternion's vector (i)
	F16 qY;  //Y component of the quaternion's vector (j)
	F16 qZ;  //Z component of the quaternion's vector (k)
	F16 qW;  //W component
};

FDK_FORGE_API  void   QuathInit                (Quath* outQuat);
FDK_FORGE_API  void   QuathIdentity            (Quath* outQuat);
FDK_FORGE_API  void   QuathInitWithValues      (F16 x, F16 y, F16 z, F16 w, Quath* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuathInitWithEulerAngles (F16 yaw, F16 roll, F16 pitch, Quath* FDK_RESTRICT outQuat);
FDK_FORGE_API  F16    QuathModulus             (const Quath& FDK_RESTRICT inQuath);
FDK_FORGE_API  F16    QuathSquaredModulus      (const Quath& FDK_RESTRICT inQuath);
FDK_FORGE_API  void   QuathNormalize           (const Quath& FDK_RESTRICT inQuath, Quath* FDK_RESTRICT outQuath);
FDK_FORGE_API  void   QuathConjugate           (const Quath& FDK_RESTRICT inQuath, Quath* FDK_RESTRICT outQuath);
FDK_FORGE_API  void   QuathInverse             (const Quath& FDK_RESTRICT inQuath, Quath* FDK_RESTRICT outQuath);
FDK_FORGE_API  F16    QuathDot                 (const Quath& FDK_RESTRICT l, const Quath& FDK_RESTRICT r);
FDK_FORGE_API  void   QuathSum                 (const Quath& FDK_RESTRICT l, const Quath& FDK_RESTRICT r, Quath* FDK_RESTRICT outQuath);
FDK_FORGE_API  void   QuathSub                 (const Quath& FDK_RESTRICT l, const Quath& FDK_RESTRICT r, Quath* FDK_RESTRICT outQuath);
FDK_FORGE_API  void   QuathAbs                 (const Quath& FDK_RESTRICT inQuath, Quath* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuathMultScalar          (const Quath& FDK_RESTRICT inQuat, const F16 scalar, Quath* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuathMult                (const Quath& FDK_RESTRICT l, const Quath& FDK_RESTRICT r, Quath* FDK_RESTRICT outQuath);
FDK_FORGE_API  void   QuathLerp                (const Quath& FDK_RESTRICT l, const Quath& FDK_RESTRICT r, F16 t, Quath* FDK_RESTRICT outQuath);
FDK_FORGE_API  void   QuathSlerp               (const Quath& FDK_RESTRICT l, const Quath& FDK_RESTRICT r, F16 t, Quath* FDK_RESTRICT outQuath);
FDK_FORGE_API  void   QuathFromAxisAngle       (const Vec3h& FDK_RESTRICT inAxis, F16 angle, Quath* FDK_RESTRICT outQuath);
FDK_FORGE_API  void   QuathGetAxis             (const Quath& FDK_RESTRICT inQuath, Vec3h* outAxis);
FDK_FORGE_API  void   QuathGetAngle            (const Quath& FDK_RESTRICT inQuath, F16* outAngle);
FDK_FORGE_API  void   QuathToAxisAngle         (const Quath& FDK_RESTRICT inQuath, F16* outAngle, Vec3h* outAxis);

FDK_FORGE_API  void   QuathToQuatf             (const Quath& FDK_RESTRICT  inQuath, Quatf* FDK_RESTRICT outQuatf);
FDK_FORGE_API  void   QuatfToQuath             (const Quatf& FDK_RESTRICT  inQuatf, Quath* FDK_RESTRICT outQuath);

//Inplace
FDK_FORGE_API  void QuathSumInplace (const Quath& FDK_RESTRICT r, Quath* FDK_RESTRICT outQuad);
FDK_FORGE_API  void QuathSubInplace (const Quath& FDK_RESTRICT r, Quath* FDK_RESTRICT outQuad);

FDK_NS_END

#endif
