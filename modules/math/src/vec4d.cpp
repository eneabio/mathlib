// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/vec4d.h"
#include "fdk/mathd.h"

FDK_NS_BEGIN

void Vec4dInit(Vec4d* outVec) {
	outVec->x = 0.0;
	outVec->y = 0.0;
	outVec->z = 0.0;
	outVec->w = 0.0;
}

void Vec4dInitWithValues(F64 x, F64 y, F64 z, F64 w, Vec4d* outVec) {
	outVec->x = x;
	outVec->y = y;
	outVec->z = z;
	outVec->w = w;
}

F64 Vec4dGetLenght(const Vec4d& FDK_RESTRICT inVec4d) {
	F64 inVec4dxQ = inVec4d.x * inVec4d.x;
	F64 inVec4dyQ = inVec4d.y * inVec4d.y;
	F64 inVec4dzQ = inVec4d.z * inVec4d.z;
	F64 inVec4dwQ = inVec4d.w * inVec4d.w;
	return Sqrtd(inVec4dxQ + inVec4dyQ + inVec4dzQ + inVec4dwQ);
}

void  Vec4dNormalize(const Vec4d&  inVec4d, Vec4d* outVec) {
	F64 lenght = Vec4dGetLenght(inVec4d);
	if (lenght != 0) {
		outVec->x = inVec4d.x / lenght;
		outVec->y = inVec4d.y / lenght;
		outVec->z = inVec4d.z / lenght;
		outVec->w = inVec4d.w / lenght;
	}
}

void Vec4dMultScalar(const Vec4d& FDK_RESTRICT  inVec4d, const F64 scalar, Vec4d* outVec){
	outVec->x = scalar * inVec4d.x;
	outVec->y = scalar * inVec4d.y;
	outVec->z = scalar * inVec4d.z;
	outVec->w = scalar * inVec4d.w;
}


void Vec4dMult(const Vec4d& FDK_RESTRICT l, const Vec4d& FDK_RESTRICT r, Vec4d* FDK_RESTRICT outVec) {
	outVec->x = r.x * l.x;
	outVec->y = r.y * l.y;
	outVec->z = r.z * l.z;
	outVec->w = r.w * l.w;
}

void Vec4dSum(const Vec4d& FDK_RESTRICT l, const Vec4d& FDK_RESTRICT r, Vec4d* FDK_RESTRICT outVec) {
	outVec->x = r.x + l.x;
	outVec->y = r.y + l.y;
	outVec->z = r.z + l.z;
	outVec->w = r.w + l.w;
}

void Vec4dSub(const Vec4d& FDK_RESTRICT l, const Vec4d& FDK_RESTRICT r, Vec4d* FDK_RESTRICT outVec) {
	outVec->x = l.x - r.x;
	outVec->y = l.y - r.y;
	outVec->z = l.z - r.z;
	outVec->w = l.w - r.w;
}

F64 Vec4dDot(const Vec4d& FDK_RESTRICT l, const Vec4d& FDK_RESTRICT r) {
	F64 xMul = l.x * r.x;
	F64 yMul = l.y * r.y;
	F64 zMul = l.z * r.z;
	F64 wMul = l.w * r.w;
	F64 res = xMul + yMul + zMul + wMul;
	return res;
}

void Vec4dAbs(const Vec4d& FDK_RESTRICT  inVec4d, Vec4d* FDK_RESTRICT outVec) {
	outVec->x = Absd(inVec4d.x);
	outVec->y = Absd(inVec4d.y);
	outVec->z = Absd(inVec4d.z);
	outVec->w = Absd(inVec4d.w);
}

void Vec4dMultScalarInplace(const F64 scalar, Vec4d* outVec) {
	outVec->x = scalar * outVec->x;
	outVec->y = scalar * outVec->y;
	outVec->z = scalar * outVec->z;
	outVec->w = scalar * outVec->w;
}


void Vec4dMultInplace(const Vec4d& FDK_RESTRICT r, Vec4d* FDK_RESTRICT outVec) {
	outVec->x = outVec->x * r.x;
	outVec->y = outVec->y * r.y;
	outVec->z = outVec->z * r.z;
	outVec->w = outVec->w * r.w;
}

void Vec4dSumInplace(const Vec4d& FDK_RESTRICT r, Vec4d* FDK_RESTRICT outVec) {
	outVec->x = outVec->x + r.x;
	outVec->y = outVec->y + r.y;
	outVec->z = outVec->z + r.z;
	outVec->w = outVec->w + r.w;
}

void Vec4dSubInplace(const Vec4d& FDK_RESTRICT r, Vec4d* FDK_RESTRICT outVec) {
	outVec->x = outVec->x - r.x;
	outVec->y = outVec->y - r.y;
	outVec->z = outVec->z - r.z;
	outVec->w = outVec->w - r.w;
}

void  Vec4dNormalizeInplace(Vec4d* outVec) {
	F64 lenght = Vec4dGetLenght(*outVec);
	if (lenght != 0) {
		outVec->x = outVec->x / lenght;
		outVec->y = outVec->y / lenght;
		outVec->z = outVec->z / lenght;
		outVec->w = outVec->w / lenght;
	}
}

FDK_NS_END