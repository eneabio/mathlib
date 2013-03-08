// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_SIMD_DEFS_H__
#define __FDK_SIMD_DEFS_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"

FDK_NS_BEGIN

#if defined (FDK_USE_SIMD)
	#if defined (FDK_OS_WIN)
		#define FDK_USE_SSE
		#if defined (_M_IX86_FP)  //The _M_IX86_FP macro indicates which, if any, /arch compiler option was used, 2 if /arch:SSE2 was used
			#include <smmintrin.h>
		#else
			#include <emmintrin.h>
		#endif
	#endif

	#if defined (FDK_OS_OSX) || (FDK_OS_IOS)
		#if defined (__i386__) || defined (__x86_64__) && (FDK_OS_OSX)
			#define FDK_USE_SSE
				//FDK_USE_SSE_IN_API is enabled on Mac OSX by default, because memory is automatically aligned on 16-byte boundaries
				//if apps run into issues, we will disable the next line
				#define FDK_USE_SSE_IN_API
			#ifdef FDK_USE_SSE
				// include appropriate SSE level
				#if defined (__SSE4_1__)
					#include <smmintrin.h>
				#elif defined (__SSSE3__)
					#include <tmmintrin.h>
				#elif defined (__SSE3__)
					#include <pmmintrin.h>
				#else
					#include <emmintrin.h>
				#endif
			#endif //BT_USE_SSE
		#elif defined  ( __armv7__ ) && defined(FDK_OS_IOS)
			#ifdef __clang__
				#define FDK_USE_NEON 1

				#if defined FDK_USE_NEON //&& defined (__clang__)
					#include <arm_neon.h>
				#endif//FDK_USE_NEON
			#endif //__clang__
		#endif//__arm__
	#endif //OSX/IOS

#endif //(FDK_USE_SIMD)

#ifdef FDK_USE_SSE
	typedef __m128 fdkSimdFloat4;
#endif//FDK_USE_SSE

FDK_NS_END

#endif