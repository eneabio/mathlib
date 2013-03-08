// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/vec3f.h"
#include "fdk/mathf.h"

#define FDK_RESTRICT

FDK_NS_BEGIN

void Vec3fInit(Vec3f* outVec) {
	outVec->x = 0.f;
	outVec->y = 0.f;
	outVec->z = 0.f;
}

void Vec3fInitWithValues(F32 x, F32 y, F32 z, Vec3f* outVec) {
	outVec->x = x;
	outVec->y = y;
	outVec->z = z;
}

F32 Vec3fGetLenght(const Vec3f&  inVec3f) {
	F32 inVec3fxQ = inVec3f.x * inVec3f.x;
	F32 inVec3fyQ = inVec3f.y * inVec3f.y;
	F32 inVec3fzQ = inVec3f.z * inVec3f.z;
	return Sqrtf(inVec3fxQ + inVec3fyQ + inVec3fzQ);
}

void Vec3fNormalize(const Vec3f&  inVec3f, Vec3f* outVec) {
	F32 lenght = Vec3fGetLenght(inVec3f);
	if (lenght != 0) {
		outVec->x = inVec3f.x / lenght;
		outVec->y = inVec3f.y / lenght;
		outVec->z = inVec3f.z / lenght;
	}
}

void Vec3fMultScalar(const Vec3f&  inVec3f, const F32 scalar, Vec3f* outVec){
	outVec->x = scalar * inVec3f.x;
	outVec->y = scalar * inVec3f.y;
	outVec->z = scalar * inVec3f.z;
}

void Vec3fMult(const Vec3f& l, const Vec3f& r, Vec3f* outVec) {
	outVec->x = r.x * l.x;
	outVec->y = r.y * l.y;
	outVec->z = r.z * l.z;
}

void Vec3fAddScale(const Vec3f&  origin, const Vec3f&  direction, const F32 scalar, Vec3f* outVec) {
	Vec3f scaledDirection;
	Vec3fMultScalar(direction, scalar, &scaledDirection);
	Vec3fSum(origin, scaledDirection, outVec);
}

void Vec3fSum(const Vec3f& l, const Vec3f& r, Vec3f* outVec){
	outVec->x = l.x + r.x;
	outVec->y = l.y + r.y;
	outVec->z = l.z + r.z;
}

void  Vec3fSub(const Vec3f& l, const Vec3f& r, Vec3f* outVec){
	outVec->x = l.x - r.x;
	outVec->y = l.y - r.y;
	outVec->z = l.z - r.z;
}

void Vec3fCross(const Vec3f& l, const Vec3f& r, Vec3f* outVec){
	//P×Q=PyQz−PzQy,PzQx−PxQz,PxQy−PyQx
	outVec->x = l.y * r.z - l.z * r.y;
	outVec->y = l.z * r.x - l.x * r.z;
	outVec->z = l.x * r.y - l.y * r.x;
}

F32 Vec3fDot(const Vec3f& l, const Vec3f& r){
	F32 res = l.x * r.x + l.y * r.y + l.z * r.z;
	return res;
}

void Vec3fAbs   (const Vec3f&  inVec3f, Vec3f* outVec) {
	outVec->x = Absf(inVec3f.x);
	outVec->y = Absf(inVec3f.y);
	outVec->z = Absf(inVec3f.z);
}

void Vec3fMultScalarInplace(const F32 scalar, Vec3f* outVec) {
	outVec->x = scalar * outVec->x;
	outVec->y = scalar * outVec->y;
	outVec->z = scalar * outVec->z;
}


void Vec3fMultInplace(const Vec3f& r, Vec3f* outVec){
	outVec->x = r.x * outVec->x;
	outVec->y = r.y * outVec->y;
	outVec->z = r.z * outVec->z;
}

void Vec3fSumInplace(const Vec3f& r, Vec3f* outVec){
	outVec->x = outVec->x + r.x;
	outVec->y = outVec->y + r.y;
	outVec->z = outVec->z + r.z;
}

void Vec3fSubInplace(const Vec3f& r, Vec3f* outVec){
	outVec->x = outVec->x - r.x;
	outVec->y = outVec->y - r.y;
	outVec->z = outVec->z - r.z;
}

void  Vec3fNormalizeInplace(Vec3f* outVec) {
	F32 lenght = Vec3fGetLenght(*outVec);
	if (lenght != 0) {
		outVec->x = outVec->x / lenght;
		outVec->y = outVec->y / lenght;
		outVec->z = outVec->z / lenght;
	}
}

FDK_NS_END
