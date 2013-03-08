// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies). 
// See Licence.txt 

#ifndef __FDK_PLATFORM_HEADER_DESF_H__
#define __FDK_PLATFORM_HEADER_DESF_H__

#if defined (FDK_OS_WIN)
	
	#include "fdk/windows_headers.h"

#elif defined(FDK_OS_OSX)

	#include <stdarg.h>
	#include <sys/types.h>
	#include <sys/uio.h>
	#include <unistd.h>

	#import <Foundation/Foundation.h>

#elif defined(FDK_OS_IOS)

	#include <stdarg.h>
	#include <sys/types.h>
	#include <sys/uio.h>
	#include <unistd.h>

	#import <Foundation/Foundation.h>
	#import <UIKit/UIKit.h>
	#import <CoreGraphics/CoreGraphics.h>

#elif defined(FDK_OS_PSVITA)

	#include <scebase.h>
	#include <libdbg.h>
	#include <assert.h>
	#include <ctype.h>



#elif defined(FDK_OS_PS3)

	//TODO: 
	

#else

	#error "Unsupported platform"

#endif

#endif
