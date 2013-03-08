// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/vec3d.h"
#include "fdk/mathd.h"

#define FDK_RESTRICT

FDK_NS_BEGIN

void Vec3dInit(Vec3d* outVec) {
	outVec->x = 0.0;
	outVec->y = 0.0;
	outVec->z = 0.0;
}

void Vec3dInitWithValues(F64 x, F64 y, F64 z, Vec3d* outVec) {
	outVec->x = x;
	outVec->y = y;
	outVec->z = z;
}

F64 Vec3dGetLenght(const Vec3d&  inVec3d) {
	F64 inVec3dxQ = inVec3d.x * inVec3d.x;
	F64 inVec3dyQ = inVec3d.y * inVec3d.y;
	F64 inVec3dzQ = inVec3d.z * inVec3d.z;
	return Sqrtd(inVec3dxQ + inVec3dyQ + inVec3dzQ);
}

void Vec3dNormalize(const Vec3d&  inVec3d, Vec3d* outVec) {
	F64 lenght = Vec3dGetLenght(inVec3d);
	if (lenght != 0) {
		outVec->x = inVec3d.x / lenght;
		outVec->y = inVec3d.y / lenght;
		outVec->z = inVec3d.z / lenght;
	}
}

void Vec3dMultScalar(const Vec3d&  inVec3d, const F64 scalar, Vec3d* outVec){
	outVec->x = scalar * inVec3d.x;
	outVec->y = scalar * inVec3d.y;
	outVec->z = scalar * inVec3d.z;
}

void Vec3dMult(const Vec3d& l, const Vec3d& r, Vec3d* outVec) {
	outVec->x = r.x * l.x;
	outVec->y = r.y * l.y;
	outVec->z = r.z * l.z;
}

void Vec3dAddScale(const Vec3d&  origin, const Vec3d&  direction, const F64 scalar, Vec3d* outVec) {
	Vec3d scaledDirection;
	Vec3dMultScalar(direction, scalar, &scaledDirection);
	Vec3dSum(origin, scaledDirection, outVec);
}

void Vec3dSum(const Vec3d& l, const Vec3d& r, Vec3d* outVec){
	outVec->x = l.x + r.x;
	outVec->y = l.y + r.y;
	outVec->z = l.z + r.z;
}

void  Vec3dSub(const Vec3d& l, const Vec3d& r, Vec3d* outVec){
	outVec->x = l.x - r.x;
	outVec->y = l.y - r.y;
	outVec->z = l.z - r.z;
}

void Vec3dCross(const Vec3d& l, const Vec3d& r, Vec3d* outVec){
	//P×Q=PyQz−PzQy,PzQx−PxQz,PxQy−PyQx
	outVec->x = l.y * r.z - l.z * r.y;
	outVec->y = l.z * r.x - l.x * r.z;
	outVec->z = l.x * r.y - l.y * r.x;
}

F64 Vec3dDot(const Vec3d& l, const Vec3d& r){
	F64 res = l.x * r.x + l.y * r.y + l.z * r.z;
	return res;
}

void Vec3dAbs   (const Vec3d&  inVec3d, Vec3d* outVec) {
	outVec->x = Absd(inVec3d.x);
	outVec->y = Absd(inVec3d.y);
	outVec->z = Absd(inVec3d.z);
}

void Vec3dMultScalarInplace(const F64 scalar, Vec3d* outVec) {
	outVec->x = scalar * outVec->x;
	outVec->y = scalar * outVec->y;
	outVec->z = scalar * outVec->z;
}


void Vec3dMultInplace(const Vec3d& r, Vec3d* outVec){
	outVec->x = r.x * outVec->x;
	outVec->y = r.y * outVec->y;
	outVec->z = r.z * outVec->z;
}

void Vec3dSumInplace(const Vec3d& r, Vec3d* outVec){
	outVec->x = outVec->x + r.x;
	outVec->y = outVec->y + r.y;
	outVec->z = outVec->z + r.z;
}

void Vec3dSubInplace(const Vec3d& r, Vec3d* outVec){
	outVec->x = outVec->x - r.x;
	outVec->y = outVec->y - r.y;
	outVec->z = outVec->z - r.z;
}

void  Vec3dNormalizeInplace(Vec3d* outVec) {
	F64 lenght = Vec3dGetLenght(*outVec);
	if (lenght != 0) {
		outVec->x = outVec->x / lenght;
		outVec->y = outVec->y / lenght;
		outVec->z = outVec->z / lenght;
	}
}

FDK_NS_END
