// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_VEC4F_H__
#define __FDK_VEC4F_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/simd_defs.h"

FDK_NS_BEGIN

FDK_DATA_ALIGN16 struct Vec4f {
	
	Vec4f(F32 _x,F32 _y,F32 _z,F32 _w) : x(_x),y(_y),z(_z),w(_w) {}
	
	Vec4f() {}
	
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
					F32 x;
					F32 y;
					F32 z;
					F32 w;
				};
				fdkSimdFloat4 mVec128;
			};
		#elif defined (FDK_OS_WIN)
			#pragma warning(disable : 4201) // disable nonstandard extension used: nameless struct/union
			union {
				FDK_DATA_ALIGN16 struct {
					F32 x;
					F32 y;
					F32 z;
					F32 w;
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
		F32 x;
		F32 y;
		F32 z;
		F32 w;
	#endif
//	#endif //__CELLOS_LV2__ __SPU__
};




FDK_FORGE_API  void  Vec4fInit           (Vec4f* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4fInitWithValues (F32 x, F32 y, F32 z, F32 w, Vec4f* FDK_RESTRICT outVec);
FDK_FORGE_API  F32   Vec4fGetLenght      (const Vec4f& FDK_RESTRICT inVec4f);
FDK_FORGE_API  void  Vec4fNormalize      (const Vec4f& FDK_RESTRICT  inVec4f, Vec4f* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4fMultScalar     (const Vec4f& FDK_RESTRICT inVec4f, const F32 scalar, Vec4f* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4fMult           (const Vec4f& FDK_RESTRICT l, const Vec4f& FDK_RESTRICT r, Vec4f* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4fSum            (const Vec4f& FDK_RESTRICT l, const Vec4f& FDK_RESTRICT r, Vec4f* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4fSub            (const Vec4f& FDK_RESTRICT l, const Vec4f& FDK_RESTRICT r, Vec4f* FDK_RESTRICT outVec);
FDK_FORGE_API  F32   Vec4fDot            (const Vec4f& FDK_RESTRICT l, const Vec4f& FDK_RESTRICT r);
FDK_FORGE_API  void  Vec4fAbs            (const Vec4f& FDK_RESTRICT inVec4f, Vec4f* FDK_RESTRICT outVec);

//Inplace
			   		   
FDK_FORGE_API  void  Vec4fMultScalarInplace (const F32 scalar, Vec4f* outVec);
FDK_FORGE_API  void  Vec4fMultInplace       (const Vec4f& FDK_RESTRICT r, Vec4f* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4fSumInplace        (const Vec4f& FDK_RESTRICT r, Vec4f* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4fSubInplace        (const Vec4f& FDK_RESTRICT r, Vec4f* FDK_RESTRICT outVec);
FDK_FORGE_API  void  Vec4fNormalizeInplace  (Vec4f* FDK_RESTRICT outVec);

FDK_NS_END

#endif

