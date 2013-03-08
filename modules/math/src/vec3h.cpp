// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/vec3h.h"

FDK_NS_BEGIN

void Vec3hInit(Vec3h* outVec) {
	outVec->x = 0;
	outVec->y = 0;
	outVec->z = 0;
}

void Vec3hInitWithValues(F16 x, F16 y, F16 z, Vec3h* outVec) {
	outVec->x = x;
	outVec->y = y;
	outVec->z = z;
}

F16 Vec3hGetLenght(const Vec3h&  inVec3h) {
	F32 xF = toFloat32(inVec3h.x);
	F32 yF = toFloat32(inVec3h.y);
	F32 zF = toFloat32(inVec3h.z);
	F32 sq = Sqrtf(xF * xF + yF * yF + zF * zF);
	return toFloat16(sq);
}

void   Vec3hNormalize(const Vec3h&  inVec3h, Vec3h* outVec) {
	F16 length = Vec3hGetLenght(inVec3h);
	F32 lengthF = toFloat32(length);
	if (lengthF != 0) {
		F32 xF = toFloat32(inVec3h.x);
		F32 yF = toFloat32(inVec3h.y);
		F32 zF = toFloat32(inVec3h.z);
		xF = xF / lengthF ;
		yF = yF / lengthF ;
		zF = zF / lengthF ;
		outVec->x = toFloat16(xF);
		outVec->y = toFloat16(yF);
		outVec->z = toFloat16(zF);
	}
}

void Vec3hMultScalar(const Vec3h&  inVec3h, const F16 scalar, Vec3h* outVec){
	F32 scalarF = toFloat32(scalar);
	F32 xF = toFloat32(inVec3h.x) * scalarF;
	F32 yF = toFloat32(inVec3h.y) * scalarF;
	F32 zF = toFloat32(inVec3h.z) * scalarF;
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
	outVec->z = toFloat16(zF);
}

void Vec3hMult(const Vec3h& l, const Vec3h& r, Vec3h* outVec) {
	Vec3f lf;
	Vec3hToVec3f(l, &lf);
	Vec3f rf;
	Vec3hToVec3f(r, &rf);
	Vec3f outVecF;
	outVecF.x = rf.x * lf.x;
	outVecF.y = rf.y * lf.y;
	outVecF.z = rf.z * lf.z;
	Vec3fToVec3h(outVecF, outVec);
}

void Vec3hSum(const Vec3h& l, const Vec3h& r, Vec3h* outVec){
	Vec3f lf;
	Vec3hToVec3f(l, &lf);
	Vec3f rf;
	Vec3hToVec3f(r, &rf);
	Vec3f outVecF;
	Vec3fSum(lf, rf, &outVecF);
	Vec3fToVec3h(outVecF, outVec);
}

void Vec3hSub(const Vec3h& l, const Vec3h& r, Vec3h* outVec){
	Vec3f lf;
	Vec3hToVec3f(l, &lf);
	Vec3f rf;
	Vec3hToVec3f(r, &rf);
	Vec3f outVecF;
	Vec3fSub(lf, rf, &outVecF);
	Vec3fToVec3h(outVecF, outVec);
}

void Vec3hCross(const Vec3h& l, const Vec3h& r, Vec3h* outVec){
	Vec3f lF;
	Vec3hToVec3f(l, &lF);
	Vec3f rF;
	Vec3hToVec3f(r, &rF);
	Vec3f outVecF;
	outVecF.x = lF.y * rF.z - lF.z * rF.y;
	outVecF.y = lF.z * rF.x - lF.x * rF.z;
	outVecF.z = lF.x * rF.y - lF.y * rF.x;
	outVec->x = toFloat16(outVecF.x);
	outVec->y = toFloat16(outVecF.y);
	outVec->z = toFloat16(outVecF.z);
}

F16 Vec3hDot(const Vec3h& l, const Vec3h& r){
	Vec3f lF;
	Vec3hToVec3f(l, &lF);
	Vec3f rF;
	Vec3hToVec3f(r, &rF);
	F32 res = lF.x * rF.x + lF.y * rF.y + lF.z * rF.z;
	return toFloat16(res);
}

void Vec3hAbs   (const Vec3h&  inVec3h, Vec3h* outVec) {
	outVec->x = Absh(inVec3h.x);
	outVec->y = Absh(inVec3h.y);
	outVec->z = Absh(inVec3h.z);
}


void   Vec3hToVec3f        (const Vec3h&   inVec3h, Vec3f*  outVec3f) {
	outVec3f->x = toFloat32(inVec3h.x);
	outVec3f->y = toFloat32(inVec3h.y);
	outVec3f->z = toFloat32(inVec3h.z);
}

void   Vec3fToVec3h        (const Vec3f&   inVec3f, Vec3h*  outVec3h) {
	outVec3h->x = toFloat16(inVec3f.x);
	outVec3h->y = toFloat16(inVec3f.y);
	outVec3h->z = toFloat16(inVec3f.z);
}

void Vec3hMultScalarInplace(const F16 scalar, Vec3h* outVec) {
	F32 scalarF = toFloat32(scalar);
	F32 xF = toFloat32(outVec->x) * scalarF;
	F32 yF = toFloat32(outVec->y) * scalarF;
	F32 zF = toFloat32(outVec->z) * scalarF;
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
	outVec->z = toFloat16(zF);
}

void Vec3hMultInplace(const Vec3h& r, Vec3h* outVec){
	F32 xF = toFloat32(r.x) * toFloat32(outVec->x);
	F32 yF = toFloat32(r.y) * toFloat32(outVec->y);
	F32 zF = toFloat32(r.z) * toFloat32(outVec->z);
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
	outVec->z = toFloat16(zF);
}

void Vec3hSumInplace(const Vec3h& r, Vec3h* outVec){
	F32 xF = toFloat32(r.x) + toFloat32(outVec->x);
	F32 yF = toFloat32(r.y) + toFloat32(outVec->y);
	F32 zF = toFloat32(r.z) + toFloat32(outVec->z);
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
	outVec->z = toFloat16(zF);
}

void Vec3hSubInplace(const Vec3h& r, Vec3h* outVec){
	F32 xF = toFloat32(outVec->x) - toFloat32(r.x);
	F32 yF = toFloat32(outVec->y) - toFloat32(r.y);
	F32 zF = toFloat32(outVec->z) - toFloat32(r.z);
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
	outVec->z = toFloat16(zF);
}

FDK_NS_END
