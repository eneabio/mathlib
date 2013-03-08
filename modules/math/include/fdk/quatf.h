// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_QUATF_H__
#define __FDK_QUATF_H__


#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/vec4f.h"
#include "fdk/vec3f.h"

FDK_NS_BEGIN

struct Vec3f;

struct Quatf {
	
	Quatf(F32 _qX,F32 _qY, F32 _qZ,F32 _qW) : qX(_qX), qY(_qY), qZ(_qZ), qW(_qW) {}

	Quatf(const Vec4f& _vec) : qX(_vec.x), qY(_vec.y), qZ(_vec.z), qW(_vec.w)  {}

	Quatf(const Vec3f& _axis, F32 _w) : qX(_axis.x), qY(_axis.y), qZ(_axis.z), qW(_w) {}
	
	Quatf() {}

	operator const F32*() const { return (const F32*)(void*)this; }
	operator F32* () const { return (F32*)(void*)this; }
	
	F32& operator()(int index) {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 4);
		return ((F32*)this)[index];
	}
	const F32& operator()(int index) const {
		//assert
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 4);
		return ((F32*)this)[index];
	}
	
//	#if defined (__SPU__) && defined (__CELLOS_LV2__)
//		F32 x;
//		F32 y;
//		F32 z;
//		F32 w;
//	FDK_FORCE_INLINE const Vec4f&	get128() const
//	{
//		return *((const Vec4f*)&x);
//	}
//	#else //__CELLOS_LV2__ __SPU__
	#if defined (FDK_USE_SSE) || defined(FDK_USE_NEON) // _WIN32 || ARM
	#if defined (FDK_OS_OSX) || (FDK_OS_IOS)
		union {
			struct {
				F32 qX;  //X component of the quaternion's vector (i)
				F32 qY;  //Y component of the quaternion's vector (j)
				F32 qZ;  //Z component of the quaternion's vector (k)
				F32 qW;  //W component
			};
			fdkSimdFloat4 mVec128;
		};
	#elif defined (FDK_OS_WIN)
	#pragma warning(disable : 4201) // disable nonstandard extension used: nameless struct/union
		union {
			FDK_DATA_ALIGN16 struct {
				F32 qX;  //X component of the quaternion's vector (i)
				F32 qY;  //Y component of the quaternion's vector (j)
				F32 qZ;  //Z component of the quaternion's vector (k)
				F32 qW;  //W component
			};
			fdkSimdFloat4 mVec128;
		};
	#endif
		FDK_FORCE_INLINE fdkSimdFloat4	get128() const {
			return mVec128;
		}
		FDK_FORCE_INLINE void	set128(fdkSimdFloat4 v128) {
			mVec128 = v128;
		}
	#else
		F32 qX;  //X component of the quaternion's vector (i)
		F32 qY;  //Y component of the quaternion's vector (j)
		F32 qZ;  //Z component of the quaternion's vector (k)
		F32 qW;  //W component
	#endif//	#endif //__CELLOS_LV2__ __SPU__
};

FDK_FORGE_API  void   QuatfInit                (Quatf* outQuat);
FDK_FORGE_API  void   QuatfIdentity            (Quatf* outQuat);
FDK_FORGE_API  void   QuatfInitWithValues      (F32 x, F32 y, F32 z, F32 w, Quatf* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatfInitWithEulerAngles (F32 yaw, F32 roll, F32 pitch, Quatf* FDK_RESTRICT outQuat);
FDK_FORGE_API  F32    QuatfModulus             (const Quatf& FDK_RESTRICT inQuatf);
FDK_FORGE_API  F32    QuatfSquaredModulus      (const Quatf& FDK_RESTRICT inQuatf);
FDK_FORGE_API  void   QuatfNormalize           (const Quatf& FDK_RESTRICT inQuatf, Quatf* FDK_RESTRICT outQuatf);
FDK_FORGE_API  void   QuatfConjugate           (const Quatf& FDK_RESTRICT inQuatf, Quatf* FDK_RESTRICT outQuatf);
FDK_FORGE_API  void   QuatfInverse             (const Quatf& FDK_RESTRICT inQuatf, Quatf* FDK_RESTRICT outQuatf);
FDK_FORGE_API  F32    QuatfDot                 (const Quatf& FDK_RESTRICT l, const Quatf& FDK_RESTRICT r);
FDK_FORGE_API  void   QuatfSum                 (const Quatf& FDK_RESTRICT l, const Quatf& FDK_RESTRICT r, Quatf* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatfSub                 (const Quatf& FDK_RESTRICT l, const Quatf& FDK_RESTRICT r, Quatf* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatfAbs                 (const Quatf& FDK_RESTRICT inQuatf, Quatf* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatfMultScalar          (const Quatf& FDK_RESTRICT inQuat, const F32 scalar, Quatf* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatfMult                (const Quatf& FDK_RESTRICT l, const Quatf& FDK_RESTRICT r, Quatf* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatfLerp                (const Quatf& FDK_RESTRICT l, const Quatf& FDK_RESTRICT r, F32 t, Quatf* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatfSlerp               (const Quatf& FDK_RESTRICT l, const Quatf& FDK_RESTRICT r, F32 t, Quatf* FDK_RESTRICT outQuat);
FDK_FORGE_API  void   QuatfFromAxisAngle       (const Vec3f& FDK_RESTRICT inAxis, F32 angle, Quatf* FDK_RESTRICT outQuatf);
FDK_FORGE_API  void   QuatfGetAxis             (const Quatf& FDK_RESTRICT inQuatf, Vec3f* outAxis);
FDK_FORGE_API  void   QuatfGetAngle            (const Quatf& FDK_RESTRICT inQuatf, F32* outAngle);
FDK_FORGE_API  void   QuatfToAxisAngle         (const Quatf& FDK_RESTRICT inQuatf, F32* outAngle, Vec3f* outAxis);

//Inplace
FDK_FORGE_API  void QuatfSumInplace (const Quatf& FDK_RESTRICT r, Quatf* FDK_RESTRICT outQuad);
FDK_FORGE_API  void QuatfSubInplace (const Quatf& FDK_RESTRICT r, Quatf* FDK_RESTRICT outQuad);

FDK_NS_END

#endif
