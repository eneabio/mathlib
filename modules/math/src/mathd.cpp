// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include <math.h>
#include "fdk/mathd.h"

FDK_NS_BEGIN

// ::::: DOUBLE :::::

F64 Div2d(F64 num) {
	if (num == 0.0f) return num;
	I64 x = reinterpret_cast<I64&>(num);
	x -= ((I64)1 << 52);
	return reinterpret_cast<F64&>(x);
	//return num/2.0;
}

F64 Absd(const F64 arg) {
	//int casted = *(int*)((void*)&arg);
	//casted &= 0x7FFFFFFF;
	//return *(F64*)((void*)&casted);
	return fabs(arg);
}

F64 ArcCosd(const F64 arg) {
	F64 res = acos(arg);
	return res;
}
F64 ArcSind(const F64 arg) {
	F64 res = asin(arg);
	return res;
}
F64 ArcTand(const F64 arg) {
	F64 res = atan(arg);
	return res;
}

F64 ArcTan2d(const F64 arg1, const F64 arg2) {
	F64 res = atan2(arg1, arg2);
	return res;
}

F64 Ceild(const F64 x) {
	F64 res = ceil(x);
	return res;
}

F64 Cosd(const F64 arg) {
	F64 res = cos(arg);
	return res;
}

F64 Coshd(const F64 arg) {
	F64 res = cosh(arg);
	return res;
}

F64 Expd(const F64 arg) {
	F64 res = exp(arg);
	return res;
}

F64 Fabsd(const F64 arg) {
	F64 res = fabs(arg);
	return res;
}

F64 Floord(const F64 arg) {
	F64 res = floor(arg);
	return res;
}

F64 Fmodd(const F64 arg1, const F64 arg2)  {
	F64 res = fmod(arg1, arg2);
	return res;
}

F64 Frexpd(const F64 arg1, int *exp) {
	F64 res = frexp(arg1, exp);
	return res;
}

F64 Ldexpd(const F64 arg1, const int exp) {
	F64 res = ldexp(arg1, exp);
	return res;
}

F64 Logd(const F64 arg) {
	F64 res = log(arg);
	return res;
}
F64 Log10d(const F64 arg) {
	F64 res = log10(arg);
	return res;
}
F64 Powd(const F64 base, const F64 exp) {
	F64 res = pow(base, exp);
	return res;
}

F64 Sind(const F64 arg) {
	F64 res = sin(arg);
	return res;
}

F64 Sinhd(const F64 arg) {
	F64 res = sinh(arg);
	return res;
}

F64  Sqrtd(const F64 arg) {
	F64 res = sqrt(arg);
	return res;
}

F64  Tand(const F64 arg)  {
	F64 res = tan(arg);
	return res;
}

F64  Tanhd(const F64 arg)  {
	F64 res = tanh(arg);
	return res;
}

F64  Deg2Radd(const F64 arg)  {
	return arg * (FDK_F64_PI/180.0);
}

F64  Rad2Degd(const F64 arg)  {
	return arg * (180.0/FDK_F64_PI);
}


F64  Epsilond () {
	int k = 0;
	F64 eps = 0.5;
	while ((eps + 1.0) > 1.0) {
		eps = eps / 2.0;
		k++;
	}
	return eps;
}


FDK_NS_END
