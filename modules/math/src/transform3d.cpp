// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/transform3d.h"
#include "fdk/mat44d.h"
#include "fdk/vec4d.h"
#include "fdk/vec3d.h"
#include "fdk/mathd.h"

FDK_NS_BEGIN



Transform3d&    Transform3dPerspectiveFovLH(F64 fov,F64 aspect,F64 zNear,F64 zFar, Transform3d* FDK_RESTRICT outTransform){
	//D3DX Style Perspective Fov matrix layout (Left handed version -> *** IT DOES NOT HAVE ANYTHING TO DO WITH LEFT HANDED IN THE CONTEXT OF CLOCKWISE OR COUNTERCLOCKWISE ROTATION  ***)
	//In our case is transposed because we want to respect our convention M*v.
	//      xScale     0          0               0
	//	0        yScale       0               0
	//	0          0       zf/(zf-zn)         1
	//	0          0       -zn*zf/(zf-zn)     0
	//where:
	
	//yScale = 1/tan(fovY/2)
	//
	//xScale = yScale / aspect ratio
	
	//init matrix to identity
        Mat44dInit(&outTransform->mat44d);
	
	//build perspective projection matrix
	F64 yScale = 1.0/Tand(fov*0.5);
	F64 xScale = yScale / aspect;
	F64 Q      = zFar / (zFar-zNear);
	
	outTransform->mat44d.v00 = xScale;
	outTransform->mat44d.v11 = yScale;
	outTransform->mat44d.v22 = Q;
	outTransform->mat44d.v23 = -zNear*Q;
	outTransform->mat44d.v32 = 1.0;
	outTransform->mat44d.v33 = 0.0;
	
	return *outTransform;
}

Transform3d&    Transform3dLookAtLH(const Vec3d& FDK_RESTRICT eye,const Vec3d& FDK_RESTRICT at,const Vec3d& FDK_RESTRICT up,Transform3d* FDK_RESTRICT outTransform){
	//D3DX Matrix Look At version (in our case is transposed because we want to respect our convention M*v).
	//zaxis = normal(At - Eye)
	//xaxis = normal(cross(Up, zaxis))
	//yaxis = cross(zaxis, xaxis)
	//
	//xaxis.x           yaxis.x           zaxis.x          0
	//xaxis.y           yaxis.y           zaxis.y          0
	//xaxis.z           yaxis.z           zaxis.z          0
	//-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye) 1
	
	Vec3d xaxis;
	Vec3d yaxis;
	Vec3d zaxis;
	
	//init matrix to identity
	Mat44dInit(&outTransform->mat44d);
	
	Vec3dSub(at,eye,&zaxis);
	Vec3dNormalizeInplace(&zaxis);
	Vec3dCross(up,zaxis,&xaxis);
	Vec3dNormalizeInplace(&xaxis);
	Vec3dCross(zaxis,xaxis,&yaxis);
	
	outTransform->mat44d.v00 = xaxis.x;
	outTransform->mat44d.v01 = xaxis.y;
	outTransform->mat44d.v02 = xaxis.z;
	
	outTransform->mat44d.v10 = yaxis.x;
	outTransform->mat44d.v11 = yaxis.y;
	outTransform->mat44d.v12 = yaxis.z;
	
	outTransform->mat44d.v20 = zaxis.x;
	outTransform->mat44d.v21 = zaxis.y;
	outTransform->mat44d.v22 = zaxis.z;
	
	outTransform->mat44d.v03 = -Vec3dDot(xaxis,eye);
	outTransform->mat44d.v13 = -Vec3dDot(yaxis,eye);
	outTransform->mat44d.v23 = -Vec3dDot(zaxis,eye);
	
	return *outTransform;
}

void TransformInit3d(Transform3d* outTransform) {
	//outTransform = | 1 0 0 0 |
	//               | 0 1 0 0 |
	//               | 0 0 1 0 |
	//               | 0 0 0 1 |
	
	// TODO: use direct assignments
	Vec4d column0 = Vec4d(1.0, 0.0, 0.0, 0.0);
	
	Vec4d column1 = Vec4d(0.0, 1.0, 0.0, 0.0);
	
	Vec4d column2 = Vec4d(0.0, 0.0, 1.0, 0.0);
	
	Vec4d column3 = Vec4d(0.0, 0.0, 0.0, 1.0);
	
	Mat44dInitWithColumnVec(column0, column1, column2, column3, (Mat44d*)&(outTransform->mat44d));
	
}

void    Transform3dRotationYZX(F64 headingY, F64 attitudeZ, F64 bankX, Transform3d* outTransform) {
	//outTransform = | R00 R01 R02 Tx |
	//               | R10 R11 R12 Ty |
	//               | R20 R21 R22 Tz |
	//               |  0   0   0   1 |
	
	//reference: http://www.euclideanspace.com/maths/geometry/rotations/euler/index.htm
	
	F64 sa = Sind(attitudeZ);
	F64 ca = Cosd(attitudeZ);
	F64 sb = Sind(bankX);
	F64 cb = Cosd(bankX);
	F64 sh = Sind(headingY);
	F64 ch = Cosd(headingY);
	
	//row 0
	outTransform->mat44d.v00 = ch * ca;
	outTransform->mat44d.v01 = -ch * sa * cb + sh * sb;
	outTransform->mat44d.v02 = ch * sa * sb + sh * cb;
	outTransform->mat44d.v03 = 0.0;
	
	//row 1
	outTransform->mat44d.v10 = sa;
	outTransform->mat44d.v11 = ca * cb;
	outTransform->mat44d.v12 = -ca * sb;
	outTransform->mat44d.v13 = 0.0;
	
	//row 2
	outTransform->mat44d.v20 = -sh * ca;
	outTransform->mat44d.v21 = sh * sa * cb + ch * sb;
	outTransform->mat44d.v22 = -sh * sa * sb + ch * cb;
	outTransform->mat44d.v23 = 0.0;
	
	//row 3
	outTransform->mat44d.v30 = 0.0;
	outTransform->mat44d.v31 = 0.0;
	outTransform->mat44d.v32 = 0.0;
	outTransform->mat44d.v33 = 1.0;
	
}

void    Transform3dRotationXYZ(F64 angleX, F64 angleY, F64 angleZ, Transform3d* outTransform) {
	//angles in rad
	
	//X rotation
	F64 cosX = Cosd(angleX);
	F64 sinX = Sind(angleX);
	
	Vec4d row0 = Vec4d(1.0, 0.0, 0.0, 0.0);
	Vec4d row1 = Vec4d(0.0, cosX, -sinX, 0.0);
	Vec4d row2 = Vec4d(0.0, sinX, cosX, 0.0);
	Vec4d row3 = Vec4d(0.0, 0.0, 0.0, 1.0);
	Mat44d Rx = Mat44d(row0, row1, row2, row3);
	
	//Mat44dMultInplace(Rx, (Mat44d*)&(outTransform->mat44d));
	Mat44d I;
	Mat44dInit(&I);
	//R1 = Rx * I
	Mat44dMult(Rx, I, &(outTransform->mat44d));
	Mat44d R1 = outTransform->mat44d;
	
	//Y rotation
	F64 cosY = Cosd(angleY);
	F64 sinY = Sind(angleY);
	Vec4dInitWithValues(cosY, 0.0, sinY, 0.0, &row0);
	Vec4dInitWithValues(0.0, 1.0, 0.0, 0.0, &row1);
	Vec4dInitWithValues(-sinY, 0.0, cosY, 0.0, &row2);
	Vec4dInitWithValues(0.0, 0.0, 0.0, 1.0, &row3);
	Mat44d Ry;
	Mat44dInitWithRowVec(row0, row1, row2, row3, &Ry);
	
	//Mat44dMultInplace(Ry, (Mat44d*)&(outTransform->mat44d));
	//R2 = Ry * R1
	Mat44dMult(Ry, R1, &(outTransform->mat44d));
	Mat44d R2 = outTransform->mat44d;
	
	//Z rotation
	F64 cosZ = Cosd(angleZ);
	F64 sinZ = Sind(angleZ);
	Vec4dInitWithValues(cosZ, -sinZ, 0.0, 0.0, &row0);
	Vec4dInitWithValues(sinZ, cosZ, 0.0, 0.0, &row1);
	Vec4dInitWithValues(0.0, 0.0, 1.0, 0.0, &row2);
	Vec4dInitWithValues(0.0, 0.0, 0.0, 1.0, &row3);
	Mat44d Rz;
	Mat44dInitWithRowVec(row0, row1, row2, row3, &Rz);
	
	//Mat44dMultInplace(Rz, (Mat44d*)&(outTransform->mat44d));
	
	//outTransform->mat44d = Ry * R1
	Mat44dMult(Rz, R2, &(outTransform->mat44d));
	
}

void    Transform3dTranslation(const Vec3d& T, Transform3d* outTransform) {
	Vec4d column0 = Vec4d(1.0, 0.0, 0.0, 0.0);
	Vec4d column1 = Vec4d(0.0, 1.0, 0.0, 0.0);
	Vec4d column2 = Vec4d(0.0, 0.0, 1.0, 0.0);
	Vec4d column3 = Vec4d(T.x, T.y, T.z, 1.0);
	
	Mat44dInitWithColumnVec(column0, column1, column2, column3, (Mat44d*)&(outTransform->mat44d));
}

void    Transform3dScaleVec(const Vec3d& scaleVec, Transform3d* outTransform) {
	Vec4d column0 = Vec4d(scaleVec.x , 0.0, 0.0, 0.0);
	Vec4d column1 = Vec4d(0.0, scaleVec.y, 0.0, 0.0);
	Vec4d column2 = Vec4d(0.0, 0.0, scaleVec.z, 0.0);
	Vec4d column3 = Vec4d(0.0, 0.0, 0.0, 1.0);
	
	Mat44dInitWithColumnVec(column0, column1, column2, column3, (Mat44d*)&(outTransform->mat44d));
}

void    Transform3dScale(F64 scaleX, F64 scaleY, F64 scaleZ, Transform3d* outTransform) {
	Vec4d column0 = Vec4d(scaleX , 0.0, 0.0, 0.0);
	Vec4d column1 = Vec4d(0.0, scaleY, 0.0, 0.0);
	Vec4d column2 = Vec4d(0.0, 0.0, scaleZ, 0.0);
	Vec4d column3 = Vec4d(0.0, 0.0, 0.0, 1.0);
	
	Mat44dInitWithColumnVec(column0, column1, column2, column3, (Mat44d*)&(outTransform->mat44d));
}

void TransformMultiply3d(const Transform3d& FDK_RESTRICT l, const Transform3d& FDK_RESTRICT r, Transform3d* FDK_RESTRICT outTransform) {
	Mat44d outMat;
	Mat44dMult(l.mat44d, r.mat44d, &outMat);
	outTransform->mat44d = outMat;
}

//Transform objects
void Transform3dPoint(const Transform3d& transf,const Point3d& point, Point3d* outPoint) {
	
	//convert vec3d in vec4d
	//If we want to transform points then we represent it with the 4th row set to one
	const Vec4d vec = Vec4d(point.point.x, point.point.y, point.point.z, 1.0);
	Vec4d outVec;
	
	//transform: outVec = transf * vec
	Mat44dMultVector(transf.mat44d, vec, &outVec);
	
	outPoint->point.x = outVec.x;
	outPoint->point.y = outVec.y;
	outPoint->point.z = outVec.z;
}


void Transform3dDirection(const Transform3d& transf,const Direction3d& direction, Direction3d* outDirection) {
	//convert vec3d in vec4d
	//If we want to transform vectors then we represent it with the 4th row set to zero
	const Vec4d vec = Vec4d( direction.dir.x, direction.dir.y, direction.dir.z, 0.0);
	Vec4d outVec;
	
	//	Mat44d invTr;
	//	Mat44dInvert(transf.mat44d, &invTr);
	//	Mat44dTransposeInplace(&invTr);
	//	Mat44dMultVector(invTr, vec, &outVec);
	
	Mat44dMultVector(transf.mat44d, vec, &outVec);
	
	outDirection->dir.x = outVec.x;
	outDirection->dir.y = outVec.y;
	outDirection->dir.z = outVec.z;
}

void Transform3dRay(const Transform3d& transf,const Ray3d& ray, Ray3d* outRay) {
	
	//Vec4d outVec;
	
	Transform3dPoint(transf, ray.origin, &(outRay->origin));
	
	Transform3dDirection(transf, ray.direction, &(outRay->direction));
	
}


void Transform3dPlane(const Transform3d& transf,const Plane3d& plane, Plane3d* outPlane) {
	//Vec4d outVec;
	
	Point3d p;
	p.point.x = plane.norm.dir.dir.x * plane.d;
	p.point.y = plane.norm.dir.dir.y * plane.d;
	p.point.z = plane.norm.dir.dir.z * plane.d;
	
	Transform3dPointInplace(transf, &p);
	
	//transform: outVec = transf * vec
	//we use the inverse transpose of the 4×4 transfor- mationmatrix.Thus,theplaneL= N,D transformsusingthe4×4matrixFas
	//L′=(F−1)TL, reference book "Mathematics for 3d game programming"
	
	Transform3dDirection(transf, plane.norm.dir, &(outPlane->norm.dir));
	
	//outPlane->norm.dir.dir.x = outVec.x;
	//outPlane->norm.dir.dir.y = outVec.y;
	//outPlane->norm.dir.dir.z = outVec.z;
	
	outPlane->d = Vec3dDot(outPlane->norm.dir.dir, p.point);
	
	
}

//Transform object Inplace

void Transform3dPointInplace(const Transform3d& transf, Point3d* outPoint) {
	//convert vec3d in vec4d
	const Vec4d vec = Vec4d( outPoint->point.x, outPoint->point.y, outPoint->point.z, 1.0);
	Vec4d outVec;
	
	//transform: outVec = transf * vec
	Mat44dMultVector(transf.mat44d, vec, &outVec);
	
	outPoint->point.x = outVec.x;
	outPoint->point.y = outVec.y;
	outPoint->point.z = outVec.z;
}

void Transform3dRayInplace(const Transform3d& transf, Ray3d* outRay) {
	
	Transform3dPointInplace(transf, &(outRay->origin));
	
	Transform3dDirectionInplace(transf, &(outRay->direction));
	
}

void Transform3dDirectionInplace(const Transform3d& transf, Direction3d* outDirection) {
	
	//Vec4d outVec;
	
	//transform normal
	//const Vec4d vecNormal = Vec4d(outNormal->dir.dir.x, outNormal->dir.dir.y, outNormal->dir.dir.z, 0.0);
	//To transform direction vectors using the same 4×4 transformation matrices that we use to transform points, we extend direction vectors to four dimensions by setting the w coordinate to 0 ????
	//Mat44d newTransf;
	//Mat44dInitWithMatrix(transf.mat44d, &newTransf);
	//newTransf.v33 = 0;
	//Mat44dMultVector(newTransf, vecNormal, &outVec);
	
	//Mat44d invTr;
	//Mat44dInvert(transf.mat44d, &invTr);
	//Mat44dTransposeInplace(&invTr);
	//Mat44dMultVector(invTr, vecNormal, &outVec);
	
	Transform3dDirection(transf, *outDirection, outDirection);
	
	//outDirection->dir = outVec.x;
	//outDirection->dir.dir.y = outVec.y;
	//outDirection->dir.dir.z = outVec.y;
}

void Transform3dPlaneInplace(const Transform3d& transf, Plane3d* outPlane) {
	FDK_UNUSED(transf);
	FDK_UNUSED(outPlane);
	
	
	
}

FDK_NS_END
