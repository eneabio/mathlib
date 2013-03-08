// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_GEOMETRYD_H__
#define __FDK_GEOMETRYD_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/mathd.h"
#include "fdk/vec2d.h"
#include "fdk/vec3d.h"
#include "fdk/mat44d.h"


FDK_NS_BEGIN

// ::::: POINT ::::::

struct Point2d {
	Point2d(F64 _x, F64 _y)    { point.x = _x; point.y = _y; }
	Point2d(const Vec2d& _vec) { point.x = _vec.x; point.y = _vec.y; }
	Point2d() {}
	
	Vec2d point;
};

struct Point3d {
	
	Point3d(const Vec3d& _vec)    { point.x = _vec.x; point.y = _vec.y; point.z = _vec.z; }
	Point3d(F64 _x,F64 _y,F64 _z) { point.x = _x; point.y = _y; point.z = _z; }
	Point3d() {}
	
	F64& operator()(int index) {
		//assert
		return ((F64*)this)[index];
	}
	const F64& operator()(int index) const {
		//assert
		return ((F64*)this)[index];
	}
	
	Vec3d point;
};

void Point2dInit(Point2d* outPoint);
void Point3dInit(Point3d* outPoint);

void Point2dInitWithVector(const Vec2d& vec, Point2d* outPoint);
void Point3dInitWithVector( const Vec3d& vec, Point3d* outPoint);

void PointInitWithValues2d( F64 x, F64 y, Point2d* outPoint);
void PointInitWithValues3d( F64 x, F64 y, F64 z, Point3d* outPoint);

// ::::: DIRECTION ::::::

struct Direction2d {
	
	Direction2d(const Vec2d& _dir) { dir.x = _dir.x; dir.y = _dir.y; }
	Direction2d() {}
	
	Vec2d dir;
};

struct Direction3d {
	
	Direction3d(const Vec3d& _dir) { dir.x = _dir.x; dir.y = _dir.y; dir.z = _dir.z; }
	Direction3d() {}
	
	// fare con quaternione
	Vec3d dir;
};

void Direction2dInitWithVector(const Vec2d vec, Direction2d* outDirection);
void Direction3dInitWithVector(const Vec3d vec, Direction3d* outDirection);

// ::::: SEGMENT ::::::

struct Segment2d {
	
	Segment2d(const Point2d& _a, const Point2d& _b ) { a.point.x = _a.point.x; a.point.y = _a.point.y; b.point.x = _b.point.x; b.point.y = _b.point.y; }
	Segment2d() {}
	
	Point2d a;
	Point2d b;
};

struct Segment3d {
	
	Segment3d(const Point3d& _a, const Point3d& _b ) { a.point.x = _a.point.x; a.point.y = _a.point.y; a.point.z = _a.point.z; b.point.x = _b.point.x; b.point.y = _b.point.y; b.point.z = _b.point.z; }
	Segment3d() {}
	
	Point3d a;
	Point3d b;
};

void SegmentInitWithPoints2d(const Point2d& pt1, const Point2d& pt2, Segment2d* outSegment);
void SegmentInitWithPoints3d(const Point3d& pt1, const Point3d& pt2, Segment3d* outSegment);

void SegmentInitWithPointVector2d(const Point2d& pt, const Vec2d& vec, Segment2d* outSegment);
void SegmentInitWithPointVector3d(const Point3d& pt, const Vec3d& vec, Segment3d* outSegment);

// ::::: NORMAL ::::::

struct Normal2d {
	
	Normal2d(const Direction2d& _dir) { dir.dir.x = _dir.dir.x; dir.dir.y = _dir.dir.y; }
	Normal2d() {}
	
	Direction2d dir;
};

struct Normal3d {
	
	Normal3d(const Direction3d& _dir) { dir.dir.x = _dir.dir.x; dir.dir.y = _dir.dir.y; dir.dir.z = _dir.dir.z; }
	Normal3d() {}
	
	Direction3d dir;
};

void NormalInit2d(const Direction2d& dir, Normal2d* outNormal);
void NormalInit3d(const Direction3d& dir, Normal3d* outNormal);

// ::::: RAY ::::::

struct Ray2d {
	
	Ray2d(const Point2d& _point, const Direction2d& _dir) { origin.point.x = _point.point.x; origin.point.y = _point.point.y; direction.dir.x = _dir.dir.x; direction.dir.y = _dir.dir.y; }
	Ray2d() {}
	
	Point2d     origin;
	Direction2d direction;
};

struct Ray3d {
	
	Ray3d(const Point3d& _point, const Direction3d& _dir) { origin.point.x = _point.point.x; origin.point.y = _point.point.y; origin.point.z = _point.point.z; direction.dir.x = _dir.dir.x; direction.dir.y = _dir.dir.y; direction.dir.z = _dir.dir.z; }
	Ray3d() {}
	
	Point3d     origin;
	Direction3d direction;
};

void RayInitWithPointDirection2d(const Point2d& pt, const Direction2d& dir, Ray2d* outRay);
void RayInitWithPointDirection3d(const Point3d& pt, const Direction3d& dir, Ray3d* outRay);

// ::::: PLANE ::::::

struct Plane3d {
	
	Plane3d(const Normal3d& _norm, const F64 _d) { norm.dir.dir.x = _norm.dir.dir.x; norm.dir.dir.y = _norm.dir.dir.y; norm.dir.dir.z = _norm.dir.dir.z; d = _d; }
	
	Plane3d(const Vec3d& _norm, const F64 _d) { norm.dir.dir.x = _norm.x; norm.dir.dir.y = _norm.y; norm.dir.dir.z = _norm.z; d = _d; }
	
	Plane3d() {}
	
	Normal3d norm; //a, b, c
	F64 d;
};

void PlaneInitWithValue3d(F64 a, F64 b, F64 c, F64 d, Plane3d* outPlane);void PlaneNormalize3d(Plane3d& plane);

//Plane Extraction for Direct3D: extract 6 planes from matrix 4X4
void ExtractPlanes3d( Plane3d* p_planes, const Mat44d& comboMatrix, bool normalize);

//Plane3d& Plane3dInitWithPointNormal(const Point3d& pt, const Normal3d& norm, Plane3d* outPlane);
//Plane3d& Plane3dInitWithPoints(const Point3d& pt1, const Point3d& pt2, const Point3d& pt3, Plane3d* outPlane);

// ::::: TRIANGLE ::::::

struct Triangle2d {
	
	Triangle2d(const Point2d& _a, const Point2d& _b) { a.point.x = _a.point.x; a.point.y = _a.point.y; b.point.x = _b.point.x; b.point.y = _b.point.y; }
	
	Triangle2d() {}
	
	Point2d a;
	Point2d b;
	Point2d c;
};

struct Triangle3d {
	
	Triangle3d(const Point3d& _a, const Point3d& _b, const Point3d& _c ) { a.point.x = _a.point.x; a.point.y = _a.point.y; a.point.z = _a.point.z; b.point.x = _b.point.x; b.point.y = _b.point.y; b.point.z = _b.point.z; c.point.x = _c.point.x; c.point.y = _c.point.y; c.point.z = _c.point.z; }
	
	Triangle3d() {}
	
	Point3d a;
	Point3d b;
	Point3d c;
};

void TriangleInitWithPoints2d(const Point2d& pt1, const Point2d& pt2, const Point2d& pt3, Triangle2d* outTriangle);
void TriangleInitWithPoints3d(const Point3d& pt1, const Point3d& pt2, const Point3d& pt3, Triangle3d* outTriangle);

// ::::: CIRCLE ::::::

struct Circle2d {
	
	Circle2d(const Point2d& _center, const F64 _radius) { center.point.x = _center.point.x; center.point.y = _center.point.y; radius = _radius; }
	Circle2d() {}
	
	Point2d center;
	F64     radius;
};

void CircleInitWithCenterRadius2d(const Point2d center, F64 rad, Circle2d* outCircle);

// ::::: CONE ::::::

struct Cone3d {
	
	Cone3d(const Point3d& _center, const F64 _radius, const F64 _heigth) { center.point.x = _center.point.x;  center.point.y = _center.point.y; center.point.z = _center.point.z; radius = _radius; heigth = _heigth; }
	Cone3d() { }
	
	Point3d center;
	F64     radius;
	F64     heigth;
};

void ConeInitWithCenterRadiusHeigth3d(const Point3d& center, F64 radius, F64 heigth, Cone3d* outCone);
//Cone& ConeInitWithCircleHeigth(const Circle3d& circle, const F64 heigth);

// ::::: CYLINDER ::::::

struct Cylinderd {
	
	Cylinderd(const Point3d& _center, const F64 _radius, const F64 _heigth) { center.point.x = _center.point.x;  center.point.y = _center.point.y; center.point.z = _center.point.z; radius = _radius; heigth = _heigth; }
	Cylinderd() {}
	
	Point3d center;
	F64     radius;
	F64     heigth;
};

void CylinderInitWithCenterRadiusHeigthd(const Point3d& center, F64 radius, F64 heigth, Cylinderd* outCylinder);

// ::::: SPHERE ::::::

struct Sphered {
	
	Sphered(const Point3d& _center, const F64 _radius) { center.point.x = _center.point.x;  center.point.y = _center.point.y; center.point.z = _center.point.z; radius = _radius; }
	Sphered() {}
	
	Point3d center;
	F64     radius;
};

void SphereInitWithCenterRadiusd(const Point3d& center, F64 radius, Sphered* outSphered);
void SphereInitWithPointsd(Point3d* ptList, int ptCount, Sphered* outSphered);

// ::::: AABB ::::::

// 2 Dimensions
struct AABB2d {

	AABB2d(const Point2d& _center, const Vec2d& _halfWidths ) { center.point.x = _center.point.x;  center.point.y = _center.point.y; halfWidths.x = _halfWidths.x; halfWidths.y = _halfWidths.y; }
	AABB2d() {}

	Point2d center;
	Vec2d   halfWidths;
};

void AABBInitWithCenterHalfWidth2d(const Point2d& center, const Vec2d& halfW, AABB2d* outAABB);
void AABBInitWithCenterHalfWidthValues2d(const Point2d& center, F64 hwX, F64 hwY, AABB2d* outAABB);
void AABBInitWithMinMax2d(const Point2d& min, const Point2d& max, AABB2d* outAABB);
void AABBInitWithPoints2d(Point2d* ptList, int ptCount, AABB2d* outBox);


void MostDistantPoints2d(Point2d* ptList, int ptCount, F64& min, F64& max);

void AABBFindMinMax2d(const AABB2d& aabb, Point2d& min, Point2d& max);
void AABBFindMinMax2d(const Point2d& center, const Vec2d& halfW, Point2d& min, Point2d& max);

// 3 Dimensions
struct AABB3d {
	
	AABB3d(const Point3d& _center, const Vec3d& _halfWidths ) { center.point.x = _center.point.x;  center.point.y = _center.point.y; center.point.z = _center.point.z; halfWidths.x = _halfWidths.x; halfWidths.y = _halfWidths.y; halfWidths.z = _halfWidths.z; }
	AABB3d() {}
	
	Point3d center;
	Vec3d   halfWidths;
};

void AABBInitWithCenterHalfWidth3d(const Point3d& center, const Vec3d& halfW,AABB3d* outAABB);
void AABBInitWithCenterHalfWidthValues3d(const Point3d& center, F64 hwX, F64 hwY, F64 hwZ, AABB3d* outAABB);
void AABBInitWithMinMax3d(const Point3d& min, const Point3d& max, AABB3d* outAABB);
void AABBInitWithPoints3d(Point3d* ptList, int ptCount, AABB3d* outBox);

void MostDistantPoints3d(Point3d* ptList, int ptCount, F64& min, F64& max);

void AABBFindMinMax3d(const AABB3d& aabb, Point3d& min, Point3d& max);
void AABBFindMinMax3d(const Point3d& center, const Vec3d& halfW, Point3d& min, Point3d& max);

// ::::: OBB3d ::::::

struct OBB3d {
	
	OBB3d(const Point3d& _center, const Vec3d& _orientX, const Vec3d& _orientY, const Vec3d& _orientZ, const Vec3d& _halfWidths) { center.point.x = _center.point.x;  center.point.y = _center.point.y; center.point.z = _center.point.z; orientX.x = _orientX.x; orientX.y = _orientX.y; orientX.z = _orientX.z; orientY.x = _orientY.x; orientY.y = _orientY.y; orientY.z = _orientY.z; orientZ.x = _orientZ.x; orientZ.y = _orientZ.y; orientZ.z = _orientZ.z; halfWidths.x = _halfWidths.x; halfWidths.y = _halfWidths.y; halfWidths.z = _halfWidths.z; }
	OBB3d() {}
	
	Point3d center;
	// Orientation matrix
	Vec3d orientX;
	Vec3d orientY;
	Vec3d orientZ;
	// Halfwidths
	Vec3d halfWidths;
};

void OBBInitWithCenterOrientationHalfWidth3d(const Point3d& center, const Vec3d& orientX, const Vec3d& orientY, const Vec3d& orientZ, const Vec3d& halfW, OBB3d* outOBB);
void OBBInitWithCenterOrientationHalfWidthValues3d(const Point3d& center, const Vec3d& orientX, const Vec3d& orientY, const Vec3d& orientZ, F64 hwX, F64 hwY, F64 hwZ, OBB3d* outOBB);

FDK_NS_END

#endif
