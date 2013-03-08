// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/geometryd.h"

FDK_NS_BEGIN

// ::::: POINT ::::::

void Point2dInit(Point2d* outPoint) {
	PointInitWithValues2d(0.0, 0.0, outPoint);
}

void PointInitWithValues2d(F64 x, F64 y, Point2d* outPoint) {
	Vec2d vec;
	Vec2dInitWithValues(x,y,&vec);
	Point2dInitWithVector(vec, outPoint);
}

void Point2dInitWithVector(const Vec2d& vec, Point2d* outPoint) {
	outPoint->point = vec;
}

void Point3dInit(Point3d* outPoint) {
	PointInitWithValues3d( 0.0, 0.0, 0.0, outPoint );
}

void PointInitWithValues3d( F64 x, F64 y, F64 z, Point3d* outPoint) {
	Vec3d vec;
	Vec3dInitWithValues(x, y, z, &vec);
	Point3dInitWithVector( vec, outPoint);
}

void Point3dInitWithVector(const Vec3d& vec, Point3d* outPoint) {
	outPoint->point = vec;
	
}

// ::::: DIRECTION ::::::

void Direction2dInitWithVector(const Vec2d vec, Direction2d* outDirection) {
	outDirection->dir.x = vec.x;
	outDirection->dir.y = vec.y;
	
}

void Direction3dInitWithVector(const Vec3d vec, Direction3d* outDirection) {
	outDirection->dir.x = vec.x;
	outDirection->dir.y = vec.y;
	outDirection->dir.z = vec.z;
	
}

// ::::: NORMAL ::::::

void NormalInit2d(const Direction2d& dir, Normal2d* outNormal) {
	outNormal->dir.dir = dir.dir;
	
}

void NormalInit3d(const Direction3d& dir, Normal3d* outNormal) {
	outNormal->dir.dir = dir.dir;
	
}

// ::::: RAY ::::::

void RayInitWithPointDirection2d(const Point2d& pt, const Direction2d& dir, Ray2d* outRay) {
	outRay->origin.point  = pt.point;
	outRay->direction.dir = dir.dir;
	
}

void RayInitWithPointDirection3d(const Point3d& pt, const Direction3d& dir, Ray3d* outRay) {
	outRay->origin.point  = pt.point;
	outRay->direction.dir = dir.dir;
	
}

// ::::: PLANE ::::::

void PlaneInitWithValue3d(F64 a, F64 b, F64 c, F64 d, Plane3d* outPlane) {
	outPlane->norm.dir.dir.x  =  a;
	outPlane->norm.dir.dir.y  =  b;
	outPlane->norm.dir.dir.z  =  c;
	outPlane->d  =  d;
	
}

void PlaneNormalize3d(Plane3d& plane)
{
	F64 mag;
	mag = Sqrtd(plane.norm.dir.dir.x * plane.norm.dir.dir.x + plane.norm.dir.dir.y * plane.norm.dir.dir.y + plane.norm.dir.dir.z * plane.norm.dir.dir.z);
	plane.norm.dir.dir.x = plane.norm.dir.dir.x / mag;
	plane.norm.dir.dir.y = plane.norm.dir.dir.y / mag;
	plane.norm.dir.dir.z = plane.norm.dir.dir.z / mag;
	plane.d = plane.d / mag;
}

void ExtractPlanes3d( Plane3d* planes, const Mat44d& comboMatrix, bool normalize) {
	//reference: Paper: Fast Extraction of Viewing Frustum Planes from the World- View-Projection Matrix, by Gil Gribb and Klaus Hartmann
	
	//a=norm.x, b=norm.y, c=norm.z
	
	// Left clipping plane
	planes[0].norm.dir.dir.x = comboMatrix.v03 + comboMatrix.v00;
	planes[0].norm.dir.dir.y = comboMatrix.v13 + comboMatrix.v10;
	planes[0].norm.dir.dir.z = comboMatrix.v23 + comboMatrix.v20;
	planes[0].d = comboMatrix.v33 + comboMatrix.v30;
	
	// Right clipping plane
	planes[1].norm.dir.dir.x = comboMatrix.v03 - comboMatrix.v00;
	planes[1].norm.dir.dir.y = comboMatrix.v13 - comboMatrix.v10;
	planes[1].norm.dir.dir.z = comboMatrix.v23 - comboMatrix.v20;
	planes[1].d = comboMatrix.v33 - comboMatrix.v30;
	
	// Top clipping plane
	planes[2].norm.dir.dir.x = comboMatrix.v03 - comboMatrix.v01;
	planes[2].norm.dir.dir.y = comboMatrix.v13 - comboMatrix.v11;
	planes[2].norm.dir.dir.z = comboMatrix.v23 - comboMatrix.v21;
	planes[2].d = comboMatrix.v33 - comboMatrix.v31;
	
	// Bottom clipping plane
	planes[3].norm.dir.dir.x = comboMatrix.v03 + comboMatrix.v01;
	planes[3].norm.dir.dir.y = comboMatrix.v13 + comboMatrix.v11;
	planes[3].norm.dir.dir.z = comboMatrix.v23 + comboMatrix.v21;
	planes[3].d = comboMatrix.v33 + comboMatrix.v31;
	
	// Near clipping plane
	planes[4].norm.dir.dir.x = comboMatrix.v02;
	planes[4].norm.dir.dir.y = comboMatrix.v12;
	planes[4].norm.dir.dir.z = comboMatrix.v22;
	planes[4].d = comboMatrix.v32;
	
	// Far clipping plane
	planes[5].norm.dir.dir.x = comboMatrix.v03 - comboMatrix.v02;
	planes[5].norm.dir.dir.y = comboMatrix.v13 - comboMatrix.v12;
	planes[5].norm.dir.dir.z = comboMatrix.v23 - comboMatrix.v22;
	planes[5].d = comboMatrix.v33 - comboMatrix.v32;
	
	// Normalize the plane equations, if requested
	if (normalize == true)
	{
		PlaneNormalize3d(planes[0]);
		PlaneNormalize3d(planes[1]);
		PlaneNormalize3d(planes[2]);
		PlaneNormalize3d(planes[3]);
		PlaneNormalize3d(planes[4]);
		PlaneNormalize3d(planes[5]);
	}
}

// ::::: SEGMENT ::::::

void SegmentInitWithPoints3d(const Point3d& pt1, const Point3d& pt2, Segment3d* outSegment) {
	outSegment->a = pt1;
	outSegment->b = pt2;
	
}

void SegmentInitWithPointVector3d(const Point3d& pt, const Vec3d& vec, Segment3d* outSegment) {
	Point3d tempOut;
	Point3dInitWithVector( vec , &tempOut );
	SegmentInitWithPoints3d( pt , tempOut , outSegment );
}

void SegmentInitWithPoints2d(const Point2d& pt1, const Point2d& pt2, Segment2d* outSegment) {
	outSegment->a = pt1;
	outSegment->b = pt2;
	
}

void SegmentInitWithPointVector2d(const Point2d& pt, const Vec2d& vec, Segment2d* outSegment) {
	Point2d tempOut;
	Point2dInitWithVector( vec , &tempOut );
	SegmentInitWithPoints2d( pt , tempOut , outSegment );
}

// ::::: SPHERE ::::::

void SphereInitWithCenterRadiusd(const Point3d& center, F64 radius, Sphered* outSphered) {
	outSphered->center = center;
	outSphered->radius = radius;
	
}

// ::::: AABB ::::::

// 2 Dimensions
void AABBInitWithCenterHalfWidthValues2d(const Point2d& center, F64 hwX, F64 hwY, AABB2d* outAABB) {
	Vec2d vec;
	Vec2dInitWithValues(hwX,hwY, &vec);
	AABBInitWithCenterHalfWidth2d(center, vec, outAABB);
}

void AABBInitWithCenterHalfWidth2d(const Point2d& center, const Vec2d& halfW, AABB2d* outAABB) {
	outAABB->center = center;
	outAABB->halfWidths = halfW;
}

void AABBInitWithMinMax2d(const Point2d& min, const Point2d& max, AABB2d* outAABB) {
	outAABB->center.point.x = Div2d(min.point.x + max.point.x);
	outAABB->center.point.y = Div2d(min.point.y + max.point.y);
	outAABB->halfWidths.x   = outAABB->center.point.x - min.point.x;
	outAABB->halfWidths.y   = outAABB->center.point.y - min.point.y;
}

void AABBInitWithPoints2d(Point2d* ptList, int ptCount, AABB2d* outBox) {
	int minX = 0;
	int maxX = 0;
	int minY = 0;
	int maxY = 0;

	for(int i = 1; i<ptCount; ++i) {
		if (ptList[i].point.x < ptList[minX].point.x) minX = i;
		if (ptList[i].point.x > ptList[maxX].point.x) maxX = i;
		if (ptList[i].point.y < ptList[minY].point.y) minY = i;
		if (ptList[i].point.y > ptList[maxY].point.y) maxY = i;
	}

	outBox->center.point.x = Div2d(ptList[maxX].point.x + ptList[minX].point.x);
	outBox->center.point.y = Div2d(ptList[maxY].point.y + ptList[minY].point.y);
	outBox->halfWidths.x   = outBox->center.point.x     - ptList[minX].point.x;
	outBox->halfWidths.y   = outBox->center.point.y     - ptList[minY].point.y;
}

void AABBFindMinMax2d( const AABB2d& aabb, Point2d& min, Point2d& max) {
	AABBFindMinMax2d( aabb.center, aabb.halfWidths, min, max );
}

void AABBFindMinMax2d(const Point2d& center, const Vec2d& halfW, Point2d& min, Point2d& max) {
	min.point.x = center.point.x - halfW.x;
	min.point.y = center.point.y - halfW.y;

	max.point.x = center.point.x + halfW.x;
	max.point.y = center.point.y + halfW.y;
}

void MostDistantPoints2d(Point2d* ptList, int ptCount, int* outMin, int* outMax) {
	int minX = 0;
	int maxX = 0;
	int minY = 0;
	int maxY = 0;

	for(int i = 1; i<ptCount; ++i) {
		if (ptList[i].point.x < ptList[minX].point.x) minX = i;
		if (ptList[i].point.x > ptList[maxX].point.x) maxX = i;
		if (ptList[i].point.y < ptList[minY].point.y) minY = i;
		if (ptList[i].point.y > ptList[maxY].point.y) maxY = i;
	}

	Vec2d tempVec1;
	
	Vec2dSub( ptList[maxX].point, ptList[minX].point, &tempVec1 );
	F64 dist2X = Vec2dDot( tempVec1 , tempVec1 );

	Vec2dSub( ptList[maxY].point, ptList[minY].point, &tempVec1 );
	F64 dist2Y = Vec2dDot( tempVec1 , tempVec1 );

	int tempMin = minX;
	int tempMax = maxX;

	if ( dist2Y > dist2X ) {
		tempMax = maxY;
		tempMin = minY;
	}
	
	*outMax = tempMax;
	*outMin = tempMin;
}

// 3 Dimensions
void AABBInitWithCenterHalfWidthValues3d(const Point3d& center, F64 hwX, F64 hwY, F64 hwZ, AABB3d* outAABB) {
	Vec3d vec;
	Vec3dInitWithValues(hwX,hwY,hwZ, &vec);
	AABBInitWithCenterHalfWidth3d(center, vec, outAABB);
}

void AABBInitWithCenterHalfWidth3d(const Point3d& center, const Vec3d& halfW, AABB3d* outAABB) {
	outAABB->center = center;
	outAABB->halfWidths = halfW;
	
}

void AABBInitWithMinMax3d(const Point3d& min, const Point3d& max, AABB3d* outAABB) {
	outAABB->center.point.x = Div2d(min.point.x + max.point.x);
	outAABB->center.point.y = Div2d(min.point.y + max.point.y);
	outAABB->center.point.z = Div2d(min.point.z + max.point.z);
	
	outAABB->halfWidths.x   = outAABB->center.point.x - min.point.x;
	outAABB->halfWidths.y   = outAABB->center.point.y - min.point.y;
	outAABB->halfWidths.z   = outAABB->center.point.z - min.point.z;
}

void AABBInitWithPoints3d(Point3d* ptList, int ptCount, AABB3d* outBox) {
	int minX = 0;
	int maxX = 0;
	int minY = 0;
	int maxY = 0;
	int minZ = 0;
	int maxZ = 0;

	for(int i = 1; i<ptCount; ++i) {
		if (ptList[i].point.x < ptList[minX].point.x) minX = i;
		if (ptList[i].point.x > ptList[maxX].point.x) maxX = i;
		if (ptList[i].point.y < ptList[minY].point.y) minY = i;
		if (ptList[i].point.y > ptList[maxY].point.y) maxY = i;
		if (ptList[i].point.z < ptList[minZ].point.z) minZ = i;
		if (ptList[i].point.z > ptList[maxZ].point.z) maxZ = i;
	}

	outBox->center.point.x = Div2d(ptList[maxX].point.x + ptList[minX].point.x);
	outBox->center.point.y = Div2d(ptList[maxY].point.y + ptList[minY].point.y);
	outBox->center.point.z = Div2d(ptList[maxZ].point.z + ptList[minZ].point.z);
	outBox->halfWidths.x   = outBox->center.point.x     - ptList[minX].point.x;
	outBox->halfWidths.y   = outBox->center.point.y     - ptList[minY].point.y;
	outBox->halfWidths.z   = outBox->center.point.z     - ptList[minZ].point.z;
}

void AABBFindMinMax3d( const AABB3d& aabb, Point3d& min, Point3d& max) {
	AABBFindMinMax3d( aabb.center, aabb.halfWidths, min, max );
}

void AABBFindMinMax3d(const Point3d& center, const Vec3d& halfW, Point3d& min, Point3d& max) {
	min.point.x = center.point.x - halfW.x;
	min.point.y = center.point.y - halfW.y;
	min.point.z = center.point.z - halfW.z;
	
	max.point.x = center.point.x + halfW.x;
	max.point.y = center.point.y + halfW.y;
	max.point.z = center.point.z + halfW.z;
}

// Compute indices to the two most separated points of the points defining the AABB encompassing the point set.
// return these ad outMin and outMax
void MostDistantPoints3d(Point3d* ptList, int ptCount, int* outMin, int* outMax) {
	int minX = 0;
	int maxX = 0;
	int minY = 0;
	int maxY = 0;
	int minZ = 0;
	int maxZ = 0;
	
	for(int i = 1; i<ptCount; ++i) {
		if (ptList[i].point.x < ptList[minX].point.x) minX = i;
		if (ptList[i].point.x > ptList[maxX].point.x) maxX = i;
		if (ptList[i].point.y < ptList[minY].point.y) minY = i;
		if (ptList[i].point.y > ptList[maxY].point.y) maxY = i;
		if (ptList[i].point.z < ptList[minZ].point.z) minZ = i;
		if (ptList[i].point.z > ptList[maxZ].point.z) maxZ = i;
	}
	
	Vec3d tempVec1;
	
	Vec3dSub( ptList[maxX].point, ptList[minX].point, &tempVec1 );
	F64 dist2X = Vec3dDot( tempVec1 , tempVec1 );
	
	Vec3dSub( ptList[maxY].point, ptList[minY].point, &tempVec1 );
	F64 dist2Y = Vec3dDot( tempVec1 , tempVec1 );
	
	Vec3dSub( ptList[maxZ].point, ptList[minZ].point, &tempVec1 );
	F64 dist2Z = Vec3dDot( tempVec1 , tempVec1 );
	
	int tempMin = minX;
	int tempMax = maxX;
	
	if (dist2Y > dist2X && dist2Y > dist2Z) {
		tempMax = maxY;
		tempMin = minY;
	}
	
	if (dist2Z > dist2X && dist2Z > dist2Y) {
		tempMax = maxZ;
		tempMin = minZ;
	}
	
	*outMax = tempMax;
	*outMin = tempMin;
}

// Bounding Sphered from a set of points
void BoundingSphered( Point3d* ptList, int ptCount, Sphered* outSphered) {
	int min;
	int max;
	Vec3d tempVec;
	
	MostDistantPoints3d( ptList , ptCount , &min , &max );
	
	Vec3dSum( ptList[min].point , ptList[max].point, &tempVec );
	Vec3dMultScalarInplace( 0.5 , &tempVec );
	outSphered->center.point = tempVec;
	
	Vec3dSub( ptList[max].point , outSphered->center.point , &tempVec );
	outSphered->radius = Vec3dDot( tempVec , tempVec );
	outSphered->radius = Sqrtd( outSphered->radius );
}

// ::::: OBB3d ::::::

void OBBInitWithCenterOrientationHalfWidthValues3d(const Point3d& center, const Vec3d& orientX, const Vec3d& orientY, const Vec3d& orientZ, F64 hwX, F64 hwY, F64 hwZ, OBB3d* outOBB) {
	
	Vec3d vec;
	Vec3dInitWithValues(hwX,hwY,hwZ,&vec);
	OBBInitWithCenterOrientationHalfWidth3d(center, orientX, orientY, orientZ, vec, outOBB);
}

void OBBInitWithCenterOrientationHalfWidth3d(const Point3d& center, const Vec3d& orientX, const Vec3d& orientY, const Vec3d& orientZ, const Vec3d& halfW, OBB3d* outOBB) {
	outOBB->center = center;
	outOBB->halfWidths = halfW; //???extent vector a. The extent vector represents the difference from the center point to the point of maximum x, y, and z on the box.
	outOBB->orientX = orientX;
	outOBB->orientY = orientY;
	outOBB->orientZ = orientZ;
	
}



FDK_NS_END
