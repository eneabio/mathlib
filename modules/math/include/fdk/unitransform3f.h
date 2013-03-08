// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_UNITRASFORM3F_H__
#define __FDK_UNITRASFORM3F_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/mathf.h"
#include "fdk/vec2f.h"
#include "fdk/quatf.h"
#include "fdk/mat33f.h"
#include "fdk/transform3f.h"


FDK_NS_BEGIN

struct UniTransform3f {
	
	UniTransform3f(F32 _scale, Vec3f& _transl, Quatf& _rot)  { scale=_scale; translation.x=_transl.x; translation.y=_transl.y; translation.z=_transl.z; rotation.qX=_rot.qX; rotation.qY=_rot.qY; rotation.qZ=_rot.qZ; rotation.qW=_rot.qW;}
	
	UniTransform3f() {}
	
	F32    scale;
	Vec3f  translation;
	Quatf  rotation;
};

FDK_FORGE_API   void  UniTransform3fInit        (const F32 s, const Vec3f& FDK_RESTRICT T, const Quatf& FDK_RESTRICT R, UniTransform3f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void  UniTransform3fRotation    (const Quatf& FDK_RESTRICT R, UniTransform3f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void  UniTransform3fTranslation (const Vec3f& FDK_RESTRICT T, UniTransform3f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void  UniTransform3fScale       (const F32 s, UniTransform3f* FDK_RESTRICT outTransform);
FDK_FORGE_API   void  UniTransform3fCat         (const UniTransform3f& FDK_RESTRICT first, const UniTransform3f& FDK_RESTRICT second, UniTransform3f* FDK_RESTRICT outTransform);

//UniTransform objects
FDK_FORGE_API void UniTransform3fPoint     (const UniTransform3f& FDK_RESTRICT transf,const Point3f& point, Point3f* FDK_RESTRICT outPoint);
FDK_FORGE_API void UniTransform3fDirection (const UniTransform3f& FDK_RESTRICT transf,const Direction3f& direction, Direction3f* FDK_RESTRICT outDirection);
FDK_FORGE_API void UniTransform3fRay       (const UniTransform3f& FDK_RESTRICT transf,const Ray3f& FDK_RESTRICT ray, Ray3f* FDK_RESTRICT outRay);
FDK_FORGE_API void UniTransform3fPlane     (const UniTransform3f& FDK_RESTRICT transf,const Plane3f& FDK_RESTRICT plane, Plane3f* FDK_RESTRICT outPlane);

FDK_NS_END

#endif
