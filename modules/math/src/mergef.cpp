// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/mergef.h"

FDK_NS_BEGIN


void    MergeAABBAABB2f(const AABB2f& a, const AABB2f& b, AABB2f* outBox) {
	Point2f minA;
	Point2f maxA;
	Point2f minB;
	Point2f maxB;
	
	AABBFindMinMax2f(a, minA, maxA);
	AABBFindMinMax2f(b, minB, maxB);

	if (minA.point.x > minB.point.x)
		minA.point.x = minB.point.x;
	if (minA.point.y > minB.point.y)
		minA.point.y = minB.point.y;
	if (maxA.point.x < maxB.point.x)
		maxA.point.x = maxB.point.x;
	if (maxA.point.y > maxB.point.y)
		maxA.point.y = maxB.point.y;

	AABBInitWithMinMax2f(minA, maxA, outBox);
}

void    MergeAABBAABB3f(const AABB3f& a, const AABB3f& b, AABB3f* outBox) {
	Point3f minA;
	Point3f maxA;
	Point3f minB;
	Point3f maxB;
	
	AABBFindMinMax3f(a, minA, maxA);
	AABBFindMinMax3f(b, minB, maxB);

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

	AABBInitWithMinMax3f(minA, maxA, outBox);

	//Vec3f tempVec;
	//Vec3fSum( a.center.point, b.center.point, &tempVec );
	//Vec3fMultScalarInplace( 0.5f, &tempVec );
	//outBox->center.point = tempVec;

	//F32 wX = a.halfWidths.x + b.halfWidths.x + Absf(a.center.point.x - b.center.point.x);
	//F32 wY = a.halfWidths.y + b.halfWidths.y + Absf(a.center.point.y - b.center.point.y);
	//F32 wZ = a.halfWidths.z + b.halfWidths.z + Absf(a.center.point.z - b.center.point.z);
	//F32 hwX = Div2f(wX);
	//F32 hwY = Div2f(wY);
	//F32 hwZ = Div2f(wZ);
	//outBox->halfWidths.x = hwX;
	//outBox->halfWidths.x = hwY;
	//outBox->halfWidths.x = hwZ;
}


void    MergeSpherefSpheref3f(const Spheref& a, const Spheref& b, Spheref* outSpheref) {
	// TODO: Optimize checking if included
	Vec3f tempVec;
	Vec3fSum( a.center.point, b.center.point, &tempVec );
	Vec3fMultScalarInplace( 0.5f, &tempVec );
	outSpheref->center.point = tempVec;
	Vec3fSub(a.center.point, b.center.point, &tempVec);
	F32 distBwCenters = Vec3fGetLenght(tempVec);
	outSpheref->radius = Div2f( a.radius + b.radius + distBwCenters );
	
}

FDK_NS_END
