// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies). 
// See Licence.txt 

#ifndef FDK_COMMON_DEFS_H
#define FDK_COMMON_DEFS_H

#ifndef NULL
	#define NULL (0L)
#endif

#define FDK_DISABLE_COPY(deviceName) deviceName(const deviceName& other);deviceName& operator=(const deviceName& other)

#define FDK_OFFSET_OF(type, member) ((unsigned int)(&((type*)0)->member))

#if defined(FDK_OS_PSVITA) || defined(FDK_OS_PS3) || defined(FDK_OS_WIN) || defined(FDK_OS_IOS) || defined(FDK_OS_OSX)
	#define FDK_UNUSED(x) ((void)x);
#else
	#error "FDK_UNUSED: not defined for platform"
#endif

#define FDK_UNIMPLEMENTED() { FDK_ASSERT(false); }

#endif


