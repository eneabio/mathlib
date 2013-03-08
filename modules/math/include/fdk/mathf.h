// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MATHF_H__
#define __FDK_MATHF_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/simd_defs.h"
#include "fdk/halffloat.h"
#include "fdk/math_defs.h"

FDK_NS_BEGIN

FDK_FORGE_API F32  Div2f    (const F32 num);
FDK_FORGE_API F32  Absf     (const F32 arg);
FDK_FORGE_API F32  ArcCosf  (const F32 arg);
FDK_FORGE_API F32  ArcSinf  (const F32 arg);
FDK_FORGE_API F32  ArcTanf  (const F32 arg);
FDK_FORGE_API F32  ArcTan2f (const F32 arg1, const F32 arg2);
FDK_FORGE_API F32  Ceilf    (const F32 x);
FDK_FORGE_API F32  Cosf     (const F32 arg);
FDK_FORGE_API F32  Coshf    (const F32 arg);
FDK_FORGE_API F32  Expf     (const F32 arg);
FDK_FORGE_API F32  Fabsf    (const F32 arg);
FDK_FORGE_API F32  Floorf   (const F32 arg);
FDK_FORGE_API F32  Fmodf    (const F32 arg1, const F32 arg2);
FDK_FORGE_API F32  Frexpf   (const F32 arg1, int *exp);
FDK_FORGE_API F32  Ldexpf   (const F32 arg1, const int exp);
FDK_FORGE_API F32  Logf     (const F32 arg);
FDK_FORGE_API F32  Log10f   (const F32 arg);
FDK_FORGE_API F32  Powf     (const F32 base, const F32 exp);
FDK_FORGE_API F32  Sinf     (const F32 arg);
FDK_FORGE_API F32  Sinhf    (const F32 arg);
FDK_FORGE_API F32  Sqrtf    (const F32 arg);
FDK_FORGE_API F32  Tanf     (const F32 arg);
FDK_FORGE_API F32  Tanhf    (const F32 arg);
FDK_FORGE_API F32  Deg2Radf (const F32 arg); //arg * (PI/180)
FDK_FORGE_API F32  Rad2Degf (const F32 arg); //arg * (180/PI)

FDK_FORGE_API F32  Epsilonf ();

FDK_FORGE_API FDK_INLINE bool FdkEqf32(F32 left, F32 right, F32 toll=FDK_F32_EPSILON) {
	//return ((((left - right) < toll) || ((left - right) < - toll)));
	return (Fabsf(left-right) < toll);
}

//half

FDK_FORGE_API F16  Div2h    (const F16 num);
FDK_FORGE_API F16  Absh     (const F16 arg);
FDK_FORGE_API F16  ArcCosh  (const F16 arg);
FDK_FORGE_API F16  ArcSinh  (const F16 arg);
FDK_FORGE_API F16  ArcTanh  (const F16 arg);
FDK_FORGE_API F16  ArcTan2h (const F16 arg1, const F16 arg2);
FDK_FORGE_API F16  Ceilh    (const F16 x);
FDK_FORGE_API F16  Cosh     (const F16 arg);
FDK_FORGE_API F16  Coshh    (const F16 arg);
FDK_FORGE_API F16  Exph     (const F16 arg);
FDK_FORGE_API F16  Fabsh    (const F16 arg);
FDK_FORGE_API F16  Floorh   (const F16 arg);
FDK_FORGE_API F16  Fmodh    (const F16 arg1, const F16 arg2);
FDK_FORGE_API F16  Frexph   (const F16 arg1, int *exp);
FDK_FORGE_API F16  Ldexph   (const F16 arg1, const int exp);
FDK_FORGE_API F16  Logh     (const F16 arg);
FDK_FORGE_API F16  Log10h   (const F16 arg);
FDK_FORGE_API F16  Powh     (const F16 base, const F16 exp);
FDK_FORGE_API F16  Sinh     (const F16 arg);
FDK_FORGE_API F16  Sinhh    (const F16 arg);
FDK_FORGE_API F16  Sqrth    (const F16 arg);
FDK_FORGE_API F16  Tanh     (const F16 arg);
FDK_FORGE_API F16  Tanhh    (const F16 arg);
FDK_FORGE_API F16  Deg2Radh (const F16 arg); //arg * (PI/180)
FDK_FORGE_API F16  Rad2Degh (const F16 arg); //arg * (180/PI)

FDK_FORGE_API F32  Epsilonh ();

FDK_FORGE_API FDK_INLINE bool FdkEqh16(F16 left, F16 right, F16 toll=FDK_F16_EPSILON) {
	return (Fabsh(left-right) < toll);
}


FDK_NS_END


#endif

