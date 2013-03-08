// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/unitransform3d.h"

FDK_NS_BEGIN
void    UniTransform3dInit(const F64 s, const Vec3d& T, const Quatd& R, UniTransform3d* outTransform) {
	outTransform->scale = s;
	Vec3dInitWithValues(T.x, T.y, T.z, &outTransform->translation);
	QuatdInitWithValues(R.qX, R.qY, R.qZ, R.qW, &outTransform->rotation);
	
}

void    UniTransform3dRotation(const Quatd& R, UniTransform3d* outTransform) {
	outTransform->scale = 1.0;
	Vec3dInitWithValues(0.0, 0.0, 0.0, &outTransform->translation);
	QuatdInitWithValues(R.qX, R.qY, R.qZ, R.qW, &outTransform->rotation);
	
}

void    UniTransform3dTranslation(const Vec3d& T, UniTransform3d* outTransform) {
	outTransform->scale = 1.0;
	Vec3dInitWithValues(T.x, T.y, T.z, &outTransform->translation);
	QuatdInitWithValues(0.0, 0.0, 0.0, 1.0, &outTransform->rotation);
	
}

void    UniTransform3dScale(const F64 s, UniTransform3d* outTransform) {
	outTransform->scale = s;
	Vec3dInitWithValues(0.0, 0.0, 0.0, &outTransform->translation);
	QuatdInitWithValues(0.0, 0.0, 0.0, 1.0, &outTransform->rotation);
	
}

void    UniTransform3dCat(const UniTransform3d& l, const UniTransform3d& r, UniTransform3d* outTransform) {
	//reference: pag. 201 Essential Mathematics for Games and Interactive Applications A Programmer’s Guide Second Edition
	
	//l is the first transformation, r is the second
	
	//set scale s' = sR * sL
	outTransform->scale = r.scale * l.scale;
	
	//set rotation r' = rR * rL
	QuatdMult(r.rotation, l.rotation, &outTransform->rotation);
	
	//set translation t' = tR + rR* (sR * tL) * invrR
	Vec4d sRtL = Vec4d(r.scale * l.translation.x, r.scale * l.translation.y, r.scale * l.translation.z, 0.0);
	
	Quatd quatP;
	QuatdInitWithValues(sRtL.x, sRtL.y, sRtL.z, 0.0, &quatP);
	Quatd ris;
	QuatdMult(r.rotation, quatP, &ris);
	
	
	Quatd invquat;
	QuatdInverse(r.rotation, &invquat);
	
	Quatd ris1;
	QuatdMult(ris, invquat, &ris1);
	
	
	outTransform->translation.x = r.translation.x + ris1.qX;
	outTransform->translation.y = r.translation.y + ris1.qY;
	outTransform->translation.z = r.translation.z + ris1.qZ;
	
}

//UniTransform objects

void UniTransform3dPoint(const UniTransform3d& transf,const Point3d& point, Point3d* outPoint) {
	//reference: pag. 200 Essential Mathematics for Games and Interactive Applications A Programmer’s Guide Second Edition
	//outPoint = quat * (scale * point) * inverseQuaternion + translate
	
	//scaleP = scale * point
	Vec4d scaleP = Vec4d(transf.scale * point.point.x, transf.scale * point.point.y, transf.scale * point.point.z, 1.0);
	
	Quatd quatP;
	QuatdInitWithValues(scaleP.x, scaleP.y, scaleP.z, 0.0, &quatP);
	Quatd ris;
	QuatdMult(transf.rotation, quatP, &ris);
	
	Quatd invquat;
	QuatdInverse(transf.rotation, &invquat);
	
	Quatd ris1;
	QuatdMult(ris, invquat, &ris1);
	
	outPoint->point.x = ris1.qX + transf.translation.x;
	outPoint->point.y = ris1.qY + transf.translation.y;
	outPoint->point.z = ris1.qZ + transf.translation.z;
}

void UniTransform3dDirection(const UniTransform3d& transf,const Direction3d& direction, Direction3d* outDirection) {
	//reference: pag. 200 Essential Mathematics for Games and Interactive Applications A Programmer’s Guide Second Edition
	//outDirection = quat * (scale * direction) * inverseQuaternion + translate
	
	Vec4d scaleD = Vec4d(transf.scale * direction.dir.x, transf.scale * direction.dir.y, transf.scale * direction.dir.z, 0.0);
	
	Quatd quatD;
	QuatdInitWithValues(scaleD.x, scaleD.y, scaleD.z, 0.0, &quatD);
	Quatd ris;
	QuatdMult(transf.rotation, quatD, &ris);
	
	Quatd invquat;
	QuatdInverse(transf.rotation, &invquat);
	
	Quatd ris1;
	QuatdMult(ris, invquat, &ris1);
	
	//traslation don't change direction
	outDirection->dir.x = ris1.qX; //+ transf.translation.x;
	outDirection->dir.y = ris1.qY; //+ transf.translation.y;
	outDirection->dir.z = ris1.qZ; //+ transf.translation.z;
}

void UniTransform3dRay(const UniTransform3d& transf,const Ray3d& ray, Ray3d* outRay) {
	//transform origin;
	UniTransform3dPoint(transf, ray.origin, &outRay->origin);
	
	//transform direction;
	UniTransform3dDirection(transf, ray.direction, &outRay->direction);
}

void UniTransform3dPlane(const UniTransform3d& transf,const Plane3d& plane, Plane3d* outPlane) {
	
	
	UniTransform3dDirection(transf, plane.norm.dir, &outPlane->norm.dir);
	F64 d = plane.d;
	
	Point3d point;
	//origin projection on the plane
	F64 t = - d/(plane.norm.dir.dir.x *plane.norm.dir.dir.x + plane.norm.dir.dir.y*plane.norm.dir.dir.y + plane.norm.dir.dir.z*plane.norm.dir.dir.z);
	point.point.x = t * plane.norm.dir.dir.x;
	point.point.y = t * plane.norm.dir.dir.y;
	point.point.z = t * plane.norm.dir.dir.z;
	
	Point3d transfPoint;
	UniTransform3dPoint(transf, point, &transfPoint);
	
	
	//distance fro origin and new point
	outPlane->d = Sqrtd((transfPoint.point.x * transfPoint.point.x)+(transfPoint.point.y * transfPoint.point.y)+(transfPoint.point.z * transfPoint.point.z));
	
}

FDK_NS_END