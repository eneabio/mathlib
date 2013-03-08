#include "fdk/ftl_common.h"

FDK_NS_BEGIN

FDK_INLINE U32 NextPow2(U32 val) {
	U32 n = val - 1;
	n = n | (n >> 1);
	n = n | (n >> 2);
	n = n | (n >> 4);
	n = n | (n >> 8);
	n = n | (n >> 16);
	n = n + 1;
	return n;
}

FDK_INLINE U32 ToPow2(U32 i) {
	if(i == 0)
		return (U32)-1;

	int bit = 31;
	if((i & 0xFFFFFF00) == 0){
		i <<= 24;
		bit = 7;
	}else if((i & 0xFFFF0000) == 0){
		i <<= 16;
		bit = 15;
	}else if((i & 0xFF000000) == 0){
		i <<= 8;
		bit = 23;
	}

	if((i & 0xF0000000) == 0){
		i <<= 4;
		bit -= 4;
	}

	while((i & 0x80000000) == 0){
		i <<= 1;
		bit--;
	}

	return bit;
}


FDK_NS_END