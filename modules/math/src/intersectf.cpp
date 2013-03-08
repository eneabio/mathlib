// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/intersectf.h"


FDK_NS_BEGIN

//  ::::: UTILITIES :::::

bool IsZerof(F32 val, F32 toll) {
	if (Absf(val) < toll)
		return true;
	return false;
}

bool IsAABB2fIncludedInOther(const AABB2f& a, const AABB2f& b) {
	// TODO
	FDK_UNUSED(a);
	FDK_UNUSED(b);
	return false;
}

bool IsAABB3fIncludedInOther(const AABB3f& a, const AABB3f& b) {
	// TODO
	FDK_UNUSED(a);
	FDK_UNUSED(b);
	return false;
}

//  ::::: Ray - Triangle ::::::

bool IntersectRayTriangle3f(const Ray3f& ray, const Triangle3f& tr) {
	
	//reference: Essential Mathematics for Games and Interactive pag. 585
	
	// test ray direction against triangle
	//triangle' s point: v1=a,v0=b,v2=c
	
	Vec3f v0 = Vec3f(tr.b.point.x, tr.b.point.y, tr.b.point.z);
	Vec3f v1 = Vec3f(tr.a.point.x, tr.a.point.y, tr.a.point.z);
	Vec3f v2 = Vec3f(tr.c.point.x, tr.c.point.y, tr.c.point.z);
	
	//e1 = v1 - v0;
	Vec3f e1;
	Vec3fSub(v1, v0, &e1);
	
	//e2 = v2 - v0;
	Vec3f e2;
	Vec3fSub(v2, v0, &e2);
	
	//p = ray.mDirection.Cross(e2);
	Vec3f p;
	Vec3fCross(ray.direction.dir, e2, &p);
	
	//float a = e1.Dot(p);
	F32 a = Vec3fDot(e1, p);
	
	// if result zero, no intersection or infinite intersections
	// (ray parallel to triangle plane)
	//if ( IsZerof(a) )
	if (IsZerof(a))
		return false;
	
	// compute denominator
	F32 f = 1.0f/a;
	
	// compute barycentric coordinates
	//IvVector3 s = ray.mOrigin - v0;
	Vec3f s;
	Vec3f mOrigin = Vec3f(ray.origin.point.x, ray.origin.point.y, ray.origin.point.z);
	Vec3fSub(mOrigin, v0, &s);
	
	//u = f*s.Dot(p)
	F32 u = f * Vec3fDot(s, p);
	if (u < 0.0f || u > 1.0f)
		return false;
	
	//q = s.Cross(e1);
	Vec3f q;
	Vec3fCross(s, e1, &q);
	
	//v = f*ray.mDirection.Dot(q);
	F32 v = f * Vec3fDot(ray.direction.dir, q);
	if (v < 0.0f || u+v > 1.0f)
		return false;
	
	// compute line parameter
	//t = f*e2.Dot(q);
	F32 t = f * Vec3fDot(e2, q);
	
	return (t >= 0.0f);
}

// ::::: Ray - OBB3f ::::::

//to do: try this...
bool IntersectRayOBB3f(const Ray3f& ray, const OBB3f& obb) {
	//intersect ray-obb reference: http://www.geometrictools.com/LibMathematics/Intersection/Intersection.html intersect box ray
	
//bool IntrRay3Box3<Real>::Test ()
//{
	//Real WdU[3], AWdU[3], DdU[3], ADdU[3], AWxDdU[3], RHS;
	F32 WdU[3], AWdU[3], DdU[3], ADdU[3], AWxDdU[3], RHS;
	
	//Vector3<Real> diff = mRay->Origin - mBox->Center;
	Vec3f diff;
	Vec3fSub(ray.origin.point, obb.center.point, &diff);
	
	//WdU[0] = mRay->Direction.Dot(mBox->Axis[0]);
	WdU[0] = Vec3fDot(ray.direction.dir, obb.orientX);
	
	//AWdU[0] = Math<Real>::FAbs(WdU[0]);
	AWdU[0] = Absf(WdU[0]);
	
	//DdU[0] = diff.Dot(mBox->Axis[0]);
	DdU[0] = Vec3fDot(diff, obb.orientX);
	
	//ADdU[0] = Math<Real>::FAbs(DdU[0]);
	ADdU[0] = Absf(DdU[0]);
	
	//if (ADdU[0] > mBox->Extent[0] && DdU[0]*WdU[0] >= (Real)0)
	if ( ADdU[0] > obb.halfWidths.x && DdU[0]*WdU[0] >= 0.f) {
		return false;
	}
	
	//WdU[1] = mRay->Direction.Dot(mBox->Axis[1]);
	WdU[1] = Vec3fDot(ray.direction.dir, obb.orientY);
	
	//AWdU[1] = Math<Real>::FAbs(WdU[1]);
	AWdU[1] = Absf(WdU[1]);
	
	//DdU[1] = diff.Dot(mBox->Axis[1]);
	DdU[1] = Vec3fDot(diff, obb.orientY);
	
	//ADdU[1] = Math<Real>::FAbs(DdU[1]);
	ADdU[1] = Absf(DdU[1]);
	
	//if (ADdU[1] > mBox->Extent[1] && DdU[1]*WdU[1] >= (Real)0)
	if ( ADdU[1] > obb.halfWidths.y && DdU[1]*WdU[1] >= 0.f) {
		return false;
	}
	
	//WdU[2] = mRay->Direction.Dot(mBox->Axis[2]);
	WdU[2] = Vec3fDot(ray.direction.dir, obb.orientZ);
		
	//AWdU[2] = Math<Real>::FAbs(WdU[2]);
	AWdU[2] = Absf(WdU[2]);
		
	//DdU[2] = diff.Dot(mBox->Axis[2]);
	DdU[2] = Vec3fDot(diff, obb.orientZ);
		
	//ADdU[2] = Math<Real>::FAbs(DdU[2]);
	ADdU[2] = Absf(DdU[2]);
		
	//if (ADdU[2] > mBox->Extent[2] && DdU[2]*WdU[2] >= (Real)0)
	if ( ADdU[2] > obb.halfWidths.z && DdU[2]*WdU[2] >= 0.f) {
		return false;
	}
	
	//Vector3<Real> WxD = mRay->Direction.Cross(diff);
	Vec3f WxD;
	Vec3fCross(ray.direction.dir, diff, &WxD);
	
	//AWxDdU[0] = Math<Real>::FAbs(WxD.Dot(mBox->Axis[0]));
	AWxDdU[0] = Absf(Vec3fDot(WxD, obb.orientX));
	
	//RHS = mBox->Extent[1]*AWdU[2] + mBox->Extent[2]*AWdU[1];
	RHS = obb.halfWidths.y * AWdU[2] + obb.halfWidths.z * AWdU[1];
	
	if (AWxDdU[0] > RHS)
	{
		return false;
	}
	
	//AWxDdU[1] = Math<Real>::FAbs(WxD.Dot(mBox->Axis[1]));
	AWxDdU[1] = Absf(Vec3fDot(WxD, obb.orientY));
	
	//RHS = mBox->Extent[0]*AWdU[2] + mBox->Extent[2]*AWdU[0];
	RHS = obb.halfWidths.x * AWdU[2] + obb.halfWidths.z * AWdU[0];
	
	if (AWxDdU[1] > RHS)
	{
		return false;
	}
	
	//AWxDdU[2] = Math<Real>::FAbs(WxD.Dot(mBox->Axis[2]));
	AWxDdU[2] = Absf(Vec3fDot(WxD, obb.orientZ));
	
	//RHS = mBox->Extent[0]*AWdU[1] + mBox->Extent[1]*AWdU[0];
	RHS = obb.halfWidths.x * AWdU[1] + obb.halfWidths.y * AWdU[0];
	
	if (AWxDdU[2] > RHS)
	{
		return false;
	}
	
	return true;
}

// ::::: Ray - Spheref ::::::

bool IntersectRaySpheref( const Ray3f& ray, const Spheref& sphere, F32& t, Point3f& q ) {
	return IntersectRaySpheref( ray.origin, ray.direction, sphere.center, sphere.radius, t, q );
}

bool IntersectRaySpheref( const Point3f& origin, const Direction3f& direction, const Point3f& centerSph, F32 radius, F32& t, Point3f& q ) {
	Vec3f m;
	Vec3fSub( origin.point , centerSph.point, &m );
	F32 b = Vec3fDot( m , direction.dir );
	F32 c = Vec3fDot( m , m ) - radius * radius;
	// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
	if(c > 0.f &&  b > 0.f)
		return false;
	F32 discr = b * b - c;
	// A negative discriminant corresponds to ray missing sphere
	if (discr < 0.f)
		return false;
	// Ray now found to intersect sphere, compute smallest t value of intersection
	t = -b - Sqrtf(discr);
	// If t is negative, ray started inside sphere so clamp t to zero
	if (t < 0.f)
		t = 0.f;
	Vec3f tempRes = direction.dir;
	Vec3fMultScalarInplace( t , &tempRes );
	Vec3fSumInplace( origin.point , &tempRes );
	q.point = tempRes;
	return true;
}

// ::::: Ray - AABB3f ::::::

bool IntersectRayAABB3f( const Ray3f& ray, const AABB3f& aabb) {
	return IntersectRayAABB3f(ray.origin, ray.direction, aabb.center, aabb.halfWidths);
}

bool IntersectRayAABB3f( const Point3f& rayOrig, const Direction3f& rayDir, const Point3f& boxCenter, const Vec3f& halfW) {
	//reference: Essential Mathematics for Games and Interactive pag. 569
	
	F32 maxS = 0.0f;   // for line, use -FLT_MAX
        F32 minT = FDK_F32_MAX;   // for line segment, use length
        
	Point3f mMin;
	Point3f mMax;
	AABBFindMinMax3f(boxCenter, halfW, mMin, mMax);
	
	// do x coordinate test (yz planes)
        
	F32 s, t;
	// compute sorted intersection parameters
        //recipX = 1.0f/ray.mDirection.x;
        F32 recipX = 1.0f/rayDir.dir.x;
	
	if ( recipX >= 0.0f )
        {
		//s = (mMin.x - ray.mOrigin.x)*recipX;
		s = (mMin.point.x - rayOrig.point.x) * recipX;
		
		//t = (mMax.x - ray.mOrigin.x)*recipX;
		t = (mMax.point.x - rayOrig.point.x) * recipX;
		     
	} else {
		//s = (mMax.x - ray.mOrigin.x)*recipX;
		s = (mMax.point.x - rayOrig.point.x) * recipX;
		
		//t = (mMin.x - ray.mOrigin.x)*recipX;
		t = (mMin.point.x - rayOrig.point.x) * recipX;
        }
        // adjust min and max values
        if ( s > maxS )
		maxS = s;
        if ( t < minT )
		minT = t;
        // check for intersection failure
        if ( maxS > minT )
		return false;
        
	// do y coordinate test (xz planes)
	// compute sorted intersection parameters
        F32 recipY = 1.0f/rayDir.dir.y;
	
	if ( recipY >= 0.0f )
        {
		s = (mMin.point.y - rayOrig.point.y) * recipY;
		
		t = (mMax.point.y - rayOrig.point.y) * recipY;
		
	} else {
		s = (mMax.point.y - rayOrig.point.y) * recipY;
		
		t = (mMin.point.y - rayOrig.point.y) * recipY;
        }
        // adjust min and max values
        if ( s > maxS )
		maxS = s;
        if ( t < minT )
		minT = t;
        // check for intersection failure
        if ( maxS > minT )
		return false;
	
	// do z coordinate test (xy planes)
	F32 recipZ = 1.0f/rayDir.dir.z;
	
	if ( recipZ >= 0.0f )
        {
		s = (mMin.point.z - rayOrig.point.z) * recipZ;
		
		t = (mMax.point.z - rayOrig.point.z) * recipZ;
		
	} else {
		s = (mMax.point.z - rayOrig.point.z) * recipZ;
		
		t = (mMin.point.z - rayOrig.point.z) * recipZ;
        }
        // adjust min and max values
        if ( s > maxS )
		maxS = s;
        if ( t < minT )
		minT = t;
        // check for intersection failure
        if ( maxS > minT )
		return false;
        // done, have intersection
        return true;

}


// ::::: AABB3f - AABB3f ::::::

bool IntersectAABBAABB3f(const AABB3f& aabb1, const AABB3f& aabb2) {
	return IntersectAABBAABB3f(
		aabb1.center, 
		aabb1.halfWidths, 
		aabb2.center, 
		aabb2.halfWidths);
}

bool IntersectAABBAABB3f(const Point3f& c1, const Vec3f& halfW1, const Point3f& c2, const Vec3f& halfW2) {
	if ( Absf(c1.point.x - c2.point.x) > (halfW1.x + halfW2.x) ) return false;
	if ( Absf(c1.point.y - c2.point.y) > (halfW1.y + halfW2.y) ) return false;
	if ( Absf(c1.point.z - c2.point.z) > (halfW1.z + halfW2.z) ) return false;
	return true;
}


// ::::: Spheref - Spheref ::::::

bool IntersectSpherefSpheref(const Spheref& sphere1, const Spheref& sphere2) {
	return IntersectSpherefSpheref(sphere1.center, sphere1.radius, sphere2.center, sphere2.radius);
}

bool IntersectSpherefSpheref(const Point3f center1, F32 radius1, const Point3f center2, F32 radius2) {
	Vec3f d;
	Vec3fSub(center1.point, center2.point, &d);
	F32 dist2;
	dist2 = Vec3fDot(d,d);
	//intersect if squared distance is less than squared sum of radius
	F32 radiusSum = radius1 + radius2;
	return dist2 <= radiusSum * radiusSum;
}

//  ::::: Plane - AABB ::::::

bool IntersectPlaneAABB3f( const Plane3f& p, const AABB3f& b) {
	// Test if AABB b intersects plane p
	//reference pag. 161 Real time collision detection
	//int TestAABBPlane(AABB b, Plane p)
	// These two lines not necessary with a (center, extents) AABB representation Point c = (b.max + b.min) * 0.5f; // Compute AABB center
	
	//Point e = b.max - c; // Compute positive extents
	Point3f min;
	Point3f max;
	AABBFindMinMax3f(b, min, max);
	Point3f e;
	e.point.x = max.point.x - b.center.point.x;
	e.point.y = max.point.y - b.center.point.y;
	e.point.z = max.point.z - b.center.point.z;
	
	// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
	//float r = e[0]*Abs(p.n[0]) + e[1]*Abs(p.n[1]) + e[2]*Abs(p.n[2]);
	F32 r = e.point.x * Fabsf(p.norm.dir.dir.x) + e.point.y * Fabsf(p.norm.dir.dir.y) + e.point.z * Fabsf(p.norm.dir.dir.z);
	
	// Compute distance of box center from plane
	//float s = Dot(p.n, c) - p.d;
	F32 s = Vec3fDot(p.norm.dir.dir, b.center.point);
	s = s - p.d ;
	
	// Intersection occurs when distance s falls within [-r,+r] interval
	//return Abs(s) <= r;
	F32 abS = Fabsf(s);
	if (abS <= r )
		return true;
	else
		return false;
}

// tests if a sphere is within the frustrum
FDK_INTERSERCT_RESULT FrustumContainsSpheref(const Plane3f* plane, const Spheref& refSpheref) {
	//C = center of sphere
	//N = normal of plane
	//D = distance of plane along normal from origin
	
	//Distance = DotProduct(C, N) + D
	
	// various distances
	float fDistance;
	
	// calculate our distances to each of the planes
	for(int i = 0; i < 6; ++i) {
		
		// find the distance to this plane
		fDistance = Vec3fDot(plane[i].norm.dir.dir, refSpheref.center.point) + plane[i].d;
		
		// if this distance is < -sphere.radius, we are outside
		if(fDistance < -refSpheref.radius)
			return(FDK_INTERSERCT_RESULT_OUT);
		
		// else if the distance is between +- radius, then we intersect
		if((float)Fabsf(fDistance) < refSpheref.radius)
			return(FDK_INTERSERCT_RESULT_INTERSECT);
	}
	
	// otherwise we are fully in view
	return(FDK_INTERSERCT_RESULT_IN);
	
}
	
FDK_NS_END
