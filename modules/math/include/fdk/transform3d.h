// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_TRASFORM3D_H__
#define __FDK_TRASFORM3D_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/mathd.h"
#include "fdk/vec3d.h"
#include "fdk/quatd.h"
#include "fdk/mat44d.h"
#include "fdk/mat33d.h"
#include "fdk/mat22d.h"
#include "fdk/geometryd.h"

FDK_NS_BEGIN

struct Transform3d {
	
	Transform3d(Mat33d& _matRotation, Vec3d& _transfXYZ)  { mat44d.v00=_matRotation.v00; mat44d.v01=_matRotation.v01; mat44d.v02=_matRotation.v02; mat44d.v03=_transfXYZ.x; mat44d.v10=_matRotation.v10; mat44d.v11=_matRotation.v11; mat44d.v12=_matRotation.v12; mat44d.v13=_transfXYZ.y; mat44d.v20=_matRotation.v20; mat44d.v21=_matRotation.v21; mat44d.v22=_matRotation.v12; mat44d.v23=_transfXYZ.z; mat44d.v30=0.0; mat44d.v31=0.0; mat44d.v32=0.0; mat44d.v33=1.0;}
	
	Transform3d(Mat44d& _mat) { mat44d.v00=_mat.v00; mat44d.v01=_mat.v01; mat44d.v02=_mat.v02; mat44d.v03=_mat.v03; mat44d.v10=_mat.v10; mat44d.v11=_mat.v11, mat44d.v12=_mat.v12; mat44d.v13=_mat.v13; mat44d.v20=_mat.v20; mat44d.v21=_mat.v21, mat44d.v22=_mat.v22; mat44d.v23=_mat.v23; mat44d.v30=_mat.v30; mat44d.v31=_mat.v31, mat44d.v32=_mat.v32; mat44d.v33=_mat.v33; }
	
	Transform3d() {}
	
	operator const F64*() const { return (const F64*)(void*)this; }
	operator F64* () const { return (F64*)(void*)this; }
	
	
	//Affine transform
	//transform3d = | R00 R01 R02 Tx |
	//              | R10 R11 R12 Ty |
	//              | R20 R21 R22 Tz |
	//              |  0   0   0   1 |
	Mat44d mat44d;
};

//affine transforms
FDK_FORGE_API   void TransformInit3d(Transform3d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform3dRotationYZX(F64 headingY, F64 attitudeZ, F64 bankX, Transform3d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform3dRotationXYZ(F64 angleX, F64 angleY, F64 angleZ, Transform3d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform3dTranslation(const Vec3d& FDK_RESTRICT T, Transform3d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform3dScaleVec(const Vec3d& scaleVec, Transform3d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform3dScale(F64 scaleX, F64 scaleY, F64 scaleZ, Transform3d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void TransformMultiply3d(const Transform3d& FDK_RESTRICT second, const Transform3d& FDK_RESTRICT first, Transform3d* FDK_RESTRICT outTransform);
FDK_FORGE_API   Transform3d& Transform3dLookAtLH(const Vec3d& FDK_RESTRICT eye,const Vec3d& FDK_RESTRICT at,const Vec3d& FDK_RESTRICT up,Transform3d* FDK_RESTRICT outTransform);

//non affine transforms
FDK_FORGE_API   Transform3d& Transform3dPerspectiveFovLH(F64 fov,F64 aspect,F64 near,F64 far, Transform3d* FDK_RESTRICT outTransform);

//Transform objects

FDK_FORGE_API void Transform3dPoint     (const Transform3d& FDK_RESTRICT transf,const Point3d& FDK_RESTRICT point, Point3d* FDK_RESTRICT outPoint);
FDK_FORGE_API void Transform3dDirection (const Transform3d& FDK_RESTRICT transf,const Direction3d& FDK_RESTRICT direction, Direction3d* FDK_RESTRICT outDirection);
FDK_FORGE_API void Transform3dRay       (const Transform3d& FDK_RESTRICT transf,const Ray3d& ray, Ray3d* FDK_RESTRICT outRay);
FDK_FORGE_API void Transform3dPlane     (const Transform3d& FDK_RESTRICT transf,const Plane3d& FDK_RESTRICT plane, Plane3d* FDK_RESTRICT outPlane);


//Transform Inplace
FDK_FORGE_API void Transform3dPointInplace     (const Transform3d& FDK_RESTRICT transf, Point3d* FDK_RESTRICT outPoint);
FDK_FORGE_API void Transform3dRayInplace       (const Transform3d& FDK_RESTRICT transf, Ray3d* FDK_RESTRICT outRay);
FDK_FORGE_API void Transform3dDirectionInplace (const Transform3d& FDK_RESTRICT transf, Direction3d* FDK_RESTRICT outDirection);
FDK_FORGE_API void Transform3dPlaneInplace     (const Transform3d& FDK_RESTRICT transf, Plane3d* FDK_RESTRICT outPlane);

FDK_NS_END

#endif
