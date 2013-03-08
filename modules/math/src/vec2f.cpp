// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/vec2f.h"
#include "fdk/mathf.h"

FDK_NS_BEGIN

void Vec2fInit(Vec2f* outVec) {
	outVec->x = 0.f;
	outVec->y = 0.f;
}

void Vec2fInitWithValues(F32 x, F32 y, Vec2f* outVec) {
	outVec->x = x;
	outVec->y = y;
}

F32 Vec2fGetLenght(const Vec2f&  inVec2f) {
	F32 inVec2fxQ = inVec2f.x * inVec2f.x;
	F32 inVec2fyQ = inVec2f.y * inVec2f.y;
	return Sqrtf(inVec2fxQ + inVec2fyQ);
}

void   Vec2fNormalize(const Vec2f&  inVec2f, Vec2f* outVec) {
	F32 lenght = Vec2fGetLenght(inVec2f);
	if (lenght != 0) {
		outVec->x = inVec2f.x / lenght ;
		outVec->y = inVec2f.y / lenght ;
	}
}

void Vec2fMultScalar(const Vec2f&  inVec2f, const F32 scalar, Vec2f* outVec){
	outVec->x = scalar * inVec2f.x;
	outVec->y = scalar * inVec2f.y;
}

void Vec2fMult(const Vec2f& l, const Vec2f& r, Vec2f* outVec) {
	outVec->x = r.x * l.x;
	outVec->y = r.y * l.y;
}

void Vec2fSum(const Vec2f& l, const Vec2f& r, Vec2f* outVec){
	outVec->x = l.x + r.x;
	outVec->y = l.y + r.y;
}

void Vec2fSub(const Vec2f& l, const Vec2f& r, Vec2f* outVec){
	outVec->x = l.x - r.x;
	outVec->y = l.y - r.y;
}

F32 Vec2fCross(const Vec2f& l, const Vec2f& r){
	F32 res = l.x * r.y - l.y * r.x;
	return res;
}

F32 Vec2fDot(const Vec2f& l, const Vec2f& r){
	F32 res = l.x * r.x + l.y * r.y;
	return res;
}

void Vec2fAbs   (const Vec2f&  inVec2f, Vec2f* outVec) {
	outVec->x = Absf(inVec2f.x);
	outVec->y = Absf(inVec2f.y);
}

void Vec2fMultScalarInplace(const F32 scalar, Vec2f* outVec) {
	outVec->x = scalar * outVec->x;
	outVec->y = scalar * outVec->y;
}

void Vec2fMultInplace(const Vec2f& r, Vec2f* outVec){
	outVec->x = r.x * outVec->x;
	outVec->y = r.y * outVec->y;
}

void Vec2fSumInplace(const Vec2f& r, Vec2f* outVec){
	outVec->x = outVec->x + r.x;
	outVec->y = outVec->y + r.y;
}

void Vec2fSubInplace(const Vec2f& r, Vec2f* outVec){
	outVec->x = outVec->x - r.x;
	outVec->y = outVec->y - r.y;
}

FDK_NS_END
