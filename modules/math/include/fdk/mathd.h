// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MATHD_H__
#define __FDK_MATHD_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
//#include "fdk/halffloat.h"
#include "fdk/math_defs.h"

FDK_NS_BEGIN

//double

FDK_FORGE_API F64  Div2d    (const F64 num);
FDK_FORGE_API F64  Absd     (const F64 arg);
FDK_FORGE_API F64  ArcCosd  (const F64 arg);
FDK_FORGE_API F64  ArcSind  (const F64 arg);
FDK_FORGE_API F64  ArcTand  (const F64 arg);
FDK_FORGE_API F64  ArcTan2d (const F64 arg1, const F64 arg2);
FDK_FORGE_API F64  Ceild    (const F64 x);
FDK_FORGE_API F64  Cosd     (const F64 arg);
FDK_FORGE_API F64  Coshd    (const F64 arg);
FDK_FORGE_API F64  Expd     (const F64 arg);
FDK_FORGE_API F64  Fabsd    (const F64 arg);
FDK_FORGE_API F64  Floord   (const F64 arg);
FDK_FORGE_API F64  Fmodd    (const F64 arg1, const F64 arg2);
FDK_FORGE_API F64  Frexpd   (const F64 arg1, const int *exp);
FDK_FORGE_API F64  Ldexpd   (const F64 arg1, const int exp);
FDK_FORGE_API F64  Logd     (const F64 arg);
FDK_FORGE_API F64  Log10d   (const F64 arg);
FDK_FORGE_API F64  Powd     (const F64 base, const F32 exp);
FDK_FORGE_API F64  Sind     (const F64 arg);
FDK_FORGE_API F64  Sinhd    (const F64 arg);
FDK_FORGE_API F64  Sqrtd    (const F64 arg);
FDK_FORGE_API F64  Tand     (const F64 arg);
FDK_FORGE_API F64  Tanhd    (const F64 arg);
FDK_FORGE_API F64  Deg2Radd (const F64 arg); //arg * (PI/180)
FDK_FORGE_API F64  Rad2Degd (const F64 arg); //arg * (180/PI)

FDK_FORGE_API F64  Epsilond ();

FDK_FORGE_API FDK_INLINE bool FdkEqd64(F64 left, F64 right, F64 toll=FDK_F64_EPSILON) {
	//return ((((left - right) < toll) || ((left - right) < - toll)));
	return (Fabsd(left-right) < toll);

}

FDK_NS_END


#endif

