// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/vec2d.h"
#include "fdk/mathd.h"

FDK_NS_BEGIN

void Vec2dInit(Vec2d* outVec) {
	outVec->x = 0.0;
	outVec->y = 0.0;
}

void Vec2dInitWithValues(F64 x, F64 y, Vec2d* outVec) {
	outVec->x = x;
	outVec->y = y;
}

F64 Vec2dGetLenght(const Vec2d&  inVec2d) {
	F64 inVec2dxQ = inVec2d.x * inVec2d.x;
	F64 inVec2dyQ = inVec2d.y * inVec2d.y;
	return Sqrtd(inVec2dxQ + inVec2dyQ);
}

void   Vec2dNormalize(const Vec2d&  inVec2d, Vec2d* outVec) {
	F64 lenght = Vec2dGetLenght(inVec2d);
	if (lenght != 0) {
		outVec->x = inVec2d.x / lenght ;
		outVec->y = inVec2d.y / lenght ;
	}
}

void Vec2dMultScalar(const Vec2d&  inVec2d, const F64 scalar, Vec2d* outVec){
	outVec->x = scalar * inVec2d.x;
	outVec->y = scalar * inVec2d.y;
}

void Vec2dMult(const Vec2d& l, const Vec2d& r, Vec2d* outVec) {
	outVec->x = r.x * l.x;
	outVec->y = r.y * l.y;
}

void Vec2dSum(const Vec2d& l, const Vec2d& r, Vec2d* outVec){
	outVec->x = l.x + r.x;
	outVec->y = l.y + r.y;
}

void Vec2dSub(const Vec2d& l, const Vec2d& r, Vec2d* outVec){
	outVec->x = l.x - r.x;
	outVec->y = l.y - r.y;
}

F64 Vec2dCross(const Vec2d& l, const Vec2d& r){
	F64 res = l.x * r.y - l.y * r.x;
	return res;
}

F64 Vec2dDot(const Vec2d& l, const Vec2d& r){
	F64 res = l.x * r.x + l.y * r.y;
	return res;
}

void Vec2dAbs   (const Vec2d&  inVec2d, Vec2d* outVec) {
	outVec->x = Absd(inVec2d.x);
	outVec->y = Absd(inVec2d.y);
}

void Vec2dMultScalarInplace(const F64 scalar, Vec2d* outVec) {
	outVec->x = scalar * outVec->x;
	outVec->y = scalar * outVec->y;
}

void Vec2dMultInplace(const Vec2d& r, Vec2d* outVec){
	outVec->x = r.x * outVec->x;
	outVec->y = r.y * outVec->y;
}

void Vec2dSumInplace(const Vec2d& r, Vec2d* outVec){
	outVec->x = outVec->x + r.x;
	outVec->y = outVec->y + r.y;
}

void Vec2dSubInplace(const Vec2d& r, Vec2d* outVec){
	outVec->x = outVec->x - r.x;
	outVec->y = outVec->y - r.y;
}

FDK_NS_END
