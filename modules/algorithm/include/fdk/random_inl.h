
#ifndef __FDK_RANDOM_INL_H__
#define __FDK_RANDOM_INL_H__

#include <stdlib.h>

FDK_NS_BEGIN

FDK_FORCE_INLINE void RandIntSetSeed(unsigned int seed) {
	::srand(seed);
}
FDK_FORCE_INLINE int RandInt() {
	return ::rand();
}

FDK_NS_END

#endif
