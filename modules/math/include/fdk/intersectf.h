// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_INTERSECTF_H__
#define __FDK_INTERSECTF_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/geometryf.h"
#include "fdk/mathf.h"


FDK_NS_BEGIN

enum FDK_INTERSERCT_RESULT {
	FDK_INTERSERCT_RESULT_INTERSECT = 2,
	FDK_INTERSERCT_RESULT_IN = 1,
	FDK_INTERSERCT_RESULT_OUT = 0
};

//  ::::: UTILITIES :::::

bool IsZerof(float val, float toll = FDK_F32_EPSILON);
bool IsAABB2fIncludedInOther(const AABB2f& a, const AABB2f& b);
bool IsAABB3fIncludedInOther(const AABB3f& a, const AABB3f& b);

//  ::::: Ray - Triangle ::::::

bool IntersectRayTriangle3f(const Ray3f& ray, const Triangle3f& tr);


// ::::: Ray - AABB3f ::::::

//without point of intersection and distance
bool IntersectRayAABB3f(const Ray3f& ray, const AABB3f& aabb);
bool IntersectRayAABB3f(const Point3f& pt, const Direction3f& dir, const Point3f& boxCenter, const Vec3f& halfW );

//with distance and point of intersection
//bool IntersectRayAABB3f( const Ray3f& ray, const AABB3f& aabb, F32& tmin, Point3f& q );
//bool IntersectRayAABB3f( const Point3f& rayOrig, const Direction3f& rayDir, const Point3f& boxCenter, const Vec3f& halfW, F32& tmin, Point3f& q );


// ::::: Ray - OBB3f ::::::

bool IntersectRayOBB3f(const Ray3f& ray, const OBB3f& obb);

//  ::::: Ray - Spheref ::::::

bool IntersectRaySpheref( const Ray3f& ray, const Spheref& sphere, F32& t, Point3f& q );
bool IntersectRaySpheref( const Point3f& origin, const Direction3f& direction, const Point3f& centerSph, F32 radius, F32& t, Point3f& q );


// ::::: AABB - OBB3f ::::::

bool IntersectAABBOBB3f(...);

// ::::: AABB - AABB3f ::::::

bool IntersectAABBAABB3f(const AABB3f& aabb1, const AABB3f& aabb2);
bool IntersectAABBAABB3f(const Point3f& c1, const Vec3f& halfW1, const Point3f& c2, const Vec3f& halfW2);

// ::::: Spheref - Spheref ::::::

bool IntersectSpherefSpheref(const Spheref& sphere1, const Spheref& sphere2);
bool IntersectSpherefSpheref(const Point3f center1, F32 radius1, const Point3f center2, F32 radius2);

//  ::::: Plane - AABB ::::::

bool IntersectPlaneAABB3f( const Plane3f& plane, const AABB3f& aabb);

// tests if a sphere is within the frustrum
FDK_INTERSERCT_RESULT FrustumContainsSpheref(const Plane3f* plane, const Spheref& refSpheref);


//Intersections:

//Ray (Plane, Spheref, AABB)
//AABB (AABB, Spheref, Cone)
//

FDK_NS_END

#endif
