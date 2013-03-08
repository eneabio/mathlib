// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_INTERSECTD_H__
#define __FDK_INTERSECTD_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/geometryd.h"
#include "fdk/mathd.h"

FDK_NS_BEGIN

enum FDK_INTERSERCT_RESULT {
	FDK_INTERSERCT_RESULT_INTERSECT = 2,
	FDK_INTERSERCT_RESULT_IN = 1,
	FDK_INTERSERCT_RESULT_OUT = 0
};

//  ::::: UTILITIES :::::

bool IsZerod(double val, double toll = FDK_F64_EPSILON);
bool IsAABB2dIncludedInOther(const AABB2d& a, const AABB2d& b);
bool IsAABB3dIncludedInOther(const AABB3d& a, const AABB3d& b);

//  ::::: Ray - Triangle ::::::

bool IntersectRayTriangle3d(const Ray3d& ray, const Triangle3d& tr);


// ::::: Ray - AABB3d ::::::

//without point of intersection and distance
bool IntersectRayAABB3d(const Ray3d& ray, const AABB3d& aabb);
bool IntersectRayAABB3d(const Point3d& pt, const Direction3d& dir, const Point3d& boxCenter, const Vec3d& halfW );

//with distance and point of intersection
//bool IntersectRayAABB3d( const Ray3d& ray, const AABB3d& aabb, F64& tmin, Point3d& q );
//bool IntersectRayAABB3d( const Point3d& rayOrig, const Direction3d& rayDir, const Point3d& boxCenter, const Vec3d& halfW, F64& tmin, Point3d& q );


// ::::: Ray - OBB3d ::::::

bool IntersectRayOBB3d(const Ray3d& ray, const OBB3d& obb);

//  ::::: Ray - Sphered ::::::

bool IntersectRaySphered( const Ray3d& ray, const Sphered& sphere, F64& t, Point3d& q );
bool IntersectRaySphered( const Point3d& origin, const Direction3d& direction, const Point3d& centerSph, F64 radius, F64& t, Point3d& q );


// ::::: AABB - OBB3d ::::::

bool IntersectAABBOBB3d(...);

// ::::: AABB - AABB3d ::::::

bool IntersectAABBAABB3d(const AABB3d& aabb1, const AABB3d& aabb2);
bool IntersectAABBAABB3d(const Point3d& c1, const Vec3d& halfW1, const Point3d& c2, const Vec3d& halfW2);

// ::::: Sphered - Sphered ::::::

bool IntersectSpheredSphered(const Sphered& sphere1, const Sphered& sphere2);
bool IntersectSpheredSphered(const Point3d center1, F64 radius1, const Point3d center2, F64 radius2);

//  ::::: Plane - AABB ::::::

bool IntersectPlaneAABB3d( const Plane3d& plane, const AABB3d& aabb);

// tests if a sphere is within the frustrum
FDK_INTERSERCT_RESULT FrustumContainsSphered(const Plane3d* plane, const Sphered& refSphered);


//Intersections:

//Ray (Plane, Sphered, AABB)
//AABB (AABB, Sphered, Cone)
//

FDK_NS_END

#endif
