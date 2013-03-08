// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/mat43d.h"
#include "fdk/mathd.h"

FDK_NS_BEGIN

void    Mat43dInit(Mat43d* outMat) {
	//
	outMat->v00 = 1.0;
	outMat->v01 = 0.0;
	outMat->v02 = 0.0;
	
	outMat->v10 = 0.0;
	outMat->v11 = 1.0;
	outMat->v12 = 0.0;
	
	outMat->v20 = 0.0;
	outMat->v21 = 0.0;
	outMat->v22 = 1.0;
	
	outMat->v30 = 0.0;
	outMat->v31 = 0.0;
	outMat->v32 = 1.0;
	
}

void    Mat43dInitWithValue(const F64 value, Mat43d* outMat) {
	outMat->v00 = value;
	outMat->v01 = value;
	outMat->v02 = value;
	
	outMat->v10 = value;
	outMat->v11 = value;
	outMat->v12 = value;
	
	outMat->v20 = value;
	outMat->v21 = value;
	outMat->v22 = value;
	
	outMat->v30 = value;
	outMat->v31 = value;
	outMat->v32 = value;
	
}

void    Mat43dInitWithRowVec(const Vec3d& row0, const Vec3d& row1, const Vec3d& row2, const Vec3d& row3,Mat43d* outMat) {
	//row 0
	outMat->v00 = row0.x;
	outMat->v01 = row0.y;
	outMat->v02 = row0.z;
	
	//row 1
	outMat->v10 = row1.x;
	outMat->v11 = row1.y;
	outMat->v12 = row1.z;
	
	//row 2
	outMat->v20 = row2.x;
	outMat->v21 = row2.y;
	outMat->v22 = row2.z;
	
	//row 3
	outMat->v30 = row3.x;
	outMat->v31 = row3.y;
	outMat->v32 = row3.z;
	
}

void    Mat43dInitWithColumnVec(const Vec4d& column0, const Vec4d& column1, const Vec4d& column2, Mat43d* outMat) {
	//column 0
	outMat->v00 = column0.x;
	outMat->v10 = column0.y;
	outMat->v20 = column0.z;
	outMat->v30 = column0.w;
	
	//column 1
	outMat->v01 = column1.x;
	outMat->v11 = column1.y;
	outMat->v21 = column1.z;
	outMat->v31 = column1.w;
	
	//column 2
	outMat->v02 = column2.x;
	outMat->v12 = column2.y;
	outMat->v22 = column2.z;
	outMat->v32 = column2.w;
	
}

void    Mat43dGetColumn(const Mat43d& FDK_RESTRICT  inMat43d, int column, Vec4d* outVec) {
	
	FDK_ASSERT(column >= 0 && column < 3);
	
	if (column == 0) {
		outVec->x = inMat43d.v00;
		outVec->y = inMat43d.v10;
		outVec->z = inMat43d.v20;
		outVec->w = inMat43d.v30;
	}
	if (column == 1) {
		outVec->x = inMat43d.v01;
		outVec->y = inMat43d.v11;
		outVec->z = inMat43d.v21;
		outVec->w = inMat43d.v31;
	}
	if (column == 2) {
		outVec->x = inMat43d.v02;
		outVec->y = inMat43d.v12;
		outVec->z = inMat43d.v22;
		outVec->w = inMat43d.v32;
	}
	
}

void    Mat43dGetRow(const Mat43d& FDK_RESTRICT  inMat43d, int row, Vec3d* outVec) {
	
	FDK_ASSERT(row >= 0 && row <= 3);
	
	if (row == 0) {
		outVec->x = inMat43d.v00;
		outVec->y = inMat43d.v01;
		outVec->z = inMat43d.v02;
	}
	if (row == 1) {
		outVec->x = inMat43d.v10;
		outVec->y = inMat43d.v11;
		outVec->z = inMat43d.v12;
	}
	if (row == 2) {
		outVec->x = inMat43d.v20;
		outVec->y = inMat43d.v21;
		outVec->z = inMat43d.v22;
	}
	if (row == 3) {
		outVec->x = inMat43d.v30;
		outVec->y = inMat43d.v31;
		outVec->z = inMat43d.v32;
	}
}

void    Mat43dSum(const Mat43d& FDK_RESTRICT  l, const Mat43d& FDK_RESTRICT r, Mat43d* FDK_RESTRICT outMat) {
	//outMat = l + r
	outMat->v00 = l.v00 + r.v00;
	outMat->v01 = l.v01 + r.v01;
	outMat->v02 = l.v02 + r.v02;
	
	outMat->v10 = l.v10 + r.v10;
	outMat->v11 = l.v11 + r.v11;
	outMat->v12 = l.v12 + r.v12;
	
	outMat->v20 = l.v20 + r.v20;
	outMat->v21 = l.v21 + r.v21;
	outMat->v22 = l.v22 + r.v22;
	
	outMat->v30 = l.v30 + r.v30;
	outMat->v31 = l.v31 + r.v31;
	outMat->v32 = l.v32 + r.v32;
	
}

void    Mat43dSub(const Mat43d& FDK_RESTRICT  l, const Mat43d& FDK_RESTRICT r, Mat43d* FDK_RESTRICT outMat) {
	//outMat = l - r
	outMat->v00 = l.v00 - r.v00;
	outMat->v01 = l.v01 - r.v01;
	outMat->v02 = l.v02 - r.v02;
	
	outMat->v10 = l.v10 - r.v10;
	outMat->v11 = l.v11 - r.v11;
	outMat->v12 = l.v12 - r.v12;
	
	outMat->v20 = l.v20 - r.v20;
	outMat->v21 = l.v21 - r.v21;
	outMat->v22 = l.v22 - r.v22;
	
	outMat->v30 = l.v30 - r.v30;
	outMat->v31 = l.v31 - r.v31;
	outMat->v32 = l.v32 - r.v32;
	
}

void    Mat43dAbs(const Mat43d& FDK_RESTRICT  l, Mat43d* FDK_RESTRICT outMat) {
	
	outMat->v00 = Fabsd(l.v00);
	outMat->v01 = Fabsd(l.v01);
	outMat->v02 = Fabsd(l.v02);
	
	outMat->v10 = Fabsd(l.v10);
	outMat->v11 = Fabsd(l.v11);
	outMat->v12 = Fabsd(l.v12);
	
	outMat->v20 = Fabsd(l.v20);
	outMat->v21 = Fabsd(l.v21);
	outMat->v22 = Fabsd(l.v22);
	
	outMat->v30 = Fabsd(l.v30);
	outMat->v31 = Fabsd(l.v31);
	outMat->v32 = Fabsd(l.v32);
	
}

void    Mat43dMultVector(const Mat43d&  inMat43d, const Vec3d& inVec3d, Vec4d* outVec) {
	outVec->x = inMat43d.v00 * inVec3d.x +  inMat43d.v01 * inVec3d.y + inMat43d.v02 * inVec3d.z;
	outVec->y = inMat43d.v10 * inVec3d.x +  inMat43d.v11 * inVec3d.y + inMat43d.v12 * inVec3d.z;
	outVec->z = inMat43d.v20 * inVec3d.x +  inMat43d.v21 * inVec3d.y + inMat43d.v22 * inVec3d.z;
	outVec->w = inMat43d.v30 * inVec3d.x +  inMat43d.v31 * inVec3d.y + inMat43d.v32 * inVec3d.z;
}

////Inplace

void    Mat43dSumInplace(const Mat43d& r, Mat43d* outMat) {
	//outMat = outMat + r
	outMat->v00 = outMat->v00 + r.v00;
	outMat->v01 = outMat->v01 + r.v01;
	outMat->v02 = outMat->v02 + r.v02;
	
	outMat->v10 = outMat->v10 + r.v10;
	outMat->v11 = outMat->v11 + r.v11;
	outMat->v12 = outMat->v12 + r.v12;
	
	outMat->v20 = outMat->v20 + r.v20;
	outMat->v21 = outMat->v21 + r.v21;
	outMat->v22 = outMat->v22 + r.v22;
	
	outMat->v30 = outMat->v30 + r.v30;
	outMat->v31 = outMat->v31 + r.v31;
	outMat->v32 = outMat->v32 + r.v32;
	
}

void    Mat43dSubInplace(const Mat43d& r, Mat43d* outMat) {
	//outMat = outMat + r
	outMat->v00 = outMat->v00 - r.v00;
	outMat->v01 = outMat->v01 - r.v01;
	outMat->v02 = outMat->v02 - r.v02;
	
	outMat->v10 = outMat->v10 - r.v10;
	outMat->v11 = outMat->v11 - r.v11;
	outMat->v12 = outMat->v12 - r.v12;
	
	outMat->v20 = outMat->v20 - r.v20;
	outMat->v21 = outMat->v21 - r.v21;
	outMat->v22 = outMat->v22 - r.v22;
	
	outMat->v30 = outMat->v30 - r.v30;
	outMat->v31 = outMat->v31 - r.v31;
	outMat->v32 = outMat->v32 - r.v32;
	
}

FDK_NS_END