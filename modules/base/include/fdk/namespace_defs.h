#ifndef __FDK_NAMESPACE_DEFS_H__
#define __FDK_NAMESPACE_DEFS_H__

#include "user_configurable_defs.h"

#if defined(FDK_USE_NAMESPACE)
        #define FDK_NS       ::FDK_NS_NAME
	#define FDK_NS_BEGIN namespace FDK_NS_NAME {
	#define FDK_NS_END   }
#else
        #define FDK_NS
	#define FDK_NS_BEGIN
	#define FDK_NS_END
#endif

#endif