// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/mathd.h"
#include "fdk/mat44d.h"
#include "fdk/mat33d.h"
//#include "fdk/memory.h"


FDK_NS_BEGIN

void    Mat44dInit(Mat44d* outMat) {
	//with identity matrix
	outMat->v00 = 1.0;
	outMat->v01 = 0.0;
	outMat->v02 = 0.0;
	outMat->v03 = 0.0;
	
	outMat->v10 = 0.0;
	outMat->v11 = 1.0;
	outMat->v12 = 0.0;
	outMat->v13 = 0.0;
	
	outMat->v20 = 0.0;
	outMat->v21 = 0.0;
	outMat->v22 = 1.0;
	outMat->v23 = 0.0;
	
	outMat->v30 = 0.0;
	outMat->v31 = 0.0;
	outMat->v32 = 0.0;
	outMat->v33 = 1.0;
	
}

void    Mat44dInitWithMatrix(const Mat44d& inMat, Mat44d* outMat) {
	outMat->v00 = inMat.v00;
	outMat->v01 = inMat.v01;
	outMat->v02 = inMat.v02;
	outMat->v03 = inMat.v03;
	
	outMat->v10 = inMat.v10;
	outMat->v11 = inMat.v11;
	outMat->v12 = inMat.v12;
	outMat->v13 = inMat.v13;
	
	outMat->v20 = inMat.v20;
	outMat->v21 = inMat.v21;
	outMat->v22 = inMat.v22;
	outMat->v23 = inMat.v23;
	
	outMat->v30 = inMat.v30;
	outMat->v31 = inMat.v31;
	outMat->v32 = inMat.v32;
	outMat->v33 = inMat.v33;
	
}

void    Mat44dInitWithValue(const F64 value, Mat44d* outMat) {
	outMat->v00 = value;
	outMat->v01 = value;
	outMat->v02 = value;
	outMat->v03 = value;
	
	outMat->v10 = value;
	outMat->v11 = value;
	outMat->v12 = value;
	outMat->v13 = value;
	
	outMat->v20 = value;
	outMat->v21 = value;
	outMat->v22 = value;
	outMat->v23 = value;
	
	outMat->v30 = value;
	outMat->v31 = value;
	outMat->v32 = value;
	outMat->v33 = value;
	
}

void    Mat44dInitWithRowVec(const Vec4d& row0, const Vec4d& row1, const Vec4d& row2, const Vec4d& row3, Mat44d* outMat) {
	//row 0
	outMat->v00 = row0.x;
	outMat->v01 = row0.y;
	outMat->v02 = row0.z;
	outMat->v03 = row0.w;
	
	//row 1
	outMat->v10 = row1.x;
	outMat->v11 = row1.y;
	outMat->v12 = row1.z;
	outMat->v13 = row1.w;
	
	//row 2
	outMat->v20 = row2.x;
	outMat->v21 = row2.y;
	outMat->v22 = row2.z;
	outMat->v23 = row2.w;
	
	//row 3
	outMat->v30 = row3.x;
	outMat->v31 = row3.y;
	outMat->v32 = row3.z;
	outMat->v33 = row3.w;
	
}

void    Mat44dInitWithColumnVec(const Vec4d& column0, const Vec4d& column1, const Vec4d& column2, const Vec4d& column3, Mat44d* outMat) {
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
	
	//column 3
	outMat->v03 = column3.x;
	outMat->v13 = column3.y;
	outMat->v23 = column3.z;
	outMat->v33 = column3.w;
	
}

void    Mat44dInitFromQuaternion(const Quatd& quat, Mat44d* outMat) {
	Mat33d matQuat;
	Mat33dInitFromQuaternion(quat, &matQuat);
	Mat44dInit(outMat);
	
	outMat->v00 = matQuat.v00;
	outMat->v01 = matQuat.v01;
	outMat->v02 = matQuat.v02;
	
	outMat->v10 = matQuat.v10;
	outMat->v11 = matQuat.v11;
	outMat->v12 = matQuat.v12;
	
	outMat->v20 = matQuat.v20;
	outMat->v21 = matQuat.v21;
	outMat->v22 = matQuat.v22;
	
}

void    Mat44dGetColumn(const Mat44d& FDK_RESTRICT  inMat44d, int column, Vec4d* outVec) {
	
	FDK_ASSERT(column >= 0 && column <=3);
	
	if (column == 0) {
		outVec->x = inMat44d.v00;
		outVec->y = inMat44d.v10;
		outVec->z = inMat44d.v20;
		outVec->w = inMat44d.v30;
	}
	if (column == 1) {
		outVec->x = inMat44d.v01;
		outVec->y = inMat44d.v11;
		outVec->z = inMat44d.v21;
		outVec->w = inMat44d.v31;
	}
	if (column == 2) {
		outVec->x = inMat44d.v02;
		outVec->y = inMat44d.v12;
		outVec->z = inMat44d.v22;
		outVec->w = inMat44d.v32;
	}
	if (column == 3) {
		outVec->x = inMat44d.v03;
		outVec->y = inMat44d.v13;
		outVec->z = inMat44d.v23;
		outVec->w = inMat44d.v33;
	}
}

void    Mat44dGetRow(const Mat44d& FDK_RESTRICT  inMat44d, int row, Vec4d* outVec) {
	
	FDK_ASSERT(row >= 0 && row <=3);
	
	if (row == 0) {
		outVec->x = inMat44d.v00;
		outVec->y = inMat44d.v01;
		outVec->z = inMat44d.v02;
		outVec->w = inMat44d.v03;
	}
	if (row == 1) {
		outVec->x = inMat44d.v10;
		outVec->y = inMat44d.v11;
		outVec->z = inMat44d.v12;
		outVec->w = inMat44d.v13;
	}
	if (row == 2) {
		outVec->x = inMat44d.v20;
		outVec->y = inMat44d.v21;
		outVec->z = inMat44d.v22;
		outVec->w = inMat44d.v23;
	}
	if (row == 3) {
		outVec->x = inMat44d.v30;
		outVec->y = inMat44d.v31;
		outVec->z = inMat44d.v32;
		outVec->w = inMat44d.v33;
	}
}

void    Mat44dSum(const Mat44d& FDK_RESTRICT  l, const Mat44d& FDK_RESTRICT r, Mat44d* FDK_RESTRICT outMat) {
	//outMat = l + r
	outMat->v00 = l.v00 + r.v00;
	outMat->v01 = l.v01 + r.v01;
	outMat->v02 = l.v02 + r.v02;
	outMat->v03 = l.v03 + r.v03;
	
	outMat->v10 = l.v10 + r.v10;
	outMat->v11 = l.v11 + r.v11;
	outMat->v12 = l.v12 + r.v12;
	outMat->v13 = l.v13 + r.v13;
	
	outMat->v20 = l.v20 + r.v20;
	outMat->v21 = l.v21 + r.v21;
	outMat->v22 = l.v22 + r.v22;
	outMat->v23 = l.v23 + r.v23;
	
	outMat->v30 = l.v30 + r.v30;
	outMat->v31 = l.v31 + r.v31;
	outMat->v32 = l.v32 + r.v32;
	outMat->v33 = l.v33 + r.v33;
	
}

void    Mat44dSub(const Mat44d& FDK_RESTRICT  l, const Mat44d& FDK_RESTRICT r, Mat44d* FDK_RESTRICT outMat) {
	//outMat = l - r
	outMat->v00 = l.v00 - r.v00;
	outMat->v01 = l.v01 - r.v01;
	outMat->v02 = l.v02 - r.v02;
	outMat->v03 = l.v03 - r.v03;
	
	outMat->v10 = l.v10 - r.v10;
	outMat->v11 = l.v11 - r.v11;
	outMat->v12 = l.v12 - r.v12;
	outMat->v13 = l.v13 - r.v13;
	
	outMat->v20 = l.v20 - r.v20;
	outMat->v21 = l.v21 - r.v21;
	outMat->v22 = l.v22 - r.v22;
	outMat->v23 = l.v23 - r.v23;
	
	outMat->v30 = l.v30 - r.v30;
	outMat->v31 = l.v31 - r.v31;
	outMat->v32 = l.v32 - r.v32;
	outMat->v33 = l.v33 - r.v33;
	
}

void    Mat44dAbs(const Mat44d& FDK_RESTRICT  l, Mat44d* FDK_RESTRICT outMat) {
	
	outMat->v00 = Fabsd(l.v00);
	outMat->v01 = Fabsd(l.v01);
	outMat->v02 = Fabsd(l.v02);
	outMat->v03 = Fabsd(l.v03);
	
	outMat->v10 = Fabsd(l.v10);
	outMat->v11 = Fabsd(l.v11);
	outMat->v12 = Fabsd(l.v12);
	outMat->v13 = Fabsd(l.v13);
	
	outMat->v20 = Fabsd(l.v20);
	outMat->v21 = Fabsd(l.v21);
	outMat->v22 = Fabsd(l.v22);
	outMat->v23 = Fabsd(l.v23);
	
	outMat->v30 = Fabsd(l.v30);
	outMat->v31 = Fabsd(l.v31);
	outMat->v32 = Fabsd(l.v32);
	outMat->v33 = Fabsd(l.v33);
	
}

F64 Mat44dCoFactor(const Mat44d& FDK_RESTRICT  m, int row, int col) {
	
	return	 (( m((row+1)&3,(col+1)&3) * m((row+2)&3,(col+2)&3) * m((row+3)&3,(col+3)&3) +
		   m((row+1)&3,(col+2)&3) * m((row+2)&3,(col+3)&3)* m((row+3)&3,(col+1)&3) +
		   m((row+1)&3,(col+3)&3) * m((row+2)&3,(col+1)&3) *m((row+3)&3,(col+2)&3))
		  -  (m((row+3)&3,(col+1)&3) *m ((row+2)&3,(col+2)&3) * m((row+1)&3,(col+3)&3) +
		      m((row+3)&3,(col+2)&3) * m((row+2)&3,(col+3)&3) * m((row+1)&3,(col+1)&3) +
		      m((row+3)&3,(col+3)&3) * m((row+2)&3,(col+1)&3) * m((row+1)&3,(col+2)&3))) * ((row + col) & 1 ? -1.0f : +1.0f);
}

F64     Mat44dDeterminant(const Mat44d& FDK_RESTRICT  inMat44d) {
	//determinant matrix 4x4
	//	F64 a1 = (inMat44d.v00 * inMat44d.v11 * inMat44d.v22 * inMat44d.v33) + (inMat44d.v00 * inMat44d.v12 * inMat44d.v23 * inMat44d.v31) + (inMat44d.v00 * inMat44d.v13 * inMat44d.v21 * inMat44d.v32) + (inMat44d.v01 * inMat44d.v10 * inMat44d.v23 * inMat44d.v32);
	//
	//	F64 a2 = (inMat44d.v01 * inMat44d.v12 * inMat44d.v20 * inMat44d.v33) + (inMat44d.v00 * inMat44d.v11 * inMat44d.v22 * inMat44d.v33) + (inMat44d.v01 * inMat44d.v13 * inMat44d.v22 * inMat44d.v30);
	//
	//	F64 a3 = (inMat44d.v02 * inMat44d.v10 * inMat44d.v21 * inMat44d.v33) + (inMat44d.v02 * inMat44d.v11 * inMat44d.v23 * inMat44d.v30) + (inMat44d.v02 * inMat44d.v13 * inMat44d.v20 * inMat44d.v31);
	//
	//	F64 a4 = (inMat44d.v03 * inMat44d.v10 * inMat44d.v22 * inMat44d.v31) + (inMat44d.v03 * inMat44d.v11 * inMat44d.v20 * inMat44d.v32) + (inMat44d.v03 * inMat44d.v12 * inMat44d.v21 * inMat44d.v30);
	//
	//	F64 a5 = -(inMat44d.v00 * inMat44d.v11 * inMat44d.v23 * inMat44d.v32) - (inMat44d.v00 * inMat44d.v12 * inMat44d.v21 * inMat44d.v33) - (inMat44d.v00 * inMat44d.v13 * inMat44d.v22 * inMat44d.v31);
	//
	//	F64 a6 = -(inMat44d.v01 * inMat44d.v10 * inMat44d.v22 * inMat44d.v33) - (inMat44d.v01 * inMat44d.v12 * inMat44d.v23 * inMat44d.v30) - (inMat44d.v01 * inMat44d.v13 * inMat44d.v20 * inMat44d.v32);
	//
	//	F64 a7 = -(inMat44d.v02 * inMat44d.v10 * inMat44d.v23 * inMat44d.v31) - (inMat44d.v02 * inMat44d.v11 * inMat44d.v20 * inMat44d.v33) - (inMat44d.v02 * inMat44d.v13 * inMat44d.v21 * inMat44d.v30);
	//
	//	F64 a8 = -(inMat44d.v03 * inMat44d.v10 * inMat44d.v21 * inMat44d.v32) - (inMat44d.v03 * inMat44d.v11 * inMat44d.v22 * inMat44d.v30) - (inMat44d.v03 * inMat44d.v12 * inMat44d.v20 * inMat44d.v31);
	//
	//	F64 determinant = a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8;
	
	
	return	inMat44d(0,0) * Mat44dCoFactor(inMat44d, 0, 0) +
	inMat44d(0,1) * Mat44dCoFactor(inMat44d, 0, 1) +
	inMat44d(0,2) * Mat44dCoFactor(inMat44d, 0, 2) +
	inMat44d(0,3) * Mat44dCoFactor(inMat44d, 0, 3);
	
}

void    Mat44dMult(const Mat44d& FDK_RESTRICT  l, const Mat44d& FDK_RESTRICT r, Mat44d* FDK_RESTRICT outMat) {
	
	//outMat = l * r
	
	outMat->v00 = l.v00 * r.v00 + l.v01 * r.v10 + l.v02 * r.v20 + l.v03 * r.v30;
	outMat->v01 = l.v00 * r.v01 + l.v01 * r.v11 + l.v02 * r.v21 + l.v03 * r.v31;
	outMat->v02 = l.v00 * r.v02 + l.v01 * r.v12 + l.v02 * r.v22 + l.v03 * r.v32;
	outMat->v03 = l.v00 * r.v03 + l.v01 * r.v13 + l.v02 * r.v23 + l.v03 * r.v33;
	
	outMat->v10 = l.v10 * r.v00 + l.v11 * r.v10 + l.v12 * r.v20 + l.v13 * r.v30;
	outMat->v11 = l.v10 * r.v01 + l.v11 * r.v11 + l.v12 * r.v21 + l.v13 * r.v31;
	outMat->v12 = l.v10 * r.v02 + l.v11 * r.v12 + l.v12 * r.v22 + l.v13 * r.v32;
	outMat->v13 = l.v10 * r.v03 + l.v11 * r.v13 + l.v12 * r.v23 + l.v13 * r.v33;
	
	outMat->v20 = l.v20 * r.v00 + l.v21 * r.v10 + l.v22 * r.v20 + l.v23 * r.v30;
	outMat->v21 = l.v20 * r.v01 + l.v21 * r.v11 + l.v22 * r.v21 + l.v23 * r.v31;
	outMat->v22 = l.v20 * r.v02 + l.v21 * r.v12 + l.v22 * r.v22 + l.v23 * r.v32;
	outMat->v23 = l.v20 * r.v03 + l.v21 * r.v13 + l.v22 * r.v23 + l.v23 * r.v33;
	
	outMat->v30 = l.v30 * r.v00 + l.v31 * r.v10 + l.v32 * r.v20 + l.v33 * r.v30;
	outMat->v31 = l.v30 * r.v01 + l.v31 * r.v11 + l.v32 * r.v21 + l.v33 * r.v31;
	outMat->v32 = l.v30 * r.v02 + l.v31 * r.v12 + l.v32 * r.v22 + l.v33 * r.v32;
	outMat->v33 = l.v30 * r.v03 + l.v31 * r.v13 + l.v32 * r.v23 + l.v33 * r.v33;
	
}

bool 	Mat44dInvert(const Mat44d& FDK_RESTRICT inMat44d, Mat44d* FDK_RESTRICT outMat) {
	//Invert the matrix 4x4
	
	//determinant matrix 4x4
	F64 determinant = Mat44dDeterminant(inMat44d);
	
	//Determinant must be different from zero, else matrix can't be inverted.
	if (FdkEqd64(determinant, 0.0, FDK_F64_TOLL))
		return false;
	
	//Invert
	
	outMat->v00 = (1.0/determinant) * (inMat44d.v11 * inMat44d.v22 * inMat44d.v33 + inMat44d.v12 * inMat44d.v23 * inMat44d.v31 + inMat44d.v13 * inMat44d.v21 * inMat44d.v32 - inMat44d.v11 * inMat44d.v23 * inMat44d.v32 - inMat44d.v12 * inMat44d.v21 * inMat44d.v33 - inMat44d.v13 * inMat44d.v22 * inMat44d.v31);
	
	outMat->v01 = (1.0/determinant) * (inMat44d.v01 * inMat44d.v23 * inMat44d.v32 + inMat44d.v02 * inMat44d.v21 * inMat44d.v33 + inMat44d.v03 * inMat44d.v22 * inMat44d.v31 - inMat44d.v01 * inMat44d.v22 * inMat44d.v33 - inMat44d.v02 * inMat44d.v23 * inMat44d.v31 - inMat44d.v03 * inMat44d.v21 * inMat44d.v32);
	
	outMat->v02 = (1.0/determinant) * (inMat44d.v01 * inMat44d.v12 * inMat44d.v33 + inMat44d.v02 * inMat44d.v13 * inMat44d.v31 + inMat44d.v03 * inMat44d.v11 * inMat44d.v32 - inMat44d.v01 * inMat44d.v13 * inMat44d.v32 - inMat44d.v02 * inMat44d.v11 * inMat44d.v33 - inMat44d.v03 * inMat44d.v12 * inMat44d.v31);
	
	outMat->v03 = (1.0/determinant) * (inMat44d.v01 * inMat44d.v13 * inMat44d.v22 + inMat44d.v02 * inMat44d.v11 * inMat44d.v23 + inMat44d.v03 * inMat44d.v12 * inMat44d.v21 - inMat44d.v01 * inMat44d.v12 * inMat44d.v23 - inMat44d.v02 * inMat44d.v13 * inMat44d.v21 - inMat44d.v03 * inMat44d.v11 * inMat44d.v22);
	
	outMat->v10 = (1.0/determinant) * (inMat44d.v10 * inMat44d.v23 * inMat44d.v32 + inMat44d.v12 * inMat44d.v20 * inMat44d.v33 + inMat44d.v13 * inMat44d.v22 * inMat44d.v30 - inMat44d.v10 * inMat44d.v22 * inMat44d.v33 - inMat44d.v12 * inMat44d.v23 * inMat44d.v30 - inMat44d.v13 * inMat44d.v20 * inMat44d.v32);
	
	outMat->v11 = (1.0/determinant) * (inMat44d.v00 * inMat44d.v22 * inMat44d.v33 + inMat44d.v02 * inMat44d.v23 * inMat44d.v30 + inMat44d.v03 * inMat44d.v20 * inMat44d.v32 - inMat44d.v00 * inMat44d.v23 * inMat44d.v32 - inMat44d.v02 * inMat44d.v20 * inMat44d.v33 - inMat44d.v03 * inMat44d.v22 * inMat44d.v30);
	
	outMat->v12 = (1.0/determinant) * (inMat44d.v00 * inMat44d.v13 * inMat44d.v32 + inMat44d.v02 * inMat44d.v10 * inMat44d.v33 + inMat44d.v03 * inMat44d.v12 * inMat44d.v30 - inMat44d.v00 * inMat44d.v12 * inMat44d.v33 - inMat44d.v02 * inMat44d.v13 * inMat44d.v30 - inMat44d.v03 * inMat44d.v10 * inMat44d.v32);
	
	outMat->v13 = (1.0/determinant) * (inMat44d.v00 * inMat44d.v12 * inMat44d.v23 + inMat44d.v02 * inMat44d.v13 * inMat44d.v20 + inMat44d.v03 * inMat44d.v10 * inMat44d.v22 - inMat44d.v00 * inMat44d.v13 * inMat44d.v22 - inMat44d.v02 * inMat44d.v10 * inMat44d.v23 - inMat44d.v03 * inMat44d.v12 * inMat44d.v20);
	
	outMat->v20 = (1.0/determinant) * (inMat44d.v10 * inMat44d.v21 * inMat44d.v33 + inMat44d.v11 * inMat44d.v23 * inMat44d.v30 + inMat44d.v13 * inMat44d.v20 * inMat44d.v31 - inMat44d.v10 * inMat44d.v23 * inMat44d.v31 - inMat44d.v11 * inMat44d.v20 * inMat44d.v33 - inMat44d.v13 * inMat44d.v21 * inMat44d.v30);
	
	outMat->v21 = (1.0/determinant) * (inMat44d.v00 * inMat44d.v23 * inMat44d.v31 + inMat44d.v01 * inMat44d.v20 * inMat44d.v33 + inMat44d.v03 * inMat44d.v21 * inMat44d.v30 - inMat44d.v00 * inMat44d.v21 * inMat44d.v33 - inMat44d.v01 * inMat44d.v23 * inMat44d.v30 - inMat44d.v03 * inMat44d.v20 * inMat44d.v31);
	
	outMat->v22 = (1.0/determinant) * (inMat44d.v00 * inMat44d.v11 * inMat44d.v33 + inMat44d.v01 * inMat44d.v13 * inMat44d.v30 + inMat44d.v03 * inMat44d.v10 * inMat44d.v31 - inMat44d.v00 * inMat44d.v13 * inMat44d.v31 - inMat44d.v01 * inMat44d.v10 * inMat44d.v33 - inMat44d.v03 * inMat44d.v11 * inMat44d.v30);
	
	outMat->v23 = (1.0/determinant) * (inMat44d.v00 * inMat44d.v13 * inMat44d.v21 + inMat44d.v01 * inMat44d.v10 * inMat44d.v23 + inMat44d.v03 * inMat44d.v11 * inMat44d.v20 - inMat44d.v00 * inMat44d.v11 * inMat44d.v23 - inMat44d.v01 * inMat44d.v13 * inMat44d.v20 - inMat44d.v03 * inMat44d.v10 * inMat44d.v21);
	
	outMat->v30 = (1.0/determinant) * (inMat44d.v10 * inMat44d.v22 * inMat44d.v31 + inMat44d.v11 * inMat44d.v20 * inMat44d.v32 + inMat44d.v12 * inMat44d.v21 * inMat44d.v30 - inMat44d.v10 * inMat44d.v21 * inMat44d.v32 - inMat44d.v11 * inMat44d.v22 * inMat44d.v30 - inMat44d.v12 * inMat44d.v20 * inMat44d.v31);
	
	outMat->v31 = (1.0/determinant) * (inMat44d.v00 * inMat44d.v21 * inMat44d.v32 + inMat44d.v01 * inMat44d.v22 * inMat44d.v30 + inMat44d.v02 * inMat44d.v20 * inMat44d.v31 - inMat44d.v00 * inMat44d.v22 * inMat44d.v31 - inMat44d.v01 * inMat44d.v20 * inMat44d.v32 - inMat44d.v02 * inMat44d.v21 * inMat44d.v30);
	
	outMat->v32 = (1.0/determinant) * (inMat44d.v00 * inMat44d.v12 * inMat44d.v31 + inMat44d.v01 * inMat44d.v10 * inMat44d.v32 + inMat44d.v02 * inMat44d.v11 * inMat44d.v30 - inMat44d.v00 * inMat44d.v11 * inMat44d.v32 - inMat44d.v01 * inMat44d.v12 * inMat44d.v30 - inMat44d.v02 * inMat44d.v10 * inMat44d.v31);
	
	outMat->v33 = (1.0/determinant) * (inMat44d.v00 * inMat44d.v11 * inMat44d.v22 + inMat44d.v01 * inMat44d.v12 * inMat44d.v20 + inMat44d.v02 * inMat44d.v10 * inMat44d.v21 - inMat44d.v00 * inMat44d.v12 * inMat44d.v21 - inMat44d.v01 * inMat44d.v10 * inMat44d.v22 - inMat44d.v02 * inMat44d.v11 * inMat44d.v20);
	
	return true;
}

void 	Mat44dTranspose(const Mat44d& FDK_RESTRICT inMat44d, Mat44d* FDK_RESTRICT outMat) {
	//transpose the matrix 4x4
	outMat->v00 = inMat44d.v00;
	outMat->v01 = inMat44d.v10;
	outMat->v02 = inMat44d.v20;
	outMat->v03 = inMat44d.v30;
	
	outMat->v10 = inMat44d.v01;
	outMat->v11 = inMat44d.v11;
	outMat->v12 = inMat44d.v21;
	outMat->v13 = inMat44d.v31;
	
	outMat->v20 = inMat44d.v02;
	outMat->v21 = inMat44d.v12;
	outMat->v22 = inMat44d.v22;
	outMat->v23 = inMat44d.v32;
	
	outMat->v30 = inMat44d.v03;
	outMat->v31 = inMat44d.v13;
	outMat->v32 = inMat44d.v23;
	outMat->v33 = inMat44d.v33;
}

void    Mat44dMultVector(const Mat44d&  inMat44d, const Vec4d& inVec4d, Vec4d* outVec) {
	outVec->x = inMat44d.v00 * inVec4d.x +  inMat44d.v01 * inVec4d.y + inMat44d.v02 * inVec4d.z + inMat44d.v03 * inVec4d.w;
	outVec->y = inMat44d.v10 * inVec4d.x +  inMat44d.v11 * inVec4d.y + inMat44d.v12 * inVec4d.z + inMat44d.v13 * inVec4d.w;
	outVec->z = inMat44d.v20 * inVec4d.x +  inMat44d.v21 * inVec4d.y + inMat44d.v22 * inVec4d.z + inMat44d.v23 * inVec4d.w;
	outVec->w = inMat44d.v30 * inVec4d.x +  inMat44d.v31 * inVec4d.y + inMat44d.v32 * inVec4d.z + inMat44d.v33 * inVec4d.w;
	
}

//Inplace

void    Mat44dSumInplace(const Mat44d& FDK_RESTRICT r, Mat44d* FDK_RESTRICT outMat) {
	//outMat = outMat + r
	outMat->v00 = outMat->v00 + r.v00;
	outMat->v01 = outMat->v01 + r.v01;
	outMat->v02 = outMat->v02 + r.v02;
	outMat->v03 = outMat->v03 + r.v03;
	
	outMat->v10 = outMat->v10 + r.v10;
	outMat->v11 = outMat->v11 + r.v11;
	outMat->v12 = outMat->v12 + r.v12;
	outMat->v13 = outMat->v13 + r.v13;
	
	outMat->v20 = outMat->v20 + r.v20;
	outMat->v21 = outMat->v21 + r.v21;
	outMat->v22 = outMat->v22 + r.v22;
	outMat->v23 = outMat->v23 + r.v23;
	
	outMat->v30 = outMat->v30 + r.v30;
	outMat->v31 = outMat->v31 + r.v31;
	outMat->v32 = outMat->v32 + r.v32;
	outMat->v33 = outMat->v33 + r.v33;
	
}

void    Mat44dSubInplace(const Mat44d& FDK_RESTRICT r, Mat44d* FDK_RESTRICT outMat) {
	//outMat = outMat + r
	outMat->v00 = outMat->v00 - r.v00;
	outMat->v01 = outMat->v01 - r.v01;
	outMat->v02 = outMat->v02 - r.v02;
	outMat->v03 = outMat->v03 - r.v03;
	
	outMat->v10 = outMat->v10 - r.v10;
	outMat->v11 = outMat->v11 - r.v11;
	outMat->v12 = outMat->v12 - r.v12;
	outMat->v13 = outMat->v13 - r.v13;
	
	outMat->v20 = outMat->v20 - r.v20;
	outMat->v21 = outMat->v21 - r.v21;
	outMat->v22 = outMat->v22 - r.v22;
	outMat->v23 = outMat->v23 - r.v23;
	
	outMat->v30 = outMat->v30 - r.v30;
	outMat->v31 = outMat->v31 - r.v31;
	outMat->v32 = outMat->v32 - r.v32;
	outMat->v33 = outMat->v33 - r.v33;
	
}


void    Mat44dMultInplace(const Mat44d& FDK_RESTRICT r, Mat44d* FDK_RESTRICT outMat) {
	//outMat = outMat * r
	Mat44d temp = *outMat;
	
	outMat->v00 = temp.v00 * r.v00 + temp.v01 * r.v10 + temp.v02 * r.v20 + temp.v03 * r.v30;
	outMat->v01 = temp.v00 * r.v01 + temp.v01 * r.v11 + temp.v02 * r.v21 + temp.v03 * r.v31;
	outMat->v02 = temp.v00 * r.v02 + temp.v01 * r.v12 + temp.v02 * r.v22 + temp.v03 * r.v32;
	outMat->v03 = temp.v00 * r.v03 + temp.v01 * r.v13 + temp.v02 * r.v23 + temp.v03 * r.v33;
	
	outMat->v10 = temp.v10 * r.v00 + temp.v11 * r.v10 + temp.v12 * r.v20 + temp.v13 * r.v30;
	outMat->v11 = temp.v10 * r.v01 + temp.v11 * r.v11 + temp.v12 * r.v21 + temp.v13 * r.v31;
	outMat->v12 = temp.v10 * r.v02 + temp.v11 * r.v12 + temp.v12 * r.v22 + temp.v13 * r.v32;
	outMat->v13 = temp.v10 * r.v03 + temp.v11 * r.v13 + temp.v12 * r.v23 + temp.v13 * r.v33;
	
	outMat->v20 = temp.v20 * r.v00 + temp.v21 * r.v10 + temp.v22 * r.v20 + temp.v23 * r.v30;
	outMat->v21 = temp.v20 * r.v01 + temp.v21 * r.v11 + temp.v22 * r.v21 + temp.v23 * r.v31;
	outMat->v22 = temp.v20 * r.v02 + temp.v21 * r.v12 + temp.v22 * r.v22 + temp.v23 * r.v32;
	outMat->v23 = temp.v20 * r.v03 + temp.v21 * r.v13 + temp.v22 * r.v23 + temp.v23 * r.v33;
	
	outMat->v30 = temp.v30 * r.v00 + temp.v31 * r.v10 + temp.v32 * r.v20 + temp.v33 * r.v30;
	outMat->v31 = temp.v30 * r.v01 + temp.v31 * r.v11 + temp.v32 * r.v21 + temp.v33 * r.v31;
	outMat->v32 = temp.v30 * r.v02 + temp.v31 * r.v12 + temp.v32 * r.v22 + temp.v33 * r.v32;
	outMat->v33 = temp.v30 * r.v03 + temp.v31 * r.v13 + temp.v32 * r.v23 + temp.v33 * r.v33;
	
}

bool 	Mat44dInvertInplace(Mat44d* FDK_RESTRICT outMat) {
	//determinant matrix 4x4
	F64 determinant = Mat44dDeterminant(*outMat);
	
	//Determinant must be different from zero, else matrix can't be inverted.
	if (determinant == 0)
		return false;
	
	Mat44d temp = *outMat;
	
	
	//Invert
	
	outMat->v00 = (1.0/determinant) * (temp.v11 * temp.v22 * temp.v33 + temp.v12 * temp.v23 * temp.v31 + temp.v13 * temp.v21 * temp.v32 - temp.v11 * temp.v23 * temp.v32 - temp.v12 * temp.v21 * temp.v33 - temp.v13 * temp.v22 * temp.v31);
	
	outMat->v01 = (1.0/determinant) * (temp.v01 * temp.v23 * temp.v32 + temp.v02 * temp.v21 * temp.v33 + temp.v03 * temp.v22 * temp.v31 - temp.v01 * temp.v22 * temp.v33 - temp.v02 * temp.v23 * temp.v31 - temp.v03 * temp.v21 * temp.v32);
	
	outMat->v02 = (1.0/determinant) * (temp.v01 * temp.v12 * temp.v33 + temp.v02 * temp.v13 * temp.v31 + temp.v03 * temp.v11 * temp.v32 - temp.v01 * temp.v13 * temp.v32 - temp.v02 * temp.v11 * temp.v33 - temp.v03 * temp.v12 * temp.v31);
	
	outMat->v03 = (1.0/determinant) * (temp.v01 * temp.v13 * temp.v22 + temp.v02 * temp.v11 * temp.v23 + temp.v03 * temp.v12 * temp.v21 - temp.v01 * temp.v12 * temp.v23 - temp.v02 * temp.v13 * temp.v21 - temp.v03 * temp.v11 * temp.v22);
	
	outMat->v10 = (1.0/determinant) * (temp.v10 * temp.v23 * temp.v32 + temp.v12 * temp.v20 * temp.v33 + temp.v13 * temp.v22 * temp.v30 - temp.v10 * temp.v22 * temp.v33 - temp.v12 * temp.v23 * temp.v30 - temp.v13 * temp.v20 * temp.v32);
	
	outMat->v11 = (1.0/determinant) * (temp.v00 * temp.v22 * temp.v33 + temp.v02 * temp.v23 * temp.v30 + temp.v03 * temp.v20 * temp.v32 - temp.v00 * temp.v23 * temp.v32 - temp.v02 * temp.v20 * temp.v33 - temp.v03 * temp.v22 * temp.v30);
	
	outMat->v12 = (1.0/determinant) * (temp.v00 * temp.v13 * temp.v32 + temp.v02 * temp.v10 * temp.v33 + temp.v03 * temp.v12 * temp.v30 - temp.v00 * temp.v12 * temp.v33 - temp.v02 * temp.v13 * temp.v30 - temp.v03 * temp.v10 * temp.v32);
	
	outMat->v13 = (1.0/determinant) * (temp.v00 * temp.v12 * temp.v23 + temp.v02 * temp.v13 * temp.v20 + temp.v03 * temp.v10 * temp.v22 - temp.v00 * temp.v13 * temp.v22 - temp.v02 * temp.v10 * temp.v23 - temp.v03 * temp.v12 * temp.v20);
	
	outMat->v20 = (1.0/determinant) * (temp.v10 * temp.v21 * temp.v33 + temp.v11 * temp.v23 * temp.v30 + temp.v13 * temp.v20 * temp.v31 - temp.v10 * temp.v23 * temp.v31 - temp.v11 * temp.v20 * temp.v33 - temp.v13 * temp.v21 * temp.v30);
	
	outMat->v21 = (1.0/determinant) * (temp.v00 * temp.v23 * temp.v31 + temp.v01 * temp.v20 * temp.v33 + temp.v03 * temp.v21 * temp.v30 - temp.v00 * temp.v21 * temp.v33 - temp.v01 * temp.v23 * temp.v30 - temp.v03 * temp.v20 * temp.v31);
	
	outMat->v22 = (1.0/determinant) * (temp.v00 * temp.v11 * temp.v33 + temp.v01 * temp.v13 * temp.v30 + temp.v03 * temp.v10 * temp.v31 - temp.v00 * temp.v13 * temp.v31 - temp.v01 * temp.v10 * temp.v33 - temp.v03 * temp.v11 * temp.v30);
	
	outMat->v23 = (1.0/determinant) * (temp.v00 * temp.v13 * temp.v21 + temp.v01 * temp.v10 * temp.v23 + temp.v03 * temp.v11 * temp.v20 - temp.v00 * temp.v11 * temp.v23 - temp.v01 * temp.v13 * temp.v20 - temp.v03 * temp.v10 * temp.v21);
	
	outMat->v30 = (1.0/determinant) * (temp.v10 * temp.v22 * temp.v31 + temp.v11 * temp.v20 * temp.v32 + temp.v12 * temp.v21 * temp.v30 - temp.v10 * temp.v21 * temp.v32 - temp.v11 * temp.v22 * temp.v30 - temp.v12 * temp.v20 * temp.v31);
	
	outMat->v31 = (1.0/determinant) * (temp.v00 * temp.v21 * temp.v32 + temp.v01 * temp.v22 * temp.v30 + temp.v02 * temp.v20 * temp.v31 - temp.v00 * temp.v22 * temp.v31 - temp.v01 * temp.v20 * temp.v32 - temp.v02 * temp.v21 * temp.v30);
	
	outMat->v32 = (1.0/determinant) * (temp.v00 * temp.v12 * temp.v31 + temp.v01 * temp.v10 * temp.v32 + temp.v02 * temp.v11 * temp.v30 - temp.v00 * temp.v11 * temp.v32 - temp.v01 * temp.v12 * temp.v30 - temp.v02 * temp.v10 * temp.v31);
	
	outMat->v33 = (1.0/determinant) * (temp.v00 * temp.v11 * temp.v22 + temp.v01 * temp.v12 * temp.v20 + temp.v02 * temp.v10 * temp.v21 - temp.v00 * temp.v12 * temp.v21 - temp.v01 * temp.v10 * temp.v22 - temp.v02 * temp.v11 * temp.v20);
	
	
	return true;
}

void 	Mat44dTransposeInplace(Mat44d* FDK_RESTRICT outMat) {
	//transpose the matrix 3x3
	Mat44d temp = Mat44d( outMat->v00, outMat->v01, outMat->v02, outMat->v03, outMat->v10, outMat->v11, outMat->v12, outMat->v13, outMat->v20, outMat->v21, outMat->v22, outMat->v23, outMat->v30, outMat->v31, outMat->v32, outMat->v33);
	
	//transpose the matrix 4x4
	outMat->v00 = temp.v00;
	outMat->v01 = temp.v10;
	outMat->v02 = temp.v20;
	outMat->v03 = temp.v30;
	
	outMat->v10 = temp.v01;
	outMat->v11 = temp.v11;
	outMat->v12 = temp.v21;
	outMat->v13 = temp.v31;
	
	outMat->v20 = temp.v02;
	outMat->v21 = temp.v12;
	outMat->v22 = temp.v22;
	outMat->v23 = temp.v32;
	
	outMat->v30 = temp.v03;
	outMat->v31 = temp.v13;
	outMat->v32 = temp.v23;
	outMat->v33 = temp.v33;
	
}

FDK_NS_END