// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies). 
// See Licence.txt 


#if defined(FDK_OS_WIN)

	#define FDK_BREAK()     DebugBreak()
	#define FDK_ASSERT(arg) { bool __res__ =  (arg)  ; if ( !__res__ ) { FDK_BREAK(); }; if ( !__res__ ) ::ExitProcess(1); }
	#define FDK_SLOWASSERT(arg) { bool __res__ =  (arg)  ; if ( !__res__ ) { FDK_BREAK(); }; if ( !__res__ ) ::ExitProcess(1); }
	#define FDK_CHECK(arg)  { bool __res__ =  (arg)  ; if ( !__res__ ) { FDK_BREAK(); return false; }; }
	#define FDK_FAIL()      FDK_ASSERT(false);

#elif defined(FDK_OS_OSX)

	#include <assert.h>
	#define FDK_ASSERT(arg) assert((arg));
	#define FDK_CHECK(arg)  { bool __res__ =  (arg)  ; if ( !__res__ ) { return false; }; }
	#define FDK_FAIL()      FDK_ASSERT(false);

#elif defined(FDK_OS_IOS)

	#include <assert.h>
	#define FDK_ASSERT(arg) assert((arg));
	#define FDK_CHECK(arg)  { bool __res__ =  (arg)  ; if ( !__res__ ) { return false; }; }
	#define FDK_FAIL()      FDK_ASSERT(false);

#elif defined(FDK_OS_PSVITA)

	#include <scebase.h>

	#define FDK_ASSERT(arg) assert((arg));
	#define FDK_CHECK(arg)  { bool __res__ =  (arg)  ; if ( !__res__ ) { return false; }; }
	#define FDK_FAIL()      FDK_ASSERT(false);

#elif defined(FDK_OS_PS3)

	#include <assert.h>

	#define FDK_ASSERT(arg) assert((arg));
	#define FDK_CHECK(arg)  { bool __res__ =  (arg)  ; if ( !__res__ ) { return false; }; }
	#define FDK_FAIL()      FDK_ASSERT(false);

#else
    #pragma error "Assertions not defined for platform"

#endif
