// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/transform2d.h"
#include "fdk/mat44d.h"
#include "fdk/vec4d.h"

FDK_NS_BEGIN



void Transform2dInit(Transform2d* outTransform) {
	Vec3d column0;
	Vec3dInitWithValues(1.0, 0.0, 0.0, &column0);
	
	Vec3d column1;
	Vec3dInitWithValues(0.0, 1.0, 0.0, &column1);
	
	Vec3d column2;
	Vec3dInitWithValues(0.0, 0.0, 1.0, &column2);
	
	Mat33dInitWithColumnVec(column0, column1, column2, (Mat33d*)&(outTransform->mat33d));
	
}

void    Transform2dRotation(F64 angle, Transform2d* outTransform) {
	//angles in rad
	
	Vec3d column0;
	Vec3d column1;
	Vec3d column2;
	
	//Rotation
	F64 cosX = Cosd(angle);
	F64 sinX = Sind(angle);
	Vec3dInitWithValues(cosX, sinX, 0.0, &column0);
	Vec3dInitWithValues(-sinX, cosX, 0.0, &column1);
	Vec3dInitWithValues(0.0, 0.0, 1.0, &column2);
	Mat33dInitWithColumnVec(column0, column1, column2, (Mat33d*)&(outTransform->mat33d));
	
}

void    Transform2dTranslation(const Vec2d& T, Transform2d* outTransform) {
	Vec3d column0;
	Vec3dInitWithValues(1.0, 0.0, 0.0, &column0);
	
	Vec3d column1;
	Vec3dInitWithValues(0.0, 1.0, 0.0, &column1);
	
	Vec3d column2;
	Vec3dInitWithValues(T.x, T.y, 1.0, &column2);
	
	Mat33dInitWithColumnVec(column0, column1, column2, (Mat33d*)&(outTransform->mat33d));
	
}

void    Transform2dScaleVec(const Vec2d& scaleVec, Transform2d* outTransform) {
	Vec3d column0;
	Vec3dInitWithValues(scaleVec.x , 0.0, 0.0, &column0);
	
	Vec3d column1;
	Vec3dInitWithValues(0.0, scaleVec.y, 0.0, &column1);
	
	
	Vec3d column2;
	Vec3dInitWithValues(0.0, 0.0, 1.0, &column2);
	
	Mat33dInitWithColumnVec(column0, column1, column2, (Mat33d*)&(outTransform->mat33d));
	
}

void    Transform2dScale(F64 scaleX, F64 scaleY, Transform2d* outTransform) {
	Vec3d column0;
	Vec3dInitWithValues(scaleX , 0.0, 0.0, &column0);
	
	Vec3d column1;
	Vec3dInitWithValues(0.0, scaleY, 0.0, &column1);
	
	
	Vec3d column2;
	Vec3dInitWithValues(0.0, 0.0, 1.0, &column2);
	
	Mat33dInitWithColumnVec(column0, column1, column2, (Mat33d*)&(outTransform->mat33d));
	
}

void    Transform2dShear(F64 shX, F64 shY,  Transform2d* outTransform) {
	//row 0
	outTransform->mat33d.v00 = 1.0;
	outTransform->mat33d.v01 = shX;
	outTransform->mat33d.v02 = 0.0;
	
	//row 1
	outTransform->mat33d.v10 = shY;
	outTransform->mat33d.v11 = 1.0;
	outTransform->mat33d.v12 = 0.0;
	
	//row 2
	outTransform->mat33d.v20 = 0.0;
	outTransform->mat33d.v21 = 0.0;
	outTransform->mat33d.v22 = 1.0;
	
}

//transform objects

void Transform2dPoint(const Transform2d& transf,const Point2d& point, Point2d* outPoint) {
	
	//convert vec2d in vec3d
	const Vec3d vec = Vec3d( point.point.x, point.point.y, 1.0);
	Vec3d outVec;
	
	//transform: outVec = transf * vec
	Mat33dMultVector(transf.mat33d, vec, &outVec);
	
	outPoint->point.x = outVec.x;
	outPoint->point.y = outVec.y;
}

void Transform2dDirection(const Transform2d& transf,const Direction2d& direction, Direction2d* outDirection) {
	
	//convert vec2d in vec3d
	const Vec3d vec = Vec3d(direction.dir.x, direction.dir.y, 0.0); //0.0 or 1.0?
	Vec3d outVec;
	//To transform direction vectors using the same 3×3 transformation matrices that we use to transform points, we extend direction vectors to four dimensions by setting the w coordinate to 0 ????const
	Mat33d newTransf;
	Mat33dInitWithMatrix(transf.mat33d, &newTransf);
	newTransf.v22 = 0;
	Mat33dMultVector(newTransf, vec, &outVec);
	
	//transform: outVec = transf * vec
	//Mat33dMultVector(transf.mat33d, vec, &outVec);
	
	outDirection->dir.x = outVec.x;
	outDirection->dir.y = outVec.y;
}

void Transform2dRay(const Transform2d& transf,const Ray2d& ray, Ray2d* outRay) {
	
	Vec3d outVec;
	
	//transform origin
	const Vec3d vecOr = Vec3d( ray.origin.point.x, ray.origin.point.y, 1.0);
	Mat33dMultVector(transf.mat33d, vecOr, &outVec);
	outRay->origin.point.x = outVec.x;
	outRay->origin.point.y = outVec.y;
	
	//transform direction
	const Vec3d vecDir = Vec3d( ray.direction.dir.x , ray.direction.dir.y, 0.0);
	//To transform direction vectors using the same 3×3 transformation matrices that we use to transform points, we extend direction vectors to four dimensions by setting the w coordinate to 0 ????
	Mat33d newTransf;
	Mat33dInitWithMatrix(transf.mat33d, &newTransf);
	newTransf.v22 = 0;
	Mat33dMultVector(newTransf, vecDir, &outVec);
	
	//Mat33dMultVector(transf.mat33d, vecDir, &outVec);
	outRay->direction.dir.x = outVec.x;
	outRay->direction.dir.y = outVec.y;
}

void    Transform2dCat(const Transform2d& FDK_RESTRICT l, const Transform2d& FDK_RESTRICT r, Transform2d* FDK_RESTRICT outTransform) {
	Mat33d outMat;
	Mat33dMult(l.mat33d, r.mat33d, &outMat);
	outTransform->mat33d = outMat;
	
}

//Transform Inplace
void Transform2dPointInplace(const Transform2d& transf, Point2d* outPoint) {
	//convert vec2d in vec3d
	const Vec3d vec = Vec3d( outPoint->point.x, outPoint->point.y, 1.0 );
	Vec3d outVec;
	
	//transform: outVec = transf * vec
	Mat33dMultVector(transf.mat33d, vec, &outVec);
	
	outPoint->point.x = outVec.x;
	outPoint->point.y = outVec.y;
}

void Transform2dRayInplace(const Transform2d& transf, Ray2d* outRay) {
	
	Vec3d outVec;
	
	//transform origin (point)
	const Vec3d vecOr = Vec3d( outRay->origin.point.x, outRay->origin.point.y, 1.0);
	Mat33dMultVector(transf.mat33d, vecOr, &outVec);
	outRay->origin.point.x = outVec.x;
	outRay->origin.point.y = outVec.y;
	
	//transform direction
	
	const Vec3d vecDir = Vec3d( outRay->direction.dir.x , outRay->direction.dir.y, 0.0);
	//To transform direction vectors using the same 3×3 transformation matrices that we use to transform points, we extend direction vectors to four dimensions by setting the w coordinate to 0 ????
	Mat33d newTransf;
	Mat33dInitWithMatrix(transf.mat33d, &newTransf);
	newTransf.v22 = 0;
	Mat33dMultVector(newTransf, vecDir, &outVec);
	
	//Mat33dMultVector(transf.mat33d, vecDir, &outVec);
	outRay->direction.dir.x = outVec.x;
	outRay->direction.dir.y = outVec.y;
}

FDK_NS_END