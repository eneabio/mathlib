// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_GEOMETRYF_H__
#define __FDK_GEOMETRYF_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/mathf.h"
#include "fdk/vec2f.h"
#include "fdk/vec3f.h"
#include "fdk/mat44f.h"


FDK_NS_BEGIN

// ::::: POINT ::::::

struct Point2f {
	Point2f(F32 _x, F32 _y) { point.x=_x; point.y=_y; }
	Point2f(const Vec2f& _vec) {point.x=_vec.x; point.y=_vec.y; }
	Point2f() {}
	
	Vec2f point;
};

struct Point3f {
	
	Point3f(const Vec3f& _vec) {point.x=_vec.x; point.y=_vec.y; point.z=_vec.z; }
	Point3f(F32 _x,F32 _y,F32 _z) {point.x=_x; point.y=_y; point.z=_z;}
	Point3f() {}
	
	F32& operator()(int index) {
	//assert
		return ((F32*)this)[index];
	}
	const F32& operator()(int index) const {
	//assert
		return ((F32*)this)[index];
	}
	
	Vec3f point;
};

void Point2fInit(Point2f* outPoint);
void Point3fInit(Point3f* outPoint);

void Point2fInitWithVector(const Vec2f& vec, Point2f* outPoint);
void Point3fInitWithVector( const Vec3f& vec, Point3f* outPoint);

void PointInitWithValues2f( F32 x, F32 y, Point2f* outPoint);
void PointInitWithValues3f( F32 x, F32 y, F32 z, Point3f* outPoint);

// ::::: DIRECTION ::::::

struct Direction2f {
	
	Direction2f(const Vec2f& _dir) {dir.x=_dir.x; dir.y=_dir.y; }
	Direction2f() {}
	
	Vec2f dir;
};

struct Direction3f {
	
	Direction3f(const Vec3f& _dir) {dir.x=_dir.x; dir.y=_dir.y; dir.z=_dir.z; }
	Direction3f() {}
	
	// fare con quaternione
	Vec3f dir;
};

void Direction2fInitWithVector(const Vec2f vec, Direction2f* outDirection);
void Direction3fInitWithVector(const Vec3f vec, Direction3f* outDirection);

// ::::: SEGMENT ::::::

struct Segment2f {
	
	Segment2f(const Point2f& _a, const Point2f& _b ) {a.point.x=_a.point.x; a.point.y=_a.point.y; b.point.x=_b.point.x; b.point.y=_b.point.y; }
	Segment2f() {}
	
	Point2f a;
	Point2f b;
};

struct Segment3f {
	
	Segment3f(const Point3f& _a, const Point3f& _b ) {a.point.x=_a.point.x; a.point.y=_a.point.y; a.point.z=_a.point.z; b.point.x=_b.point.x; b.point.y=_b.point.y; b.point.z=_b.point.z; }
	Segment3f() {}
	
	Point3f a;
	Point3f b;
};

void SegmentInitWithPoints2f(const Point2f& pt1, const Point2f& pt2, Segment2f* outSegment);
void SegmentInitWithPoints3f(const Point3f& pt1, const Point3f& pt2, Segment3f* outSegment);

void SegmentInitWithPointVector2f(const Point2f& pt, const Vec2f& vec, Segment2f* outSegment);
void SegmentInitWithPointVector3f(const Point3f& pt, const Vec3f& vec, Segment3f* outSegment);

// ::::: NORMAL ::::::

struct Normal2f {
	
	Normal2f(const Direction2f& _dir) {dir.dir.x=_dir.dir.x; dir.dir.y=_dir.dir.y; }
	Normal2f() {}
	
	Direction2f dir;
};

struct Normal3f {
	
	Normal3f(const Direction3f& _dir) {dir.dir.x=_dir.dir.x; dir.dir.y=_dir.dir.y; dir.dir.z=_dir.dir.z; }
	Normal3f() {}
	
	Direction3f dir;
};

void NormalInit2f(const Direction2f& dir, Normal2f* outNormal);
void NormalInit3f(const Direction3f& dir, Normal3f* outNormal);

// ::::: RAY ::::::

struct Ray2f {
	
	Ray2f(const Point2f& _point, const Direction2f& _dir) {origin.point.x=_point.point.x; origin.point.y=_point.point.y; direction.dir.x=_dir.dir.x; direction.dir.y=_dir.dir.y; }
	Ray2f() {}
	
	Point2f     origin;
	Direction2f direction;
};

struct Ray3f {
	
	Ray3f(const Point3f& _point, const Direction3f& _dir) {origin.point.x=_point.point.x; origin.point.y=_point.point.y; origin.point.z=_point.point.z; direction.dir.x=_dir.dir.x; direction.dir.y=_dir.dir.y; direction.dir.z=_dir.dir.z; }
	Ray3f() {}
	
	Point3f     origin;
	Direction3f direction;
};

void RayInitWithPointDirection2f(const Point2f& pt, const Direction2f& dir, Ray2f* outRay);
void RayInitWithPointDirection3f(const Point3f& pt, const Direction3f& dir, Ray3f* outRay);

// ::::: PLANE ::::::

struct Plane3f {
	
	Plane3f(const Normal3f& _norm, const F32 _d) {norm.dir.dir.x=_norm.dir.dir.x; norm.dir.dir.y=_norm.dir.dir.y; norm.dir.dir.z=_norm.dir.dir.z; d=_d;}
	
	Plane3f(const Vec3f& _norm, const F32 _d) {norm.dir.dir.x=_norm.x; norm.dir.dir.y=_norm.y; norm.dir.dir.z=_norm.z; d=_d;}
	
	Plane3f() {}
	
	Normal3f norm; //a, b, c
	F32 d;
};

void PlaneInitWithValue3f(F32 a, F32 b, F32 c, F32 d, Plane3f* outPlane);void PlaneNormalize3f(Plane3f& plane);

//Plane Extraction for Direct3D: extract 6 planes from matrix 4X4
void ExtractPlanes3f( Plane3f* p_planes, const Mat44f& comboMatrix, bool normalize);

//Plane3f& Plane3fInitWithPointNormal(const Point3f& pt, const Normal3f& norm, Plane3f* outPlane);
//Plane3f& Plane3fInitWithPoints(const Point3f& pt1, const Point3f& pt2, const Point3f& pt3, Plane3f* outPlane);

// ::::: TRIANGLE ::::::

struct Triangle2f {
	
	Triangle2f(const Point2f& _a, const Point2f& _b) {a.point.x=_a.point.x; a.point.y=_a.point.y; b.point.x=_b.point.x; b.point.y=_b.point.y; }
	
	Triangle2f() {}
	
	Point2f a;
	Point2f b;
	Point2f c;
};

struct Triangle3f {
	
	Triangle3f(const Point3f& _a, const Point3f& _b, const Point3f& _c ) {a.point.x=_a.point.x; a.point.y=_a.point.y; a.point.z=_a.point.z; b.point.x=_b.point.x; b.point.y=_b.point.y; b.point.z=_b.point.z; c.point.x=_c.point.x; c.point.y=_c.point.y; c.point.z=_c.point.z; }
	
	Triangle3f() {}
	
	Point3f a;
	Point3f b;
	Point3f c;
};

void TriangleInitWithPoints2f(const Point2f& pt1, const Point2f& pt2, const Point2f& pt3, Triangle2f* outTriangle);
void TriangleInitWithPoints3f(const Point3f& pt1, const Point3f& pt2, const Point3f& pt3, Triangle3f* outTriangle);

// ::::: CIRCLE ::::::

struct Circle2f {
	
	Circle2f(const Point2f& _center, const F32 _radius) {center.point.x=_center.point.x; center.point.y=_center.point.y; radius=_radius; }
	Circle2f() {}
	
	Point2f center;
	F32     radius;
};

void CircleInitWithCenterRadius2f(const Point2f center, F32 rad, Circle2f* outCircle);

// ::::: CONE ::::::

struct Cone3f {
	
	Cone3f(const Point3f& _center, const F32 _radius, const F32 _heigth) {center.point.x=_center.point.x;  center.point.y=_center.point.y; center.point.z=_center.point.z; radius=_radius; heigth=_heigth; }
	Cone3f() { }
	
	Point3f center;
	F32     radius;
	F32     heigth;
};

void ConeInitWithCenterRadiusHeigth3f(const Point3f& center, F32 radius, F32 heigth, Cone3f* outCone);
//Cone& ConeInitWithCircleHeigth(const Circle3f& circle, const F32 heigth);

// ::::: CYLINDER ::::::

struct Cylinderf {
	
	Cylinderf(const Point3f& _center, const F32 _radius, const F32 _heigth) {center.point.x=_center.point.x;  center.point.y=_center.point.y; center.point.z=_center.point.z; radius=_radius; heigth=_heigth; }
	Cylinderf() {}
	
	Point3f center;
	F32     radius;
	F32     heigth;
};

void CylinderInitWithCenterRadiusHeigthf(const Point3f& center, F32 radius, F32 heigth, Cylinderf* outCylinder);

// ::::: SPHERE ::::::

struct Spheref {
	
	Spheref(const Point3f& _center, const F32 _radius) {center.point.x=_center.point.x;  center.point.y=_center.point.y; center.point.z=_center.point.z; radius=_radius; }
	Spheref() {}
	
	Point3f center;
	F32     radius;
};

void SphereInitWithCenterRadiusf(const Point3f& center, F32 radius, Spheref* outSpheref);
void SphereInitWithPointsf(Point3f* ptList, int ptCount, Spheref* outSpheref);

// ::::: AABB ::::::

// 2 Dimensions
struct AABB2f {

	AABB2f(const Point2f& _center, const Vec2f& _halfWidths ) { center.point.x = _center.point.x;  center.point.y = _center.point.y; halfWidths.x = _halfWidths.x; halfWidths.y = _halfWidths.y; }
	AABB2f() {}

	Point2f center;
	Vec2f   halfWidths;
};

void AABBInitWithCenterHalfWidth2f(const Point2f& center, const Vec2f& halfW, AABB2f* outAABB);
void AABBInitWithCenterHalfWidthValues2f(const Point2f& center, F32 hwX, F32 hwY, AABB2f* outAABB);
void AABBInitWithMinMax2f(const Point2f& min, const Point2f& max, AABB2f* outAABB);
void AABBInitWithPoints2f(Point2f* ptList, int ptCount, AABB2f* outBox);

void MostDistantPoints2f(Point2f* ptList, int ptCount, F32& min, F32& max);

void AABBFindMinMax2f(const AABB2f& aabb, Point2f& min, Point2f& max);
void AABBFindMinMax2f(const Point2f& center, const Vec2f& halfW, Point2f& min, Point2f& max);

// 3 Dimensions
struct AABB3f {
	
	AABB3f(const Point3f& _center, const Vec3f& _halfWidths ) {center.point.x=_center.point.x;  center.point.y=_center.point.y; center.point.z=_center.point.z; halfWidths.x=_halfWidths.x; halfWidths.y=_halfWidths.y; halfWidths.z=_halfWidths.z; }
	AABB3f() {}
	
	Point3f center;
	Vec3f   halfWidths;
};

void AABBInitWithCenterHalfWidth3f(const Point3f& center, const Vec3f& halfW,AABB3f* outAABB);
void AABBInitWithCenterHalfWidthValues3f(const Point3f& center, F32 hwX, F32 hwY, F32 hwZ, AABB3f* outAABB);
void AABBInitWithMinMax3f(const Point3f& min, const Point3f& max, AABB3f* outAABB);
void AABBInitWithPoints3f(Point3f* ptList, int ptCount, AABB3f* outBox);

void MostDistantPoints3f(Point3f* ptList, int ptCount, F32& min, F32& max);

void AABBFindMinMax3f(const AABB3f& aabb, Point3f& min, Point3f& max);
void AABBFindMinMax3f(const Point3f& center, const Vec3f& halfW, Point3f& min, Point3f& max);
F32 AABBVolume3f(const AABB3f& aabb);

// ::::: OBB3f ::::::

struct OBB3f {
	
	OBB3f(const Point3f& _center, const Vec3f& _orientX, const Vec3f& _orientY, const Vec3f& _orientZ, const Vec3f& _halfWidths) {center.point.x=_center.point.x;  center.point.y=_center.point.y; center.point.z=_center.point.z; orientX.x=_orientX.x; orientX.y=_orientX.y; orientX.z=_orientX.z; orientY.x=_orientY.x; orientY.y=_orientY.y; orientY.z=_orientY.z; orientZ.x=_orientZ.x; orientZ.y=_orientZ.y; orientZ.z=_orientZ.z; halfWidths.x=_halfWidths.x; halfWidths.y=_halfWidths.y; halfWidths.z=_halfWidths.z;}
	OBB3f() {}
	
	Point3f center;
	// Orientation matrix
	Vec3f orientX;
	Vec3f orientY;
	Vec3f orientZ;
	// Halfwidths
	Vec3f halfWidths;
};

void OBBInitWithCenterOrientationHalfWidth3f(const Point3f& center, const Vec3f& orientX, const Vec3f& orientY, const Vec3f& orientZ, const Vec3f& halfW, OBB3f* outOBB);
void OBBInitWithCenterOrientationHalfWidthValues3f(const Point3f& center, const Vec3f& orientX, const Vec3f& orientY, const Vec3f& orientZ, F32 hwX, F32 hwY, F32 hwZ, OBB3f* outOBB);



FDK_NS_END

#endif
