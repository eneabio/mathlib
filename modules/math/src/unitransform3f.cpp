// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/unitransform3f.h"

FDK_NS_BEGIN
void    UniTransform3fInit(const F32 s, const Vec3f& T, const Quatf& R, UniTransform3f* outTransform) {
	outTransform->scale = s;
	Vec3fInitWithValues(T.x, T.y, T.z, &outTransform->translation);
	QuatfInitWithValues(R.qX, R.qY, R.qZ, R.qW, &outTransform->rotation);

}

void    UniTransform3fRotation(const Quatf& R, UniTransform3f* outTransform) {
	outTransform->scale = 1.f;
	Vec3fInitWithValues(0.f, 0.f, 0.f, &outTransform->translation);
	QuatfInitWithValues(R.qX, R.qY, R.qZ, R.qW, &outTransform->rotation);
	
}

void    UniTransform3fTranslation(const Vec3f& T, UniTransform3f* outTransform) {
	outTransform->scale = 1.f;
	Vec3fInitWithValues(T.x, T.y, T.z, &outTransform->translation);
	QuatfInitWithValues(0.f, 0.f, 0.f, 1.f, &outTransform->rotation);
	
}

void    UniTransform3fScale(const F32 s, UniTransform3f* outTransform) {
	outTransform->scale = s;
	Vec3fInitWithValues(0.f, 0.f, 0.f, &outTransform->translation);
	QuatfInitWithValues(0.f, 0.f, 0.f, 1.f, &outTransform->rotation);
	
}

void    UniTransform3fCat(const UniTransform3f& l, const UniTransform3f& r, UniTransform3f* outTransform) {
	//reference: pag. 201 Essential Mathematics for Games and Interactive Applications A Programmer’s Guide Second Edition
	
	//l is the first transformation, r is the second
	
	//set scale s' = sR * sL
	outTransform->scale = r.scale * l.scale;
	
	//set rotation r' = rR * rL
	QuatfMult(r.rotation, l.rotation, &outTransform->rotation);
	
	//set translation t' = tR + rR* (sR * tL) * invrR
	Vec4f sRtL = Vec4f(r.scale * l.translation.x, r.scale * l.translation.y, r.scale * l.translation.z, 0.f);
	
	Quatf quatP;
	QuatfInitWithValues(sRtL.x, sRtL.y, sRtL.z, 0.f, &quatP);
	Quatf ris;
	QuatfMult(r.rotation, quatP, &ris);
	
	
	Quatf invquat;
	QuatfInverse(r.rotation, &invquat);
	
	Quatf ris1;
	QuatfMult(ris, invquat, &ris1);
	
	
	outTransform->translation.x = r.translation.x + ris1.qX;
	outTransform->translation.y = r.translation.y + ris1.qY;
	outTransform->translation.z = r.translation.z + ris1.qZ;
	
}

//UniTransform objects

void UniTransform3fPoint(const UniTransform3f& transf,const Point3f& point, Point3f* outPoint) {
	//reference: pag. 200 Essential Mathematics for Games and Interactive Applications A Programmer’s Guide Second Edition
	//outPoint = quat * (scale * point) * inverseQuaternion + translate
	
	//scaleP = scale * point
	Vec4f scaleP = Vec4f(transf.scale * point.point.x, transf.scale * point.point.y, transf.scale * point.point.z, 1.f);
	
	Quatf quatP;
	QuatfInitWithValues(scaleP.x, scaleP.y, scaleP.z, 0.f, &quatP);
	Quatf ris;
	QuatfMult(transf.rotation, quatP, &ris);
	
	Quatf invquat;
	QuatfInverse(transf.rotation, &invquat);
	
	Quatf ris1;
	QuatfMult(ris, invquat, &ris1);
	
	outPoint->point.x = ris1.qX + transf.translation.x;
	outPoint->point.y = ris1.qY + transf.translation.y;
	outPoint->point.z = ris1.qZ + transf.translation.z;
}

void UniTransform3fDirection(const UniTransform3f& transf,const Direction3f& direction, Direction3f* outDirection) {
	//reference: pag. 200 Essential Mathematics for Games and Interactive Applications A Programmer’s Guide Second Edition
	//outDirection = quat * (scale * direction) * inverseQuaternion + translate
	
	Vec4f scaleD = Vec4f(transf.scale * direction.dir.x, transf.scale * direction.dir.y, transf.scale * direction.dir.z, 0.f);
	
	Quatf quatD;
	QuatfInitWithValues(scaleD.x, scaleD.y, scaleD.z, 0.f, &quatD);
	Quatf ris;
	QuatfMult(transf.rotation, quatD, &ris);
	
	Quatf invquat;
	QuatfInverse(transf.rotation, &invquat);
	
	Quatf ris1;
	QuatfMult(ris, invquat, &ris1);
	
	//traslation don't change direction
	outDirection->dir.x = ris1.qX; //+ transf.translation.x;
	outDirection->dir.y = ris1.qY; //+ transf.translation.y;
	outDirection->dir.z = ris1.qZ; //+ transf.translation.z;
}

void UniTransform3fRay(const UniTransform3f& transf,const Ray3f& ray, Ray3f* outRay) {
	//transform origin;
	UniTransform3fPoint(transf, ray.origin, &outRay->origin);
	
	//transform direction;
	UniTransform3fDirection(transf, ray.direction, &outRay->direction);
}

void UniTransform3fPlane(const UniTransform3f& transf,const Plane3f& plane, Plane3f* outPlane) {
	
	
	UniTransform3fDirection(transf, plane.norm.dir, &outPlane->norm.dir);
	F32 d = plane.d;
	
	Point3f point;
	//origin projection on the plane
	F32 t = - d/(plane.norm.dir.dir.x *plane.norm.dir.dir.x + plane.norm.dir.dir.y*plane.norm.dir.dir.y + plane.norm.dir.dir.z*plane.norm.dir.dir.z);
	point.point.x = t * plane.norm.dir.dir.x;
	point.point.y = t * plane.norm.dir.dir.y;
	point.point.z = t * plane.norm.dir.dir.z;
	
	Point3f transfPoint;
	UniTransform3fPoint(transf, point, &transfPoint);
	
	
	//distance fro origin and new point
	outPlane->d = Sqrtf((transfPoint.point.x * transfPoint.point.x)+(transfPoint.point.y * transfPoint.point.y)+(transfPoint.point.z * transfPoint.point.z));
	
}

FDK_NS_END