// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_TRASFORM2F_H__
#define __FDK_TRASFORM2F_H__

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

struct Transform2f {
	
	Transform2f(Mat22f& _matRotation, Vec2f& _transfXY)  { mat33f.v00=_matRotation.v00; mat33f.v01=_matRotation.v01; mat33f.v02=_transfXY.x; mat33f.v10=_matRotation.v10; mat33f.v11=_matRotation.v11; mat33f.v12=_transfXY.y; mat33f.v20=0.f; mat33f.v21=0.f; mat33f.v22=1.f; }
	
	Transform2f(Mat33f& _mat) { mat33f.v00=_mat.v00; mat33f.v01=_mat.v01; mat33f.v02=_mat.v02; mat33f.v10=_mat.v10; mat33f.v11=_mat.v11, mat33f.v12=_mat.v12; mat33f.v20=_mat.v20; mat33f.v21=_mat.v21, mat33f.v22=_mat.v22; }
	
	Transform2f() {}
	
	//transform2f = | R00 R01 Tx |
	//              | R10 R11 Ty |
	//              |  0   0   1 |
	
	Mat33f mat33f;
};

FDK_FORGE_API   void Transform2fInit        (Transform2f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform2fRotation    (F32 angle, Transform2f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform2fTranslation (const Vec2f& FDK_RESTRICT T, Transform2f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform2fScaleVec    (const Vec2f& scale, Transform2f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform2fScale       (F32 scaleX, F32 scaleY, Transform2f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform2fShear       (F32 shX, F32 shY,  Transform2f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void Transform2fCat         (const Transform2f& FDK_RESTRICT second, const Transform2f& FDK_RESTRICT first, Transform2f* FDK_RESTRICT outTransform);

//Transform objects

FDK_FORGE_API void Transform2fPoint     (const Transform2f& FDK_RESTRICT transf, const Point2f& point, Point2f* FDK_RESTRICT outPoint);
FDK_FORGE_API void Transform2fDirection (const Transform2f& FDK_RESTRICT transf, const Direction2f& direction, Direction2f* FDK_RESTRICT outDirection);
FDK_FORGE_API void Transform2fRay       (const Transform2f& FDK_RESTRICT transf, const Ray2f& ray, Ray2f* FDK_RESTRICT outRay);

//Transform Inplace
FDK_FORGE_API void Transform2fPointInplace (const Transform2f& FDK_RESTRICT transf, Point2f* FDK_RESTRICT outPoint);
FDK_FORGE_API void Transform2fRayInplace   (const Transform2f& FDK_RESTRICT transf, Ray2f* FDK_RESTRICT outRay);
//


FDK_NS_END

#endif
