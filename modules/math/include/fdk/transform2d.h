// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_TRASFORM2F_H__
#define __FDK_TRASFORM2F_H__

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

struct Transform2d {
	
	Transform2d(Mat22d& _matRotation, Vec2d& _transfXY)  { mat33d.v00=_matRotation.v00; mat33d.v01=_matRotation.v01; mat33d.v02=_transfXY.x; mat33d.v10=_matRotation.v10; mat33d.v11=_matRotation.v11; mat33d.v12=_transfXY.y; mat33d.v20=0.0; mat33d.v21=0.0; mat33d.v22=1.0; }
	
	Transform2d(Mat33d& _mat) { mat33d.v00=_mat.v00; mat33d.v01=_mat.v01; mat33d.v02=_mat.v02; mat33d.v10=_mat.v10; mat33d.v11=_mat.v11, mat33d.v12=_mat.v12; mat33d.v20=_mat.v20; mat33d.v21=_mat.v21, mat33d.v22=_mat.v22; }
	
	Transform2d() {}
	
	//Transform2d = | R00 R01 Tx |
	//              | R10 R11 Ty |
	//              |  0   0   1 |
	
	Mat33d mat33d;
};

FDK_FORGE_API   void Transform2dInit        (Transform2d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform2dRotation    (F64 angle, Transform2d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform2dTranslation (const Vec2d& FDK_RESTRICT T, Transform2d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform2dScaleVec    (const Vec2d& scale, Transform2d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform2dScale       (F64 scaleX, F64 scaleY, Transform2d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform2dShear       (F64 shX, F64 shY,  Transform2d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform2dCat         (const Transform2d& FDK_RESTRICT second, const Transform2d& FDK_RESTRICT first, Transform2d* FDK_RESTRICT outTransform);

//Transform objects

FDK_FORGE_API void Transform2dPoint     (const Transform2d& FDK_RESTRICT transf, const Point2d& point, Point2d* FDK_RESTRICT outPoint);
FDK_FORGE_API void Transform2dDirection (const Transform2d& FDK_RESTRICT transf, const Direction2d& direction, Direction2d* FDK_RESTRICT outDirection);
FDK_FORGE_API void Transform2dRay       (const Transform2d& FDK_RESTRICT transf, const Ray2d& ray, Ray2d* FDK_RESTRICT outRay);

//Transform Inplace
FDK_FORGE_API void Transform2dPointInplace (const Transform2d& FDK_RESTRICT transf, Point2d* FDK_RESTRICT outPoint);
FDK_FORGE_API void Transform2dRayInplace   (const Transform2d& FDK_RESTRICT transf, Ray2d* FDK_RESTRICT outRay);
//


FDK_NS_END

#endif
