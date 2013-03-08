// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/merged.h"

FDK_NS_BEGIN

void    MergeAABBAABB2d(const AABB2d& a, const AABB2d& b, AABB2d* outBox) {
	Point2d minA;
	Point2d maxA;
	Point2d minB;
	Point2d maxB;
	
	AABBFindMinMax2d(a, minA, maxA);
	AABBFindMinMax2d(b, minB, maxB);

	if (minA.point.x > minB.point.x)
		minA.point.x = minB.point.x;
	if (minA.point.y > minB.point.y)
		minA.point.y = minB.point.y;
	if (maxA.point.x < maxB.point.x)
		maxA.point.x = maxB.point.x;
	if (maxA.point.y > maxB.point.y)
		maxA.point.y = maxB.point.y;

	AABBInitWithMinMax2d(minA, maxA, outBox);
}

void    MergeAABBAABB3d(const AABB3d& a, const AABB3d& b, AABB3d* outBox) {
	Point3d minA;
	Point3d maxA;
	Point3d minB;
	Point3d maxB;
	
	AABBFindMinMax3d(a, minA, maxA);
	AABBFindMinMax3d(b, minB, maxB);

	if (minA.point.x > minB.point.x)
		minA.point.x = minB.point.x;
	if (minA.point.y > minB.point.y)
		minA.point.y = minB.point.y;
	if (minA.point.z > minB.point.z)
		minA.point.z = minB.point.z;
	if (maxA.point.x < maxB.point.x)
		maxA.point.x = maxB.point.x;
	if (maxA.point.y < maxB.point.y)
		maxA.point.y = maxB.point.y;
	if (maxA.point.z < maxB.point.z)
		maxA.point.z = maxB.point.z;

	AABBInitWithMinMax3d(minA, maxA, outBox);

	//Vec3d tempVec;
	//Vec3dSum( a.center.point, b.center.point, &tempVec );
	//Vec3dMultScalarInplace( 0.5, &tempVec );
	//outBox->center.point = tempVec;
	//
	//F64 wX = a.halfWidths.x + b.halfWidths.x + Absd(a.center.point.x - b.center.point.x);
	//F64 wY = a.halfWidths.y + b.halfWidths.y + Absd(a.center.point.y - b.center.point.y);
	//F64 wZ = a.halfWidths.z + b.halfWidths.z + Absd(a.center.point.z - b.center.point.z);
	//F64 hwX = Div2d(wX);
	//F64 hwY = Div2d(wY);
	//F64 hwZ = Div2d(wZ);
	//outBox->halfWidths.x = hwX;
	//outBox->halfWidths.x = hwY;
	//outBox->halfWidths.x = hwZ;
}

void    MergeSpheredSphered3d(const Sphered& a, const Sphered& b, Sphered* outSphered) {
	//Optimize checking if included

	Vec3d tempVec;
	Vec3dSum( a.center.point, b.center.point, &tempVec );
	Vec3dMultScalarInplace( 0.5, &tempVec );
	outSphered->center.point = tempVec;
	Vec3dSub(a.center.point, b.center.point, &tempVec);
	F64 distBwCenters = Vec3dGetLenght(tempVec);
	outSphered->radius = Div2d( a.radius + b.radius + distBwCenters );
	
}

FDK_NS_END
