// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/geometryf.h"

FDK_NS_BEGIN

// ::::: POINT ::::::

void Point2fInit(Point2f* outPoint) {
	PointInitWithValues2f(0.0f, 0.0f, outPoint);
}

void PointInitWithValues2f(F32 x, F32 y, Point2f* outPoint) {
	Vec2f vec;
	Vec2fInitWithValues(x,y,&vec);
	Point2fInitWithVector(vec, outPoint);
}

void Point2fInitWithVector(const Vec2f& vec, Point2f* outPoint) {
	outPoint->point = vec;

}

void Point3fInit(Point3f* outPoint) {
	PointInitWithValues3f( 0.0f, 0.0f, 0.0f, outPoint );
}

void PointInitWithValues3f( F32 x, F32 y, F32 z, Point3f* outPoint) {
	Vec3f vec;
	Vec3fInitWithValues(x, y, z, &vec);
	Point3fInitWithVector( vec, outPoint);
}

void Point3fInitWithVector(const Vec3f& vec, Point3f* outPoint) {
	outPoint->point = vec;

}

// ::::: DIRECTION ::::::

void Direction2fInitWithVector(const Vec2f vec, Direction2f* outDirection) {
	outDirection->dir.x = vec.x;
	outDirection->dir.y = vec.y;

}

void Direction3fInitWithVector(const Vec3f vec, Direction3f* outDirection) {
	outDirection->dir.x = vec.x;
	outDirection->dir.y = vec.y;
	outDirection->dir.z = vec.z;

}

// ::::: NORMAL ::::::

void NormalInit2f(const Direction2f& dir, Normal2f* outNormal) {
	outNormal->dir.dir = dir.dir;
	
}

void NormalInit3f(const Direction3f& dir, Normal3f* outNormal) {
	outNormal->dir.dir = dir.dir;
	
}

// ::::: RAY ::::::

void RayInitWithPointDirection2f(const Point2f& pt, const Direction2f& dir, Ray2f* outRay) {
	outRay->origin.point  = pt.point;
	outRay->direction.dir = dir.dir;
	
}

void RayInitWithPointDirection3f(const Point3f& pt, const Direction3f& dir, Ray3f* outRay) {
	outRay->origin.point  = pt.point;
	outRay->direction.dir = dir.dir;
	
}

// ::::: PLANE ::::::

void PlaneInitWithValue3f(F32 a, F32 b, F32 c, F32 d, Plane3f* outPlane) {
	outPlane->norm.dir.dir.x  =  a;
	outPlane->norm.dir.dir.y  =  b;
	outPlane->norm.dir.dir.z  =  c;
	outPlane->d  =  d;
	
}

void PlaneNormalize3f(Plane3f& plane)
{
	F32 mag;
	mag = Sqrtf(plane.norm.dir.dir.x * plane.norm.dir.dir.x + plane.norm.dir.dir.y * plane.norm.dir.dir.y + plane.norm.dir.dir.z * plane.norm.dir.dir.z);
	plane.norm.dir.dir.x = plane.norm.dir.dir.x / mag;
	plane.norm.dir.dir.y = plane.norm.dir.dir.y / mag;
	plane.norm.dir.dir.z = plane.norm.dir.dir.z / mag;
	plane.d = plane.d / mag;
}

void ExtractPlanes3f( Plane3f* planes, const Mat44f& comboMatrix, bool normalize) {
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
		PlaneNormalize3f(planes[0]);
		PlaneNormalize3f(planes[1]);
		PlaneNormalize3f(planes[2]);
		PlaneNormalize3f(planes[3]);
		PlaneNormalize3f(planes[4]);
		PlaneNormalize3f(planes[5]);
	}
}

// ::::: SEGMENT ::::::

void SegmentInitWithPoints3f(const Point3f& pt1, const Point3f& pt2, Segment3f* outSegment) {
	outSegment->a = pt1;
	outSegment->b = pt2;

}

void SegmentInitWithPointVector3f(const Point3f& pt, const Vec3f& vec, Segment3f* outSegment) {
	Point3f tempOut;
	Point3fInitWithVector( vec , &tempOut );
	SegmentInitWithPoints3f( pt , tempOut , outSegment );
}

void SegmentInitWithPoints2f(const Point2f& pt1, const Point2f& pt2, Segment2f* outSegment) {
	outSegment->a = pt1;
	outSegment->b = pt2;
	
}

void SegmentInitWithPointVector2f(const Point2f& pt, const Vec2f& vec, Segment2f* outSegment) {
	Point2f tempOut;
	Point2fInitWithVector( vec , &tempOut );
	SegmentInitWithPoints2f( pt , tempOut , outSegment );
}

// ::::: SPHERE ::::::

void SphereInitWithCenterRadiusf(const Point3f& center, F32 radius, Spheref* outSpheref) {
	outSpheref->center = center;
	outSpheref->radius = radius;
	
}

// ::::: AABB ::::::

// 2 Dimensions
void AABBInitWithCenterHalfWidthValues2f(const Point2f& center, F32 hwX, F32 hwY, AABB2f* outAABB) {
	Vec2f vec;
	Vec2fInitWithValues(hwX,hwY, &vec);
	AABBInitWithCenterHalfWidth2f(center, vec, outAABB);
}

void AABBInitWithCenterHalfWidth2f(const Point2f& center, const Vec2f& halfW, AABB2f* outAABB) {
	outAABB->center = center;
	outAABB->halfWidths = halfW;
}

void AABBInitWithMinMax2f(const Point2f& min, const Point2f& max, AABB2f* outAABB) {
	outAABB->center.point.x = Div2f(min.point.x + max.point.x);
	outAABB->center.point.y = Div2f(min.point.y + max.point.y);
	outAABB->halfWidths.x   = outAABB->center.point.x - min.point.x;
	outAABB->halfWidths.y   = outAABB->center.point.y - min.point.y;
}

void AABBInitWithPoints2f(Point2f* ptList, int ptCount, AABB2f* outBox) {
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

	outBox->center.point.x = Div2f(ptList[maxX].point.x + ptList[minX].point.x);
	outBox->center.point.y = Div2f(ptList[maxY].point.y + ptList[minY].point.y);
	outBox->halfWidths.x   = outBox->center.point.x     - ptList[minX].point.x;
	outBox->halfWidths.y   = outBox->center.point.y     - ptList[minY].point.y;
}

void AABBFindMinMax2f( const AABB2f& aabb, Point2f& min, Point2f& max) {
	AABBFindMinMax2f( aabb.center, aabb.halfWidths, min, max );
}

void AABBFindMinMax2f(const Point2f& center, const Vec2f& halfW, Point2f& min, Point2f& max) {
	min.point.x = center.point.x - halfW.x;
	min.point.y = center.point.y - halfW.y;

	max.point.x = center.point.x + halfW.x;
	max.point.y = center.point.y + halfW.y;
}

void MostDistantPoints2f(Point2f* ptList, int ptCount, int* outMin, int* outMax) {
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

	Vec2f tempVec1;
	
	Vec2fSub( ptList[maxX].point, ptList[minX].point, &tempVec1 );
	F32 dist2X = Vec2fDot( tempVec1 , tempVec1 );

	Vec2fSub( ptList[maxY].point, ptList[minY].point, &tempVec1 );
	F32 dist2Y = Vec2fDot( tempVec1 , tempVec1 );

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
void AABBInitWithCenterHalfWidthValues3f(const Point3f& center, F32 hwX, F32 hwY, F32 hwZ, AABB3f* outAABB) {
	Vec3f vec;
	Vec3fInitWithValues(hwX,hwY,hwZ, &vec);
	AABBInitWithCenterHalfWidth3f(center, vec, outAABB);
}

void AABBInitWithCenterHalfWidth3f(const Point3f& center, const Vec3f& halfW, AABB3f* outAABB) {
	outAABB->center = center;
	outAABB->halfWidths = halfW;
}

void AABBInitWithMinMax3f(const Point3f& min, const Point3f& max, AABB3f* outAABB) {
	outAABB->center.point.x = Div2f(min.point.x + max.point.x);
	outAABB->center.point.y = Div2f(min.point.y + max.point.y);
	outAABB->center.point.z = Div2f(min.point.z + max.point.z);
	
	outAABB->halfWidths.x   = outAABB->center.point.x - min.point.x;
	outAABB->halfWidths.y   = outAABB->center.point.y - min.point.y;
	outAABB->halfWidths.z   = outAABB->center.point.z - min.point.z;
}

void AABBInitWithPoints3f(Point3f* ptList, int ptCount, AABB3f* outBox) {
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

	outBox->center.point.x = Div2f(ptList[maxX].point.x + ptList[minX].point.x);
	outBox->center.point.y = Div2f(ptList[maxY].point.y + ptList[minY].point.y);
	outBox->center.point.z = Div2f(ptList[maxZ].point.z + ptList[minZ].point.z);
	outBox->halfWidths.x   = outBox->center.point.x     - ptList[minX].point.x;
	outBox->halfWidths.y   = outBox->center.point.y     - ptList[minY].point.y;
	outBox->halfWidths.z   = outBox->center.point.z     - ptList[minZ].point.z;
}

void AABBFindMinMax3f( const AABB3f& aabb, Point3f& min, Point3f& max) {
	AABBFindMinMax3f( aabb.center, aabb.halfWidths, min, max );
}

void AABBFindMinMax3f(const Point3f& center, const Vec3f& halfW, Point3f& min, Point3f& max) {
	min.point.x = center.point.x - halfW.x;
	min.point.y = center.point.y - halfW.y;
	min.point.z = center.point.z - halfW.z;

	max.point.x = center.point.x + halfW.x;
	max.point.y = center.point.y + halfW.y;
	max.point.z = center.point.z + halfW.z;
}

F32 AABBVolume3f(const AABB3f& aabb) {
	return aabb.halfWidths.x * aabb.halfWidths.y * aabb.halfWidths.z * 8;
}

// Compute indices to the two most separated points of the points defining the AABB encompassing the point set.
// return these ad outMin and outMax
void MostDistantPoints3f(Point3f* ptList, int ptCount, int* outMin, int* outMax) {
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

	Vec3f tempVec1;
	
	Vec3fSub( ptList[maxX].point, ptList[minX].point, &tempVec1 );
	F32 dist2X = Vec3fDot( tempVec1 , tempVec1 );

	Vec3fSub( ptList[maxY].point, ptList[minY].point, &tempVec1 );
	F32 dist2Y = Vec3fDot( tempVec1 , tempVec1 );

	Vec3fSub( ptList[maxZ].point, ptList[minZ].point, &tempVec1 );
	F32 dist2Z = Vec3fDot( tempVec1 , tempVec1 );
	
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

// Bounding Spheref from a set of points
void BoundingSpheref( Point3f* ptList, int ptCount, Spheref* outSpheref) {
	int min;
	int max;
	Vec3f tempVec;

	MostDistantPoints3f( ptList , ptCount , &min , &max );
	
	Vec3fSum( ptList[min].point , ptList[max].point, &tempVec );
	Vec3fMultScalarInplace( 0.5f , &tempVec );
	outSpheref->center.point = tempVec;
	
	Vec3fSub( ptList[max].point , outSpheref->center.point , &tempVec );
	outSpheref->radius = Vec3fDot( tempVec , tempVec );
	outSpheref->radius = Sqrtf( outSpheref->radius );
	
}

// ::::: OBB3f ::::::

void OBBInitWithCenterOrientationHalfWidthValues3f(const Point3f& center, const Vec3f& orientX, const Vec3f& orientY, const Vec3f& orientZ, F32 hwX, F32 hwY, F32 hwZ, OBB3f* outOBB) {
	
	Vec3f vec;
	Vec3fInitWithValues(hwX,hwY,hwZ,&vec);
	OBBInitWithCenterOrientationHalfWidth3f(center, orientX, orientY, orientZ, vec, outOBB);
}

void OBBInitWithCenterOrientationHalfWidth3f(const Point3f& center, const Vec3f& orientX, const Vec3f& orientY, const Vec3f& orientZ, const Vec3f& halfW, OBB3f* outOBB) {
	outOBB->center = center;
	outOBB->halfWidths = halfW; //???extent vector a. The extent vector represents the difference from the center point to the point of maximum x, y, and z on the box.
	outOBB->orientX = orientX;
	outOBB->orientY = orientY;
	outOBB->orientZ = orientZ;

}



FDK_NS_END
