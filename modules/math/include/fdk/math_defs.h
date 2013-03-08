#ifndef __FDK_MATH_DEFS_H__
#define __FDK_MATH_DEFS_H__

#include "fdk/forge_defs.h"

FDK_NS_BEGIN

	//float
#define FDK_F32_PI       (3.141592653589793F)
#define FDK_F32_TOLL     (0.0001F)

	// In primitives later
#define FDK_F32_MAX      (3.402823466e+38F)
#define FDK_F32_EPSILON  (1.192092896e-07F)  //? it's 5.96e-08?
#define	FDK_F32_RAND_MAX (0x7fffffff)

	//half, values in floating point (F32)...
#define FDK_F16_PI       (3.14159F)
#define FDK_F16_TOLL     (0.01F)

	// In primitives later
#define FDK_F16_MAX      (6.550400e+004f)
#define FDK_F16_EPSILON  (4.8875809e-4f)  //reference D3DX10math.h (Microsoft)


	//double
#define FDK_F64_PI       (3.141592653589793238462)
#define FDK_F64_TOLL     (0.0001)

	// In primitives later
#define FDK_F64_MAX      (1.7976931348623158+308)
#define FDK_F64_EPSILON  (2.2204460492503131e-016)  //? it's 1.11e-16?

FDK_NS_END

#endif