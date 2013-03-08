// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_UNITRASFORM3D_H__
#define __FDK_UNITRASFORM3D_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/mathd.h"
#include "fdk/vec2d.h"
#include "fdk/quatd.h"
#include "fdk/mat33d.h"
#include "fdk/transform3d.h"


FDK_NS_BEGIN

struct UniTransform3d {
	
	UniTransform3d(F64 _scale, Vec3d& _transl, Quatd& _rot)  { scale=_scale; translation.x=_transl.x; translation.y=_transl.y; translation.z=_transl.z; rotation.qX=_rot.qX; rotation.qY=_rot.qY; rotation.qZ=_rot.qZ; rotation.qW=_rot.qW;}
	
	UniTransform3d() {}
	
	F64    scale;
	Vec3d  translation;
	Quatd  rotation;
};

FDK_FORGE_API   void  UniTransform3dInit        (const F64 s, const Vec3d& FDK_RESTRICT T, const Quatd& FDK_RESTRICT R, UniTransform3d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void  UniTransform3dRotation    (const Quatd& FDK_RESTRICT R, UniTransform3d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void  UniTransform3dTranslation (const Vec3d& FDK_RESTRICT T, UniTransform3d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void  UniTransform3dScale       (const F64 s, UniTransform3d* FDK_RESTRICT outTransform);
FDK_FORGE_API   void  UniTransform3dCat         (const UniTransform3d& FDK_RESTRICT first, const UniTransform3d& FDK_RESTRICT second, UniTransform3d* FDK_RESTRICT outTransform);

//UniTransform objects
FDK_FORGE_API void UniTransform3dPoint     (const UniTransform3d& FDK_RESTRICT transf,const Point3d& point, Point3d* FDK_RESTRICT outPoint);
FDK_FORGE_API void UniTransform3dDirection (const UniTransform3d& FDK_RESTRICT transf,const Direction3d& direction, Direction3d* FDK_RESTRICT outDirection);
FDK_FORGE_API void UniTransform3dRay       (const UniTransform3d& FDK_RESTRICT transf,const Ray3d& FDK_RESTRICT ray, Ray3d* FDK_RESTRICT outRay);
FDK_FORGE_API void UniTransform3dPlane     (const UniTransform3d& FDK_RESTRICT transf,const Plane3d& FDK_RESTRICT plane, Plane3d* FDK_RESTRICT outPlane);

FDK_NS_END

#endif
