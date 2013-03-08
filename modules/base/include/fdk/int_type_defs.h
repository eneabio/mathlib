// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies). 
// See Licence.txt 

#ifndef __FDK_INT_TYPE_DEFS_H__
#define __FDK_INT_TYPE_DEFS_H__

#if defined (FDK_OS_WIN)

	// Integer types
	#pragma warning (push,0)
	#include <cstdint>
	#pragma warning (pop)

#elif defined (FDK_OS_OSX) || defined (FDK_OS_IOS) || defined (FDK_OS_PS3)

	#include <stdint.h>
	

#elif defined (FDK_OS_PSVITA)
	
	#include <scebase.h>

#else

	#error "Integer types configuration not set for platform"

#endif

FDK_NS_BEGIN


typedef unsigned char FdkBool; //todo: Deprecated

typedef bool     Bool;

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef int8_t   I8;
typedef int16_t  I16;
typedef int32_t  I32;
typedef int64_t  I64;

//typedef short    F16;
typedef float    F32;
typedef double   F64;

typedef uintptr_t UPtr;
typedef intptr_t  IPtr;

typedef uintptr_t Size;
typedef intptr_t  SSize;

typedef uintptr_t UPtr;
typedef intptr_t  IPtr;


FDK_NS_END

#endif

