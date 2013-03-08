// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies). 
// See Licence.txt 

#ifndef __FDK_COMPILER_DEFS_H__
#define __FDK_COMPILER_DEFS_H__

#if defined(FDK_OS_WIN)

	#define FDK_FILE __FILE__
	#define FDK_LINE __LINE__
	#define FDK_CDECL __cdecl
	#define FDK_STDCALL __stdcall
	#define FDK_FUNCTION __FUNCTION__
	#define FDK_FUNCDNAME __FUNCDNAME__
	#define FDK_INLINE __inline
	#define FDK_FORCE_INLINE __forceinline
	#define FDK_DATA_ALIGN16 __declspec(align(16))
	#define FDK_RESTRICT

#elif defined(FDK_OS_OSX) || defined(FDK_OS_IOS)

	#define FDK_FILE         __FILE__
	#define FDK_LINE         __LINE__
	#define FDK_CDECL
	#define FDK_STDCALL
	#define FDK_FUNCTION
	#define FDK_FUNCDNAME
	#define FDK_INLINE       inline
	#define FDK_FORCE_INLINE inline
	#define FDK_DATA_ALIGN16
	#define FDK_RESTRICT


#elif defined(FDK_OS_PSVITA) 
	
	#define FDK_FILE         __FILE__
	#define FDK_LINE         __LINE__
	#define FDK_CDECL
	#define FDK_STDCALL
	#define FDK_FUNCTION
	#define FDK_FUNCDNAME
	#define FDK_INLINE       inline
	#define FDK_FORCE_INLINE inline
	#define FDK_DATA_ALIGN16
	#define FDK_RESTRICT

#elif defined(FDK_OS_PS3) 

	#define FDK_LINE         __LINE__
	#define FDK_CDECL
	#define FDK_STDCALL
	#define FDK_FUNCTION
	#define FDK_FUNCDNAME
	#define FDK_INLINE       inline
	#define FDK_FORCE_INLINE inline
	#define FDK_DATA_ALIGN16
	#define FDK_RESTRICT

#else

    #pragma error "Precompiler macros not set for platform"

#endif

#endif
