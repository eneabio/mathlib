#ifndef __FDK_FORGE_BASE_DEFS_H__
#define __FDK_FORGE_BASE_DEFS_H__

#ifndef __FDK_BASE_DEFS_H__
	#include "fdk/base_defs.h"
#endif

#if  defined(FDK_OS_PS3) || defined(FDK_OS_OSX) || defined(FDK_OS_IOS)
	
	#define FDK_FORGE_API

#elif defined (FDK_OS_WIN) || defined(FDK_OS_PSVITA) 

	#ifdef FDK_FORGE_LIB

		#define FDK_FORGE_API

	#else

		#ifdef FDK_FORGE_EXPORTS
			#define FDK_FORGE_API __declspec(dllexport)
		#else
			#define FDK_FORGE_API __declspec(dllimport)
		#endif

	#endif

#endif

#endif