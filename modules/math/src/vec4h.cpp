// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/vec4h.h"
#include "fdk/mathf.h"

FDK_NS_BEGIN

void Vec4hInit(Vec4h* outVec) {
	outVec->x = 0;
	outVec->y = 0;
	outVec->z = 0;
	outVec->w = 0;
}

void Vec4hInitWithValues(F16 x, F16 y, F16 z, F16 w, Vec4h* outVec) {
	outVec->x = x;
	outVec->y = y;
	outVec->z = z;
	outVec->w = w;
}

F16 Vec4hGetLenght(const Vec4h& FDK_RESTRICT inVec4h) {
	F32 xF = toFloat32(inVec4h.x);
	F32 yF = toFloat32(inVec4h.y);
	F32 zF = toFloat32(inVec4h.z);
	F32 wF = toFloat32(inVec4h.w);
	F32 sq = Sqrtf(xF * xF + yF * yF + zF * zF + wF * wF);
	return toFloat16(sq);
}

void  Vec4hNormalize(const Vec4h&  inVec4h, Vec4h* outVec) {
	F16 length = Vec4hGetLenght(inVec4h);
	F32 lengthF = toFloat32(length);
	if (lengthF != 0) {
		F32 xF = toFloat32(inVec4h.x);
		F32 yF = toFloat32(inVec4h.y);
		F32 zF = toFloat32(inVec4h.z);
		F32 wF = toFloat32(inVec4h.w);
		xF = xF / lengthF ;
		yF = yF / lengthF ;
		zF = zF / lengthF ;
		wF = wF / lengthF ;
		outVec->x = toFloat16(xF);
		outVec->y = toFloat16(yF);
		outVec->z = toFloat16(zF);
		outVec->w = toFloat16(wF);
	}
}

void Vec4hMultScalar(const Vec4h& FDK_RESTRICT  inVec4h, const F16 scalar, Vec4h* outVec){
	F32 scalarF = toFloat32(scalar);
	F32 xF = toFloat32(inVec4h.x) * scalarF;
	F32 yF = toFloat32(inVec4h.y) * scalarF;
	F32 zF = toFloat32(inVec4h.z) * scalarF;
	F32 wF = toFloat32(inVec4h.w) * scalarF;
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
	outVec->z = toFloat16(zF);
	outVec->w = toFloat16(wF);
}


void Vec4hMult(const Vec4h& FDK_RESTRICT l, const Vec4h& FDK_RESTRICT r, Vec4h* FDK_RESTRICT outVec) {
	Vec4f lf;
	Vec4hToVec4f(l, &lf);
	Vec4f rf;
	Vec4hToVec4f(r, &rf);
	Vec4f outVecF;
	outVecF.x = rf.x * lf.x;
	outVecF.y = rf.y * lf.y;
	outVecF.z = rf.z * lf.z;
	outVecF.w = rf.w * lf.w;
	Vec4fToVec4h(outVecF, outVec);
}

void Vec4hSum(const Vec4h& FDK_RESTRICT l, const Vec4h& FDK_RESTRICT r, Vec4h* FDK_RESTRICT outVec) {
	Vec4f lf;
	Vec4hToVec4f(l, &lf);
	Vec4f rf;
	Vec4hToVec4f(r, &rf);
	Vec4f outVecF;
	Vec4fSum(lf, rf, &outVecF);
	Vec4fToVec4h(outVecF, outVec);
}

void Vec4hSub(const Vec4h& FDK_RESTRICT l, const Vec4h& FDK_RESTRICT r, Vec4h* FDK_RESTRICT outVec) {
	Vec4f lf;
	Vec4hToVec4f(l, &lf);
	Vec4f rf;
	Vec4hToVec4f(r, &rf);
	Vec4f outVecF;
	Vec4fSub(lf, rf, &outVecF);
	Vec4fToVec4h(outVecF, outVec);
}

F16 Vec4hDot(const Vec4h& FDK_RESTRICT l, const Vec4h& FDK_RESTRICT r) {
	Vec4f lF;
	Vec4hToVec4f(l, &lF);
	Vec4f rF;
	Vec4hToVec4f(r, &rF);
	F32 res = lF.x * rF.x + lF.y * rF.y + lF.z * rF.z + lF.w * rF.w;
	return toFloat16(res);
}

void Vec4hAbs(const Vec4h& FDK_RESTRICT  inVec4h, Vec4h* FDK_RESTRICT outVec) {
	outVec->x = Absh(inVec4h.x);
	outVec->y = Absh(inVec4h.y);
	outVec->z = Absh(inVec4h.z);
	outVec->w = Absh(inVec4h.w);
}

void   Vec4hToVec4f        (const Vec4h&   inVec4h, Vec4f*  outVec4f) {
	outVec4f->x = toFloat32(inVec4h.x);
	outVec4f->y = toFloat32(inVec4h.y);
	outVec4f->z = toFloat32(inVec4h.z);
	outVec4f->w = toFloat32(inVec4h.w);
}

void   Vec4fToVec4h        (const Vec4f&   inVec4f, Vec4h*  outVec4h) {
	outVec4h->x = toFloat16(inVec4f.x);
	outVec4h->y = toFloat16(inVec4f.y);
	outVec4h->z = toFloat16(inVec4f.z);
	outVec4h->w = toFloat16(inVec4f.w);
}


void Vec4hMultScalarInplace(const F16 scalar, Vec4h* outVec) {
	F32 scalarF = toFloat32(scalar);
	F32 xF = toFloat32(outVec->x) * scalarF;
	F32 yF = toFloat32(outVec->y) * scalarF;
	F32 zF = toFloat32(outVec->z) * scalarF;
	F32 wF = toFloat32(outVec->w) * scalarF;
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
	outVec->z = toFloat16(zF);
	outVec->w = toFloat16(wF);
}


void Vec4hMultInplace(const Vec4h& FDK_RESTRICT r, Vec4h* FDK_RESTRICT outVec) {
	F32 xF = toFloat32(r.x) * toFloat32(outVec->x);
	F32 yF = toFloat32(r.y) * toFloat32(outVec->y);
	F32 zF = toFloat32(r.z) * toFloat32(outVec->z);
	F32 wF = toFloat32(r.w) * toFloat32(outVec->w);
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
	outVec->z = toFloat16(zF);
	outVec->w = toFloat16(wF);
}

void Vec4hSumInplace(const Vec4h& FDK_RESTRICT r, Vec4h* FDK_RESTRICT outVec) {
	F32 xF = toFloat32(r.x) + toFloat32(outVec->x);
	F32 yF = toFloat32(r.y) + toFloat32(outVec->y);
	F32 zF = toFloat32(r.z) + toFloat32(outVec->z);
	F32 wF = toFloat32(r.w) + toFloat32(outVec->w);
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
	outVec->z = toFloat16(zF);
	outVec->w = toFloat16(wF);
}

void Vec4hSubInplace(const Vec4h& FDK_RESTRICT r, Vec4h* FDK_RESTRICT outVec) {
	F32 xF = toFloat32(outVec->x) - toFloat32(r.x);
	F32 yF = toFloat32(outVec->y) - toFloat32(r.y);
	F32 zF = toFloat32(outVec->z) - toFloat32(r.z);
	F32 wF = toFloat32(outVec->w) - toFloat32(r.w);
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
	outVec->z = toFloat16(zF);
	outVec->w = toFloat16(wF);
}

void  Vec4hNormalizeInplace(Vec4h* outVec) {
	F16 lenght = Vec4hGetLenght(*outVec);
	if (lenght != 0) {
		outVec->x = outVec->x / lenght;
		outVec->y = outVec->y / lenght;
		outVec->z = outVec->z / lenght;
		outVec->w = outVec->w / lenght;
	}
}

FDK_NS_END