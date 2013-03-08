// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_TRASFORM3F_H__
#define __FDK_TRASFORM3F_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/mathf.h"
#include "fdk/vec3f.h"
#include "fdk/quatf.h"
#include "fdk/mat44f.h"
#include "fdk/mat33f.h"
#include "fdk/mat22f.h"
#include "fdk/geometryf.h"

FDK_NS_BEGIN

struct Transform3f {
	
	Transform3f(Mat33f& _matRotation, Vec3f& _transfXYZ)  { mat44f.v00=_matRotation.v00; mat44f.v01=_matRotation.v01; mat44f.v02=_matRotation.v02; mat44f.v03=_transfXYZ.x; mat44f.v10=_matRotation.v10; mat44f.v11=_matRotation.v11; mat44f.v12=_matRotation.v12; mat44f.v13=_transfXYZ.y; mat44f.v20=_matRotation.v20; mat44f.v21=_matRotation.v21; mat44f.v22=_matRotation.v12; mat44f.v23=_transfXYZ.z; mat44f.v30=0.f; mat44f.v31=0.f; mat44f.v32=0.f; mat44f.v33=1.f;}
	
	Transform3f(Mat44f& _mat) { mat44f.v00=_mat.v00; mat44f.v01=_mat.v01; mat44f.v02=_mat.v02; mat44f.v03=_mat.v03; mat44f.v10=_mat.v10; mat44f.v11=_mat.v11, mat44f.v12=_mat.v12; mat44f.v13=_mat.v13; mat44f.v20=_mat.v20; mat44f.v21=_mat.v21, mat44f.v22=_mat.v22; mat44f.v23=_mat.v23; mat44f.v30=_mat.v30; mat44f.v31=_mat.v31, mat44f.v32=_mat.v32; mat44f.v33=_mat.v33; }
	
	Transform3f() {}
	
	operator const F32*() const { return (const F32*)(void*)this; }
	operator F32* () const { return (F32*)(void*)this; }


	//Affine transform
	//transform3f = | R00 R01 R02 Tx |
	//              | R10 R11 R12 Ty |
	//              | R20 R21 R22 Tz |
	//              |  0   0   0   1 |
	Mat44f mat44f;
};

//affine transforms
FDK_FORGE_API   void TransformInit3f(Transform3f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform3fRotationYZX(F32 headingY, F32 attitudeZ, F32 bankX, Transform3f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform3fRotationXYZ(F32 angleX, F32 angleY, F32 angleZ, Transform3f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform3fTranslation(const Vec3f& FDK_RESTRICT T, Transform3f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform3fScaleVec(const Vec3f& scaleVec, Transform3f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform3fScale(F32 scaleX, F32 scaleY, F32 scaleZ, Transform3f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void TransformMultiply3f(const Transform3f& FDK_RESTRICT second, const Transform3f& FDK_RESTRICT first, Transform3f* FDK_RESTRICT outTransform);
FDK_FORGE_API   Transform3f& Transform3fLookAtLH(const Vec3f& FDK_RESTRICT eye,const Vec3f& FDK_RESTRICT at,const Vec3f& FDK_RESTRICT up,Transform3f* FDK_RESTRICT outTransform);

//non affine transforms
FDK_FORGE_API   Transform3f& Transform3fPerspectiveFovLH(F32 fov,F32 aspect,F32 near,F32 far, Transform3f* FDK_RESTRICT outTransform);

//Transform objects

FDK_FORGE_API void Transform3fPoint     (const Transform3f& FDK_RESTRICT transf,const Point3f& FDK_RESTRICT point, Point3f* FDK_RESTRICT outPoint);
FDK_FORGE_API void Transform3fDirection (const Transform3f& FDK_RESTRICT transf,const Direction3f& FDK_RESTRICT direction, Direction3f* FDK_RESTRICT outDirection);
FDK_FORGE_API void Transform3fRay       (const Transform3f& FDK_RESTRICT transf,const Ray3f& ray, Ray3f* FDK_RESTRICT outRay);
FDK_FORGE_API void Transform3fPlane     (const Transform3f& FDK_RESTRICT transf,const Plane3f& FDK_RESTRICT plane, Plane3f* FDK_RESTRICT outPlane);


//Transform Inplace
FDK_FORGE_API void Transform3fPointInplace     (const Transform3f& FDK_RESTRICT transf, Point3f* FDK_RESTRICT outPoint);
FDK_FORGE_API void Transform3fRayInplace       (const Transform3f& FDK_RESTRICT transf, Ray3f* FDK_RESTRICT outRay);
FDK_FORGE_API void Transform3fDirectionInplace (const Transform3f& FDK_RESTRICT transf, Direction3f* FDK_RESTRICT outDirection);
FDK_FORGE_API void Transform3fPlaneInplace     (const Transform3f& FDK_RESTRICT transf, Plane3f* FDK_RESTRICT outPlane);

FDK_NS_END

#endif
