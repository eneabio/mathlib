// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/intersectd.h"


FDK_NS_BEGIN

//  ::::: UTILITIES :::::

bool IsZerod(F64 val, F64 toll) {
	if (Absd(val) < toll)
		return true;
	return false;
}

bool IsAABB2dIncludedInOther(const AABB2d& a, const AABB2d& b) {
	// TODO
	FDK_UNUSED(a);
	FDK_UNUSED(b);
	return false;
}

bool IsAABB3dIncludedInOther(const AABB3d& a, const AABB3d& b) {
	// TODO
	FDK_UNUSED(a);
	FDK_UNUSED(b);
	return false;
}

//  ::::: Ray - Triangle ::::::

bool IntersectRayTriangle3d(const Ray3d& ray, const Triangle3d& tr) {
	
	//reference: Essential Mathematics for Games and Interactive pag. 585
	
	// test ray direction against triangle
	//triangle' s point: v1=a,v0=b,v2=c
	
	Vec3d v0 = Vec3d(tr.b.point.x, tr.b.point.y, tr.b.point.z);
	Vec3d v1 = Vec3d(tr.a.point.x, tr.a.point.y, tr.a.point.z);
	Vec3d v2 = Vec3d(tr.c.point.x, tr.c.point.y, tr.c.point.z);
	
	//e1 = v1 - v0;
	Vec3d e1;
	Vec3dSub(v1, v0, &e1);
	
	//e2 = v2 - v0;
	Vec3d e2;
	Vec3dSub(v2, v0, &e2);
	
	//p = ray.mDirection.Cross(e2);
	Vec3d p;
	Vec3dCross(ray.direction.dir, e2, &p);
	
	//float a = e1.Dot(p);
	F64 a = Vec3dDot(e1, p);
	
	// if result zero, no intersection or infinite intersections
	// (ray parallel to triangle plane)
	//if ( IsZerod(a) )
	if (IsZerod(a))
		return false;
	
	// compute denominator
	F64 f = 1.0/a;
	
	// compute barycentric coordinates
	//IvVector3 s = ray.mOrigin - v0;
	Vec3d s;
	Vec3d mOrigin = Vec3d(ray.origin.point.x, ray.origin.point.y, ray.origin.point.z);
	Vec3dSub(mOrigin, v0, &s);
	
	//u = f*s.Dot(p)
	F64 u = f * Vec3dDot(s, p);
	if (u < 0.0 || u > 1.0)
		return false;
	
	//q = s.Cross(e1);
	Vec3d q;
	Vec3dCross(s, e1, &q);
	
	//v = f*ray.mDirection.Dot(q);
	F64 v = f * Vec3dDot(ray.direction.dir, q);
	if (v < 0.0 || u+v > 1.0)
		return false;
	
	// compute line parameter
	//t = f*e2.Dot(q);
	F64 t = f * Vec3dDot(e2, q);
	
	return (t >= 0.0);
}

// ::::: Ray - OBB3d ::::::

//to do: try this...
bool IntersectRayOBB3d(const Ray3d& ray, const OBB3d& obb) {
	//intersect ray-obb reference: http://www.geometrictools.com/LibMathematics/Intersection/Intersection.html intersect box ray
	
	//bool IntrRay3Box3<Real>::Test ()
	//{
	//Real WdU[3], AWdU[3], DdU[3], ADdU[3], AWxDdU[3], RHS;
	F64 WdU[3], AWdU[3], DdU[3], ADdU[3], AWxDdU[3], RHS;
	
	//Vector3<Real> diff = mRay->Origin - mBox->Center;
	Vec3d diff;
	Vec3dSub(ray.origin.point, obb.center.point, &diff);
	
	//WdU[0] = mRay->Direction.Dot(mBox->Axis[0]);
	WdU[0] = Vec3dDot(ray.direction.dir, obb.orientX);
	
	//AWdU[0] = Math<Real>::FAbs(WdU[0]);
	AWdU[0] = Absd(WdU[0]);
	
	//DdU[0] = diff.Dot(mBox->Axis[0]);
	DdU[0] = Vec3dDot(diff, obb.orientX);
	
	//ADdU[0] = Math<Real>::FAbs(DdU[0]);
	ADdU[0] = Absd(DdU[0]);
	
	//if (ADdU[0] > mBox->Extent[0] && DdU[0]*WdU[0] >= (Real)0)
	if ( ADdU[0] > obb.halfWidths.x && DdU[0]*WdU[0] >= 0.0) {
		return false;
	}
	
	//WdU[1] = mRay->Direction.Dot(mBox->Axis[1]);
	WdU[1] = Vec3dDot(ray.direction.dir, obb.orientY);
	
	//AWdU[1] = Math<Real>::FAbs(WdU[1]);
	AWdU[1] = Absd(WdU[1]);
	
	//DdU[1] = diff.Dot(mBox->Axis[1]);
	DdU[1] = Vec3dDot(diff, obb.orientY);
	
	//ADdU[1] = Math<Real>::FAbs(DdU[1]);
	ADdU[1] = Absd(DdU[1]);
	
	//if (ADdU[1] > mBox->Extent[1] && DdU[1]*WdU[1] >= (Real)0)
	if ( ADdU[1] > obb.halfWidths.y && DdU[1]*WdU[1] >= 0.0) {
		return false;
	}
	
	//WdU[2] = mRay->Direction.Dot(mBox->Axis[2]);
	WdU[2] = Vec3dDot(ray.direction.dir, obb.orientZ);
	
	//AWdU[2] = Math<Real>::FAbs(WdU[2]);
	AWdU[2] = Absd(WdU[2]);
	
	//DdU[2] = diff.Dot(mBox->Axis[2]);
	DdU[2] = Vec3dDot(diff, obb.orientZ);
	
	//ADdU[2] = Math<Real>::FAbs(DdU[2]);
	ADdU[2] = Absd(DdU[2]);
	
	//if (ADdU[2] > mBox->Extent[2] && DdU[2]*WdU[2] >= (Real)0)
	if ( ADdU[2] > obb.halfWidths.z && DdU[2]*WdU[2] >= 0.0) {
		return false;
	}
	
	//Vector3<Real> WxD = mRay->Direction.Cross(diff);
	Vec3d WxD;
	Vec3dCross(ray.direction.dir, diff, &WxD);
	
	//AWxDdU[0] = Math<Real>::FAbs(WxD.Dot(mBox->Axis[0]));
	AWxDdU[0] = Absd(Vec3dDot(WxD, obb.orientX));
	
	//RHS = mBox->Extent[1]*AWdU[2] + mBox->Extent[2]*AWdU[1];
	RHS = obb.halfWidths.y * AWdU[2] + obb.halfWidths.z * AWdU[1];
	
	if (AWxDdU[0] > RHS)
	{
		return false;
	}
	
	//AWxDdU[1] = Math<Real>::FAbs(WxD.Dot(mBox->Axis[1]));
	AWxDdU[1] = Absd(Vec3dDot(WxD, obb.orientY));
	
	//RHS = mBox->Extent[0]*AWdU[2] + mBox->Extent[2]*AWdU[0];
	RHS = obb.halfWidths.x * AWdU[2] + obb.halfWidths.z * AWdU[0];
	
	if (AWxDdU[1] > RHS)
	{
		return false;
	}
	
	//AWxDdU[2] = Math<Real>::FAbs(WxD.Dot(mBox->Axis[2]));
	AWxDdU[2] = Absd(Vec3dDot(WxD, obb.orientZ));
	
	//RHS = mBox->Extent[0]*AWdU[1] + mBox->Extent[1]*AWdU[0];
	RHS = obb.halfWidths.x * AWdU[1] + obb.halfWidths.y * AWdU[0];
	
	if (AWxDdU[2] > RHS)
	{
		return false;
	}
	
	return true;
}

// ::::: Ray - Sphered ::::::

bool IntersectRaySphered( const Ray3d& ray, const Sphered& sphere, F64& t, Point3d& q ) {
	return IntersectRaySphered( ray.origin, ray.direction, sphere.center, sphere.radius, t, q );
}

bool IntersectRaySphered( const Point3d& origin, const Direction3d& direction, const Point3d& centerSph, F64 radius, F64& t, Point3d& q ) {
	Vec3d m;
	Vec3dSub( origin.point , centerSph.point, &m );
	F64 b = Vec3dDot( m , direction.dir );
	F64 c = Vec3dDot( m , m ) - radius * radius;
	// Exit if rís origin outside s (c > 0) and r pointing away from s (b > 0)
	if(c > 0.0 &&  b > 0.0)
		return false;
	F64 discr = b * b - c;
	// A negative discriminant corresponds to ray missing sphere
	if (discr < 0.0)
		return false;
	// Ray now found to intersect sphere, compute smallest t value of intersection
	t = -b - Sqrtd(discr);
	// If t is negative, ray started inside sphere so clamp t to zero
	if (t < 0.0)
		t = 0.0;
	Vec3d tempRes = direction.dir;
	Vec3dMultScalarInplace( t , &tempRes );
	Vec3dSumInplace( origin.point , &tempRes );
	q.point = tempRes;
	return true;
}

// ::::: Ray - AABB3d ::::::

bool IntersectRayAABB3d( const Ray3d& ray, const AABB3d& aabb) {
	return IntersectRayAABB3d(ray.origin, ray.direction, aabb.center, aabb.halfWidths);
}

bool IntersectRayAABB3d( const Point3d& rayOrig, const Direction3d& rayDir, const Point3d& boxCenter, const Vec3d& halfW) {
	//reference: Essential Mathematics for Games and Interactive pag. 569
	
	F64 maxS = 0.0;   // for line, use -FLT_MAX
        F64 minT = FDK_F64_MAX;   // for line segment, use length
        
	Point3d mMin;
	Point3d mMax;
	AABBFindMinMax3d(boxCenter, halfW, mMin, mMax);
	
	// do x coordinate test (yz planes)
        
	F64 s, t;
	// compute sorted intersection parameters
        //recipX = 1.0f/ray.mDirection.x;
        F64 recipX = 1.0/rayDir.dir.x;
	
	if ( recipX >= 0.0 )
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
        F64 recipY = 1.0/rayDir.dir.y;
	
	if ( recipY >= 0.0 )
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
	F64 recipZ = 1.0/rayDir.dir.z;
	
	if ( recipZ >= 0.0 )
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


// ::::: AABB3d - AABB3d ::::::

bool IntersectAABBAABB3d(const AABB3d& aabb1, const AABB3d& aabb2) {
	return IntersectAABBAABB3d(
				   aabb1.center,
				   aabb1.halfWidths,
				   aabb2.center,
				   aabb2.halfWidths);
}

bool IntersectAABBAABB3d(const Point3d& c1, const Vec3d& halfW1, const Point3d& c2, const Vec3d& halfW2) {
	if ( Absd(c1.point.x - c2.point.x) > (halfW1.x + halfW2.x) ) return false;
	if ( Absd(c1.point.y - c2.point.y) > (halfW1.y + halfW2.y) ) return false;
	if ( Absd(c1.point.z - c2.point.z) > (halfW1.z + halfW2.z) ) return false;
	return true;
}


// ::::: Sphered - Sphered ::::::

bool IntersectSpheredSphered(const Sphered& sphere1, const Sphered& sphere2) {
	return IntersectSpheredSphered(sphere1.center, sphere1.radius, sphere2.center, sphere2.radius);
}

bool IntersectSpheredSphered(const Point3d center1, F64 radius1, const Point3d center2, F64 radius2) {
	Vec3d d;
	Vec3dSub(center1.point, center2.point, &d);
	F64 dist2;
	dist2 = Vec3dDot(d,d);
	//intersect if squared distance is less than squared sum of radius
	F64 radiusSum = radius1 + radius2;
	return dist2 <= radiusSum * radiusSum;
}

//  ::::: Plane - AABB ::::::

bool IntersectPlaneAABB3d( const Plane3d& p, const AABB3d& b) {
	// Test if AABB b intersects plane p
	//reference pag. 161 Real time collision detection
	//int TestAABBPlane(AABB b, Plane p)
	// These two lines not necessary with a (center, extents) AABB representation Point c = (b.max + b.min) * 0.5; // Compute AABB center
	
	//Point e = b.max - c; // Compute positive extents
	Point3d min;
	Point3d max;
	AABBFindMinMax3d(b, min, max);
	Point3d e;
	e.point.x = max.point.x - b.center.point.x;
	e.point.y = max.point.y - b.center.point.y;
	e.point.z = max.point.z - b.center.point.z;
	
	// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
	//float r = e[0]*Abs(p.n[0]) + e[1]*Abs(p.n[1]) + e[2]*Abs(p.n[2]);
	F64 r = e.point.x * Fabsd(p.norm.dir.dir.x) + e.point.y * Fabsd(p.norm.dir.dir.y) + e.point.z * Fabsd(p.norm.dir.dir.z);
	
	// Compute distance of box center from plane
	//float s = Dot(p.n, c) - p.d;
	F64 s = Vec3dDot(p.norm.dir.dir, b.center.point);
	s = s - p.d ;
	
	// Intersection occurs when distance s falls within [-r,+r] interval
	//return Abs(s) <= r;
	F64 abS = Fabsd(s);
	if (abS <= r )
		return true;
	else
		return false;
}

// tests if a sphere is within the frustrum
FDK_INTERSERCT_RESULT FrustumContainsSphered(const Plane3d* plane, const Sphered& refSphered) {
	//C = center of sphere
	//N = normal of plane
	//D = distance of plane along normal from origin
	
	//Distance = DotProduct(C, N) + D
	
	// various distances
	F64 fDistance;
	
	// calculate our distances to each of the planes
	for(int i = 0; i < 6; ++i) {
		
		// find the distance to this plane
		fDistance = Vec3dDot(plane[i].norm.dir.dir, refSphered.center.point) + plane[i].d;
		
		// if this distance is < -sphere.radius, we are outside
		if(fDistance < -refSphered.radius)
			return(FDK_INTERSERCT_RESULT_OUT);
		
		// else if the distance is between +- radius, then we intersect
		if((float)Fabsd(fDistance) < refSphered.radius)
			return(FDK_INTERSERCT_RESULT_INTERSECT);
	}
	
	// otherwise we are fully in view
	return(FDK_INTERSERCT_RESULT_IN);
	
}

FDK_NS_END
