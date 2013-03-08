// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/transform2f.h"
#include "fdk/mat44f.h"
#include "fdk/vec4f.h"

FDK_NS_BEGIN



void Transform2fInit(Transform2f* outTransform) {
	Vec3f column0;
	Vec3fInitWithValues(1.f, 0.f, 0.f, &column0);
	
	Vec3f column1;
	Vec3fInitWithValues(0.f, 1.f, 0.f, &column1);
	
	Vec3f column2;
	Vec3fInitWithValues(0.f, 0.f, 1.f, &column2);
	
	Mat33fInitWithColumnVec(column0, column1, column2, (Mat33f*)&(outTransform->mat33f));

}

void    Transform2fRotation(F32 angle, Transform2f* outTransform) {
	//angles in rad
	
	Vec3f column0;
	Vec3f column1;
	Vec3f column2;
	
	//Rotation
	F32 cosX = Cosf(angle);
	F32 sinX = Sinf(angle);
	Vec3fInitWithValues(cosX, sinX, 0.f, &column0);
	Vec3fInitWithValues(-sinX, cosX, 0.f, &column1);
	Vec3fInitWithValues(0.f, 0.f, 1.f, &column2);
	Mat33fInitWithColumnVec(column0, column1, column2, (Mat33f*)&(outTransform->mat33f));

}

void    Transform2fTranslation(const Vec2f& T, Transform2f* outTransform) {
	Vec3f column0;
	Vec3fInitWithValues(1.f, 0.f, 0.f, &column0);
	
	Vec3f column1;
	Vec3fInitWithValues(0.f, 1.f, 0.f, &column1);

	Vec3f column2;
	Vec3fInitWithValues(T.x, T.y, 1.f, &column2);
	
	Mat33fInitWithColumnVec(column0, column1, column2, (Mat33f*)&(outTransform->mat33f));

}

void    Transform2fScaleVec(const Vec2f& scaleVec, Transform2f* outTransform) {
	Vec3f column0;
	Vec3fInitWithValues(scaleVec.x , 0.f, 0.f, &column0);
	
	Vec3f column1;
	Vec3fInitWithValues(0.f, scaleVec.y, 0.f, &column1);
	
	
	Vec3f column2;
	Vec3fInitWithValues(0.f, 0.f, 1.f, &column2);
	
	Mat33fInitWithColumnVec(column0, column1, column2, (Mat33f*)&(outTransform->mat33f));

}

void    Transform2fScale(F32 scaleX, F32 scaleY, Transform2f* outTransform) {
	Vec3f column0;
	Vec3fInitWithValues(scaleX , 0.f, 0.f, &column0);
	
	Vec3f column1;
	Vec3fInitWithValues(0.f, scaleY, 0.f, &column1);
	
	
	Vec3f column2;
	Vec3fInitWithValues(0.f, 0.f, 1.f, &column2);
	
	Mat33fInitWithColumnVec(column0, column1, column2, (Mat33f*)&(outTransform->mat33f));
	
}

void    Transform2fShear(F32 shX, F32 shY,  Transform2f* outTransform) {
	//row 0
	outTransform->mat33f.v00 = 1.f;
	outTransform->mat33f.v01 = shX;
	outTransform->mat33f.v02 = 0.f;
	
	//row 1
	outTransform->mat33f.v10 = shY;
	outTransform->mat33f.v11 = 1.f;
	outTransform->mat33f.v12 = 0.f;
	
	//row 2
	outTransform->mat33f.v20 = 0.f;
	outTransform->mat33f.v21 = 0.f;
	outTransform->mat33f.v22 = 1.f;
	
}

//transform objects

void Transform2fPoint(const Transform2f& transf,const Point2f& point, Point2f* outPoint) {
	
	//convert vec2f in vec3f
	const Vec3f vec = Vec3f( point.point.x, point.point.y, 1.f);
	Vec3f outVec;
	
	//transform: outVec = transf * vec
	Mat33fMultVector(transf.mat33f, vec, &outVec);
	
	outPoint->point.x = outVec.x;
	outPoint->point.y = outVec.y;
}

void Transform2fDirection(const Transform2f& transf,const Direction2f& direction, Direction2f* outDirection) {
	
	//convert vec2f in vec3f
	const Vec3f vec = Vec3f(direction.dir.x, direction.dir.y, 0.f); //0.f or 1.f?
	Vec3f outVec;
	//To transform direction vectors using the same 3×3 transformation matrices that we use to transform points, we extend direction vectors to four dimensions by setting the w coordinate to 0 ????const
	Mat33f newTransf;
	Mat33fInitWithMatrix(transf.mat33f, &newTransf);
	newTransf.v22 = 0;
	Mat33fMultVector(newTransf, vec, &outVec);
	
	//transform: outVec = transf * vec
	//Mat33fMultVector(transf.mat33f, vec, &outVec);
	
	outDirection->dir.x = outVec.x;
	outDirection->dir.y = outVec.y;
}

void Transform2fRay(const Transform2f& transf,const Ray2f& ray, Ray2f* outRay) {
	
	Vec3f outVec;
	
	//transform origin
	const Vec3f vecOr = Vec3f( ray.origin.point.x, ray.origin.point.y, 1.f);
	Mat33fMultVector(transf.mat33f, vecOr, &outVec);
	outRay->origin.point.x = outVec.x;
	outRay->origin.point.y = outVec.y;
	
	//transform direction
	const Vec3f vecDir = Vec3f( ray.direction.dir.x , ray.direction.dir.y, 0.f);
	//To transform direction vectors using the same 3×3 transformation matrices that we use to transform points, we extend direction vectors to four dimensions by setting the w coordinate to 0 ????
	Mat33f newTransf;
	Mat33fInitWithMatrix(transf.mat33f, &newTransf);
	newTransf.v22 = 0;
	Mat33fMultVector(newTransf, vecDir, &outVec);
	
	//Mat33fMultVector(transf.mat33f, vecDir, &outVec);
	outRay->direction.dir.x = outVec.x;
	outRay->direction.dir.y = outVec.y;
}

void    Transform2fCat(const Transform2f& FDK_RESTRICT l, const Transform2f& FDK_RESTRICT r, Transform2f* FDK_RESTRICT outTransform) {
	Mat33f outMat;
	Mat33fMult(l.mat33f, r.mat33f, &outMat);
	outTransform->mat33f = outMat;
	
}

//Transform Inplace
void Transform2fPointInplace(const Transform2f& transf, Point2f* outPoint) {
	//convert vec2f in vec3f
	const Vec3f vec = Vec3f( outPoint->point.x, outPoint->point.y, 1.f );
	Vec3f outVec;
	
	//transform: outVec = transf * vec
	Mat33fMultVector(transf.mat33f, vec, &outVec);
	
	outPoint->point.x = outVec.x;
	outPoint->point.y = outVec.y;
}

void Transform2fRayInplace(const Transform2f& transf, Ray2f* outRay) {
	
	Vec3f outVec;
	
	//transform origin (point)
	const Vec3f vecOr = Vec3f( outRay->origin.point.x, outRay->origin.point.y, 1.f);
	Mat33fMultVector(transf.mat33f, vecOr, &outVec);
	outRay->origin.point.x = outVec.x;
	outRay->origin.point.y = outVec.y;
	
	//transform direction
	
	const Vec3f vecDir = Vec3f( outRay->direction.dir.x , outRay->direction.dir.y, 0.f);
	//To transform direction vectors using the same 3×3 transformation matrices that we use to transform points, we extend direction vectors to four dimensions by setting the w coordinate to 0 ????
	Mat33f newTransf;
	Mat33fInitWithMatrix(transf.mat33f, &newTransf);
	newTransf.v22 = 0;
	Mat33fMultVector(newTransf, vecDir, &outVec);
	
	//Mat33fMultVector(transf.mat33f, vecDir, &outVec);
	outRay->direction.dir.x = outVec.x;
	outRay->direction.dir.y = outVec.y;
}

FDK_NS_END