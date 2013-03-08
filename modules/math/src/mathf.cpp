// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include <math.h>
#include "fdk/mathf.h"


FDK_NS_BEGIN

// ::::: FLOAT :::::

F32 Div2f(F32 num) {
	if (num == 0.0f) return num;
	I32 x = reinterpret_cast<I32&>(num);
	x -= ((I32)1 << 23);
	return reinterpret_cast<F32&>(x);
}

F32 Absf(const F32 arg) {
	int casted = *(int*)((void*)&arg);
	casted &= 0x7FFFFFFF;
	return *(F32*)((void*)&casted);
}

F32 ArcCosf(const F32 arg) {
	F32 res = acosf(arg);
	return res;
}
F32 ArcSinf(const F32 arg) {
	F32 res = asinf(arg);
	return res;
}
F32 ArcTanf(const F32 arg) {
	F32 res = atanf(arg);
	return res;
}

F32 ArcTan2f(const F32 arg1, const F32 arg2) {
	F32 res = atan2f(arg1, arg2);
	return res;
}

F32 Ceilf(const F32 x) {
	F32 res = ceilf(x);
	return res;
}

F32 Cosf(const F32 arg) {
	F32 res = cosf(arg);
	return res;
}

F32 Coshf(const F32 arg) {
	F32 res = coshf(arg);
	return res;
}

F32 Expf(const F32 arg) {
	F32 res = expf(arg);
	return res;
}

F32 Fabsf(const F32 arg) {
	F32 res = fabsf(arg);
	return res;
}

F32 Floorf(const F32 arg) {
	F32 res = floorf(arg);
	return res;
}

F32 Fmodf(const F32 arg1, const F32 arg2)  {
	F32 res = fmodf(arg1, arg2);
	return res;
}

F32 Frexpf(const F32 arg1, int *exp) {
	F32 res = frexpf(arg1, exp);
	return res;
}

F32 Ldexpf(const F32 arg1, const int exp) {
	F32 res = ldexpf(arg1, exp);
	return res;
}

F32 Logf(const F32 arg) {
	F32 res = logf(arg);
	return res;
}
F32 Log10f(const F32 arg) {
	F32 res = log10f(arg);
	return res;
}
F32 Powf(const F32 base, const F32 exp) {
	F32 res = powf(base, exp);
	return res;
}

F32 Sinf(const F32 arg) {
	F32 res = sinf(arg);
	return res;
}

F32 Sinhf(const F32 arg) {
	F32 res = sinhf(arg);
	return res;
}

F32  Sqrtf(const F32 arg) {
	F32 res = sqrtf(arg);
	return res;
}

F32  Tanf(const F32 arg)  {
	F32 res = tanf(arg);
	return res;
}

F32  Tanhf(const F32 arg)  {
	F32 res = tanhf(arg);
	return res;
}

F32  Deg2Radf(const F32 arg)  {
	return arg * (FDK_F32_PI/180.f);
}

F32  Rad2Degf(const F32 arg)  {
	return arg * (180.f/FDK_F32_PI);
}

F32  Epsilonf () {
	int k = 0;
	F32 eps = 0.5f;
	while ((eps + 1.f) > 1.f) {
		eps = eps / 2.f;
		k++;
	}
	return eps;
}

// ::::: HALF :::::

F16 Div2h(F16 num) {
	F32 numF = toFloat32(num);
	int x = reinterpret_cast<int&>(numF);
	x -= (1 << 23);
	return toFloat16(reinterpret_cast<F32&>(x));
}

F16 Absh(const F16 arg) {
	F32 argF = toFloat32(arg);
	int casted = *(int*)((void*)&argF);
	casted &= 0x7FFFFFFF;
	return toFloat16(*(F32*)((void*)&casted));
}

F16 Fabsh(const F16 arg) {
	F32 abs = fabsf(toFloat32(arg));
	return toFloat16(abs);
}

F16 ArcCosh(const F16 arg) {
	F32 res = acosf(toFloat32(arg));
	return toFloat16(res);
}
F16 ArcSinh(const F16 arg) {
	F32 res = asinf(toFloat32(arg));
	return toFloat16(res);
}
F16 ArcTanh(const F16 arg) {
	F32 res = atanf(toFloat32(arg));
	return toFloat16(res);
}

F16 ArcTan2h(const F16 arg1, const F16 arg2) {
	F32 res = atan2f(toFloat32(arg1), toFloat32(arg2));
	return toFloat16(res);
}

F16 Ceilh(const F16 x) {
	F32 res = ceilf(toFloat32(x));
	return toFloat16(res);
}

F16 Cosh(const F16 arg) {
	F32 res = cosf(toFloat32(arg));
	return toFloat16(res);
}

F16 Coshh(const F16 arg) {
	F32 res = coshf(toFloat32(arg));
	return toFloat16(res);
}

F16 Exph(const F16 arg) {
	F32 res = expf(toFloat32(arg));
	return toFloat16(res);
}

F16 Floorh(const F16 arg) {
	F32 res = floorf(toFloat32(arg));
	return toFloat16(res);
}

F16 Fmodh(const F16 arg1, const F16 arg2)  {
	F32 res = fmodf(toFloat32(arg1), toFloat32(arg2));
	return toFloat16(res);
}

F16 Frexph(const F16 arg1, int *exp) {
	F32 res = frexpf(toFloat32(arg1), exp);
	return toFloat16(res);
}

F16 Ldexph(const F16 arg1, const int exp) {
	F32 res = ldexpf(toFloat32(arg1), exp);
	return toFloat16(res);
}

F16 Logh(const F16 arg) {
	F32 res = logf(toFloat32(arg));
	return toFloat16(res);
}
F16 Log10h(const F16 arg) {
	F32 res = log10f(arg);
	return toFloat16(res);
}
F16 Powh(const F16 base, const F16 exp) {
	F32 res = powf(toFloat32(base), toFloat32(exp));
	return toFloat16(res);
}

F16 Sinh(const F16 arg) {
	F32 res = sinf(toFloat32(arg));
	return toFloat16(res);
}

F16 Sinhh(const F16 arg) {
	F32 res = sinhf(toFloat32(arg));
	return toFloat16(res);
}

F16  Sqrth(const F16 arg) {
	F32 res = sqrtf(toFloat32(arg));
	return toFloat16(res);
}

F16  Tanh(const F16 arg)  {
	F32 res = tanf(toFloat32(arg));
	return toFloat16(res);
}

F16  Tanhh(const F16 arg)  {
	F32 res = tanhf(toFloat32(arg));
	return toFloat16(res);
}

F16  Deg2Radh(const F16 arg)  {
	F32 res = toFloat32(arg) * (FDK_F32_PI/180.f);
	return toFloat16(res);
}

F16  Rad2Degh(const F16 arg)  {
	F32 res = toFloat32(arg) * (180.f/FDK_F32_PI);
	return toFloat16(res);
}

F32  Epsilonh () {
	return Powf(2.f, -10.f);
}

FDK_NS_END
