// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/transform3f.h"
#include "fdk/mat44f.h"
#include "fdk/vec4f.h"
#include "fdk/vec3f.h"
#include "fdk/mathf.h"

FDK_NS_BEGIN

Transform3f&    Transform3fPerspectiveFovLH(F32 fov,F32 aspect,F32 zNear,F32 zFar, Transform3f* FDK_RESTRICT outTransform){
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
        Mat44fInit(&outTransform->mat44f);

	//build perspective projection matrix
	F32 yScale = 1.f/Tanf(fov*0.5f);
	F32 xScale = yScale / aspect;
	F32 Q      = zFar / (zFar-zNear);

	outTransform->mat44f.v00 = xScale;
	outTransform->mat44f.v11 = yScale;
	outTransform->mat44f.v22 = Q;
	outTransform->mat44f.v23 = -zNear*Q;
	outTransform->mat44f.v32 = 1.f;
	outTransform->mat44f.v33 = 0.f;

	return *outTransform;
}

Transform3f&    Transform3fLookAtLH(const Vec3f& FDK_RESTRICT eye,const Vec3f& FDK_RESTRICT at,const Vec3f& FDK_RESTRICT up,Transform3f* FDK_RESTRICT outTransform){
	//D3DX Matrix Look At version (in our case is transposed because we want to respect our convention M*v).
	//zaxis = normal(At - Eye)
	//xaxis = normal(cross(Up, zaxis))
	//yaxis = cross(zaxis, xaxis)
	//
	//xaxis.x           yaxis.x           zaxis.x          0
	//xaxis.y           yaxis.y           zaxis.y          0
	//xaxis.z           yaxis.z           zaxis.z          0
	//-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye) 1

	Vec3f xaxis;
	Vec3f yaxis;
	Vec3f zaxis;

	//init matrix to identity 
	Mat44fInit(&outTransform->mat44f);

	Vec3fSub(at,eye,&zaxis);
	Vec3fNormalizeInplace(&zaxis);
	Vec3fCross(up,zaxis,&xaxis);
	Vec3fNormalizeInplace(&xaxis);
	Vec3fCross(zaxis,xaxis,&yaxis);

	outTransform->mat44f.v00 = xaxis.x;
	outTransform->mat44f.v01 = xaxis.y;
	outTransform->mat44f.v02 = xaxis.z;

	outTransform->mat44f.v10 = yaxis.x;
	outTransform->mat44f.v11 = yaxis.y;
	outTransform->mat44f.v12 = yaxis.z;
	
	outTransform->mat44f.v20 = zaxis.x;
	outTransform->mat44f.v21 = zaxis.y;
	outTransform->mat44f.v22 = zaxis.z;

	outTransform->mat44f.v03 = -Vec3fDot(xaxis,eye);
	outTransform->mat44f.v13 = -Vec3fDot(yaxis,eye);
	outTransform->mat44f.v23 = -Vec3fDot(zaxis,eye);

	return *outTransform;
}

void TransformInit3f(Transform3f* outTransform) {
	//outTransform = | 1 0 0 0 |
	//               | 0 1 0 0 |
	//               | 0 0 1 0 |
	//               | 0 0 0 1 |
	
	// TODO: use direct assignments
	Vec4f column0 = Vec4f(1.f, 0.f, 0.f, 0.f);
	
	Vec4f column1 = Vec4f(0.f, 1.f, 0.f, 0.f);
	
	Vec4f column2 = Vec4f(0.f, 0.f, 1.f, 0.f);
	
	Vec4f column3 = Vec4f(0.f, 0.f, 0.f, 1.f);
	
	Mat44fInitWithColumnVec(column0, column1, column2, column3, (Mat44f*)&(outTransform->mat44f));
	
}

void    Transform3fRotationYZX(F32 headingY, F32 attitudeZ, F32 bankX, Transform3f* outTransform) {
	//outTransform = | R00 R01 R02 Tx |
	//               | R10 R11 R12 Ty |
	//               | R20 R21 R22 Tz |
	//               |  0   0   0   1 |
	
	//reference: http://www.euclideanspace.com/maths/geometry/rotations/euler/index.htm
	
	F32 sa = Sinf(attitudeZ);
	F32 ca = Cosf(attitudeZ);
	F32 sb = Sinf(bankX);
	F32 cb = Cosf(bankX);
	F32 sh = Sinf(headingY);
	F32 ch = Cosf(headingY);
	
	//row 0
	outTransform->mat44f.v00 = ch * ca;
	outTransform->mat44f.v01 = -ch * sa * cb + sh * sb;
	outTransform->mat44f.v02 = ch * sa * sb + sh * cb;
	outTransform->mat44f.v03 = 0.f;
	
	//row 1
	outTransform->mat44f.v10 = sa;
	outTransform->mat44f.v11 = ca * cb;
	outTransform->mat44f.v12 = -ca * sb;
	outTransform->mat44f.v13 = 0.f;
	
	//row 2
	outTransform->mat44f.v20 = -sh * ca;
	outTransform->mat44f.v21 = sh * sa * cb + ch * sb;
	outTransform->mat44f.v22 = -sh * sa * sb + ch * cb;
	outTransform->mat44f.v23 = 0.f;
	
	//row 3
	outTransform->mat44f.v30 = 0.f;
	outTransform->mat44f.v31 = 0.f;
	outTransform->mat44f.v32 = 0.f;
	outTransform->mat44f.v33 = 1.f;
	
}

void    Transform3fRotationXYZ(F32 angleX, F32 angleY, F32 angleZ, Transform3f* outTransform) {
	//angles in rad
	
	//X rotation
	F32 cosX = Cosf(angleX);
	F32 sinX = Sinf(angleX);
	
	Vec4f row0 = Vec4f(1.0f, 0.f, 0.f, 0.f);
	Vec4f row1 = Vec4f(0.f, cosX, -sinX, 0.f);
	Vec4f row2 = Vec4f(0.f, sinX, cosX, 0.f);
	Vec4f row3 = Vec4f(0.f, 0.f, 0.f, 1.f);
	Mat44f Rx = Mat44f(row0, row1, row2, row3);

	//Mat44fMultInplace(Rx, (Mat44f*)&(outTransform->mat44f));
	Mat44f I;
	Mat44fInit(&I);
	//R1 = Rx * I
	Mat44fMult(Rx, I, &(outTransform->mat44f));
	Mat44f R1 = outTransform->mat44f;
	
	//Y rotation
	F32 cosY = Cosf(angleY);
	F32 sinY = Sinf(angleY);
	Vec4fInitWithValues(cosY, 0.f, sinY, 0.f, &row0);
	Vec4fInitWithValues(0.f, 1.f, 0.f, 0.f, &row1);
	Vec4fInitWithValues(-sinY, 0.f, cosY, 0.f, &row2);
	Vec4fInitWithValues(0.f, 0.f, 0.f, 1.f, &row3);
	Mat44f Ry;
	Mat44fInitWithRowVec(row0, row1, row2, row3, &Ry);
	
	//Mat44fMultInplace(Ry, (Mat44f*)&(outTransform->mat44f));
	//R2 = Ry * R1
	Mat44fMult(Ry, R1, &(outTransform->mat44f));
	Mat44f R2 = outTransform->mat44f;
	
	//Z rotation
	F32 cosZ = Cosf(angleZ);
	F32 sinZ = Sinf(angleZ);
	Vec4fInitWithValues(cosZ, -sinZ, 0.f, 0.f, &row0);
	Vec4fInitWithValues(sinZ, cosZ, 0.f, 0.f, &row1);
	Vec4fInitWithValues(0.f, 0.f, 1.f, 0.f, &row2);
	Vec4fInitWithValues(0.f, 0.f, 0.f, 1.f, &row3);
	Mat44f Rz;
	Mat44fInitWithRowVec(row0, row1, row2, row3, &Rz);
	
	//Mat44fMultInplace(Rz, (Mat44f*)&(outTransform->mat44f));
	
	//outTransform->mat44f = Ry * R1
	Mat44fMult(Rz, R2, &(outTransform->mat44f));
	
}

void    Transform3fTranslation(const Vec3f& T, Transform3f* outTransform) {
	Vec4f column0 = Vec4f(1.f, 0.f, 0.f, 0.f);
	Vec4f column1 = Vec4f(0.f, 1.f, 0.f, 0.f);
	Vec4f column2 = Vec4f(0.f, 0.f, 1.f, 0.f);
	Vec4f column3 = Vec4f(T.x, T.y, T.z, 1.f);
	
	Mat44fInitWithColumnVec(column0, column1, column2, column3, (Mat44f*)&(outTransform->mat44f));
}

void    Transform3fScaleVec(const Vec3f& scaleVec, Transform3f* outTransform) {
	Vec4f column0 = Vec4f(scaleVec.x , 0.f, 0.f, 0.f);
	Vec4f column1 = Vec4f(0.f, scaleVec.y, 0.f, 0.f);
	Vec4f column2 = Vec4f(0.f, 0.f, scaleVec.z, 0.f);
	Vec4f column3 = Vec4f(0.f, 0.f, 0.f, 1.f);
	
	Mat44fInitWithColumnVec(column0, column1, column2, column3, (Mat44f*)&(outTransform->mat44f));
}

void    Transform3fScale(F32 scaleX, F32 scaleY, F32 scaleZ, Transform3f* outTransform) {
	Vec4f column0 = Vec4f(scaleX , 0.f, 0.f, 0.f);
	Vec4f column1 = Vec4f(0.f, scaleY, 0.f, 0.f);
	Vec4f column2 = Vec4f(0.f, 0.f, scaleZ, 0.f);
	Vec4f column3 = Vec4f(0.f, 0.f, 0.f, 1.f);
	
	Mat44fInitWithColumnVec(column0, column1, column2, column3, (Mat44f*)&(outTransform->mat44f));
}

void TransformMultiply3f(const Transform3f& FDK_RESTRICT l, const Transform3f& FDK_RESTRICT r, Transform3f* FDK_RESTRICT outTransform) {
	Mat44f outMat;
	Mat44fMult(l.mat44f, r.mat44f, &outMat);
	outTransform->mat44f = outMat;
}

//Transform objects
void Transform3fPoint(const Transform3f& transf,const Point3f& point, Point3f* outPoint) {
	
	//convert vec3f in vec4f
	//If we want to transform points then we represent it with the 4th row set to one
	const Vec4f vec = Vec4f(point.point.x, point.point.y, point.point.z, 1.f);
	Vec4f outVec;
	
	//transform: outVec = transf * vec
	Mat44fMultVector(transf.mat44f, vec, &outVec);
	
	outPoint->point.x = outVec.x;
	outPoint->point.y = outVec.y;
	outPoint->point.z = outVec.z;
}


void Transform3fDirection(const Transform3f& transf,const Direction3f& direction, Direction3f* outDirection) {
	//convert vec3f in vec4f
	//If we want to transform vectors then we represent it with the 4th row set to zero
	const Vec4f vec = Vec4f( direction.dir.x, direction.dir.y, direction.dir.z, 0.f);
	Vec4f outVec;
	
//	Mat44f invTr;
//	Mat44fInvert(transf.mat44f, &invTr);
//	Mat44fTransposeInplace(&invTr);
//	Mat44fMultVector(invTr, vec, &outVec);
	
	Mat44fMultVector(transf.mat44f, vec, &outVec);
	
	outDirection->dir.x = outVec.x;
	outDirection->dir.y = outVec.y;
	outDirection->dir.z = outVec.z;
}

void Transform3fRay(const Transform3f& transf,const Ray3f& ray, Ray3f* outRay) {
	
	//Vec4f outVec;
	
	Transform3fPoint(transf, ray.origin, &(outRay->origin));
	
	Transform3fDirection(transf, ray.direction, &(outRay->direction));
	
}


void Transform3fPlane(const Transform3f& transf,const Plane3f& plane, Plane3f* outPlane) {
	//Vec4f outVec;
	
	Point3f p;
	p.point.x = plane.norm.dir.dir.x * plane.d;
	p.point.y = plane.norm.dir.dir.y * plane.d;
	p.point.z = plane.norm.dir.dir.z * plane.d;
	
	Transform3fPointInplace(transf, &p);
	
	//transform: outVec = transf * vec
	//we use the inverse transpose of the 4×4 transfor- mationmatrix.Thus,theplaneL= N,D transformsusingthe4×4matrixFas
	//L′=(F−1)TL, reference book "Mathematics for 3d game programming"
	
	Transform3fDirection(transf, plane.norm.dir, &(outPlane->norm.dir));

	//outPlane->norm.dir.dir.x = outVec.x;
	//outPlane->norm.dir.dir.y = outVec.y;
	//outPlane->norm.dir.dir.z = outVec.z;
	
	outPlane->d = Vec3fDot(outPlane->norm.dir.dir, p.point);
	
	
}

//Transform object Inplace

void Transform3fPointInplace(const Transform3f& transf, Point3f* outPoint) {
	//convert vec3f in vec4f
	const Vec4f vec = Vec4f( outPoint->point.x, outPoint->point.y, outPoint->point.z, 1.f);
	Vec4f outVec;
	
	//transform: outVec = transf * vec
	Mat44fMultVector(transf.mat44f, vec, &outVec);
	
	outPoint->point.x = outVec.x;
	outPoint->point.y = outVec.y;
	outPoint->point.z = outVec.z;
}

void Transform3fRayInplace(const Transform3f& transf, Ray3f* outRay) {
	
	Transform3fPointInplace(transf, &(outRay->origin));

	Transform3fDirectionInplace(transf, &(outRay->direction));

}

void Transform3fDirectionInplace(const Transform3f& transf, Direction3f* outDirection) {
	
	//Vec4f outVec;
	
	//transform normal
	//const Vec4f vecNormal = Vec4f(outNormal->dir.dir.x, outNormal->dir.dir.y, outNormal->dir.dir.z, 0.f);
	//To transform direction vectors using the same 4×4 transformation matrices that we use to transform points, we extend direction vectors to four dimensions by setting the w coordinate to 0 ????
	//Mat44f newTransf;
	//Mat44fInitWithMatrix(transf.mat44f, &newTransf);
	//newTransf.v33 = 0;
	//Mat44fMultVector(newTransf, vecNormal, &outVec);
	
	//Mat44f invTr;
	//Mat44fInvert(transf.mat44f, &invTr);
	//Mat44fTransposeInplace(&invTr);
	//Mat44fMultVector(invTr, vecNormal, &outVec);
	
	Transform3fDirection(transf, *outDirection, outDirection);
	
	//outDirection->dir = outVec.x;
	//outDirection->dir.dir.y = outVec.y;
	//outDirection->dir.dir.z = outVec.y;
}

void Transform3fPlaneInplace(const Transform3f& transf, Plane3f* outPlane) {
	FDK_UNUSED(transf);		
	FDK_UNUSED(outPlane);		

	
	
}

FDK_NS_END
