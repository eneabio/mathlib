// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/vec2h.h"

FDK_NS_BEGIN

void Vec2hInit(Vec2h* outVec) {
	outVec->x = 0;
	outVec->y = 0;
}

void Vec2hInitWithValues(F16 x, F16 y, Vec2h* outVec) {
	outVec->x = x;
	outVec->y = y;
}

F16 Vec2hGetLenght(const Vec2h&  inVec2h) {
	F32 xF = toFloat32(inVec2h.x);
	F32 yF = toFloat32(inVec2h.y);
	F32 sq = Sqrtf(xF * xF + yF * yF);
	return toFloat16(sq);
}

void   Vec2hNormalize(const Vec2h&  inVec2h, Vec2h* outVec) {
	F16 length = Vec2hGetLenght(inVec2h);
	F32 lengthF = toFloat32(length);
	if (lengthF != 0) {
		F32 xF = toFloat32(inVec2h.x);
		F32 yF = toFloat32(inVec2h.y);
		xF = xF / lengthF ;
		yF = yF / lengthF ;
		outVec->x = toFloat16(xF);
		outVec->y = toFloat16(yF);
	}
}

void Vec2hMultScalar(const Vec2h&  inVec2h, const F16 scalar, Vec2h* outVec){
	F32 scalarF = toFloat32(scalar);
	F32 xF = toFloat32(inVec2h.x) * scalarF;
	F32 yF = toFloat32(inVec2h.y) * scalarF;
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
}

void Vec2hMult(const Vec2h& l, const Vec2h& r, Vec2h* outVec) {
	Vec2f lf;
	Vec2hToVec2f(l, &lf);
	Vec2f rf;
	Vec2hToVec2f(r, &rf);
	Vec2f outVecF;
	outVecF.x = rf.x * lf.x;
	outVecF.y = rf.y * lf.y;
	Vec2fToVec2h(outVecF, outVec);
}

void Vec2hSum(const Vec2h& l, const Vec2h& r, Vec2h* outVec){
	Vec2f lf;
	Vec2hToVec2f(l, &lf);
	Vec2f rf;
	Vec2hToVec2f(r, &rf);
	Vec2f outVecF;
	Vec2fSum(lf, rf, &outVecF);
	Vec2fToVec2h(outVecF, outVec);
}

void Vec2hSub(const Vec2h& l, const Vec2h& r, Vec2h* outVec){
	Vec2f lf;
	Vec2hToVec2f(l, &lf);
	Vec2f rf;
	Vec2hToVec2f(r, &rf);
	Vec2f outVecF;
	Vec2fSub(lf, rf, &outVecF);
	Vec2fToVec2h(outVecF, outVec);
}

F16 Vec2hCross(const Vec2h& l, const Vec2h& r){
	Vec2f lf;
	Vec2hToVec2f(l, &lf);
	Vec2f rf;
	Vec2hToVec2f(r, &rf);
	F32 res = lf.x * rf.y - lf.y * rf.x;
	return toFloat16(res);
}

F16 Vec2hDot(const Vec2h& l, const Vec2h& r){
	Vec2f lf;
	Vec2hToVec2f(l, &lf);
	Vec2f rf;
	Vec2hToVec2f(r, &rf);
	F32 res = lf.x * rf.x + lf.y * rf.y;
	return toFloat16(res);
}

void Vec2hAbs   (const Vec2h&  inVec2h, Vec2h* outVec) {
	outVec->x = Absh(inVec2h.x);
	outVec->y = Absh(inVec2h.y);
}


void   Vec2hToVec2f        (const Vec2h&   inVec2h, Vec2f*  outVec2f) {
	outVec2f->x = toFloat32(inVec2h.x);
	outVec2f->y = toFloat32(inVec2h.y);
}

void   Vec2fToVec2h        (const Vec2f&   inVec2f, Vec2h*  outVec2h) {
	outVec2h->x = toFloat16(inVec2f.x);
	outVec2h->y = toFloat16(inVec2f.y);
}

void Vec2hMultScalarInplace(const F16 scalar, Vec2h* outVec) {
	F32 scalarF = toFloat32(scalar);
	F32 xF = toFloat32(outVec->x) * scalarF;
	F32 yF = toFloat32(outVec->y) * scalarF;
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
}

void Vec2hMultInplace(const Vec2h& r, Vec2h* outVec){
	F32 xF = toFloat32(r.x) * toFloat32(outVec->x);
	F32 yF = toFloat32(r.y) * toFloat32(outVec->y);
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
}

void Vec2hSumInplace(const Vec2h& r, Vec2h* outVec){
	F32 xF = toFloat32(r.x) + toFloat32(outVec->x);
	F32 yF = toFloat32(r.y) + toFloat32(outVec->y);
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
	
}

void Vec2hSubInplace(const Vec2h& r, Vec2h* outVec){
	F32 xF = toFloat32(outVec->x) - toFloat32(r.x);
	F32 yF = toFloat32(outVec->y) - toFloat32(r.y);
	outVec->x = toFloat16(xF);
	outVec->y = toFloat16(yF);
}

FDK_NS_END
