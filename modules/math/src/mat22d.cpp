// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/Mat22d.h"
#include "fdk/mathd.h"


FDK_NS_BEGIN

void    Mat22dInit(Mat22d* outMat) {
	//with identity matrix
	outMat->v00 = 1.0;
	outMat->v01 = 0.0;
	outMat->v10 = 0.0;
	outMat->v11 = 1.0;
}

void    Mat22dInitWithValue(const F64 value, Mat22d* outMat) {
	outMat->v00 = value;
	outMat->v01 = value;
	outMat->v10 = value;
	outMat->v11 = value;
}

void    Mat22dInitWithRowVec(const Vec2d& row0, const Vec2d& row1, Mat22d* outMat) {
	outMat->v00 = row0.x;
	outMat->v01 = row0.y;
	outMat->v10 = row1.x;
	outMat->v11 = row1.y;
}

void    Mat22dInitWithColumnVec(const Vec2d& column0, const Vec2d& column1, Mat22d* outMat) {
	outMat->v00 = column0.x;
	outMat->v10 = column0.y;
	outMat->v01 = column1.x;
	outMat->v11 = column1.y;
}

void    Mat22dGetColumn(const Mat22d& FDK_RESTRICT  inMat22d, int column, Vec2d* outVec) {
	
	FDK_ASSERT(column >= 0 && column < 2);
	
	if (column == 0) {
		outVec->x = inMat22d.v00;
		outVec->y = inMat22d.v10;
	}
	if (column == 1) {
		outVec->x = inMat22d.v01;
		outVec->y = inMat22d.v11;
	}
}

void    Mat22dGetRow(const Mat22d& FDK_RESTRICT  inMat22d, int row, Vec2d* outVec) {
	
	FDK_ASSERT(row >= 0 && row < 2);
	
	if (row == 0) {
		outVec->x = inMat22d.v00;
		outVec->y = inMat22d.v01;
	}
	if (row == 1) {
		outVec->x = inMat22d.v10;
		outVec->y = inMat22d.v11;
	}
}

void    Mat22dSum(const Mat22d& FDK_RESTRICT  l, const Mat22d& FDK_RESTRICT r, Mat22d* FDK_RESTRICT outMat) {
	//outMat = l + r
	outMat->v00 = l.v00 + r.v00;
	outMat->v01 = l.v01 + r.v01;
	outMat->v10 = l.v10 + r.v10;
	outMat->v11 = l.v11 + r.v11;
}

void    Mat22dSub(const Mat22d& FDK_RESTRICT  l, const Mat22d& FDK_RESTRICT r, Mat22d* FDK_RESTRICT outMat) {
	//outMat = l - r
	outMat->v00 = l.v00 - r.v00;
	outMat->v01 = l.v01 - r.v01;
	outMat->v10 = l.v10 - r.v10;
	outMat->v11 = l.v11 - r.v11;
}

void    Mat22dAbs(const Mat22d& FDK_RESTRICT  l, Mat22d* FDK_RESTRICT outMat) {
	outMat->v00 = Fabsd(l.v00);
	outMat->v01 = Fabsd(l.v01);
	outMat->v10 = Fabsd(l.v10);
	outMat->v11 = Fabsd(l.v11);
}

F64     Mat22dDeterminant(const Mat22d& FDK_RESTRICT  inMat22d) {
	return inMat22d.v00 * inMat22d.v11 - inMat22d.v01 * inMat22d.v10;
}

void    Mat22dMult(const Mat22d& FDK_RESTRICT  l, const Mat22d& FDK_RESTRICT r, Mat22d* FDK_RESTRICT outMat) {
	//outMat = l * r
	outMat->v00 = l.v00 * r.v00 + l.v01 * r.v10;
	outMat->v01 = l.v00 * r.v01 + l.v01 * r.v11;
	outMat->v10 = l.v10 * r.v00 + l.v11 * r.v10;
	outMat->v11 = l.v10 * r.v01 + l.v11 * r.v11;
	
}

bool 	Mat22dInvert(const Mat22d& FDK_RESTRICT inMat22d, Mat22d* FDK_RESTRICT outMat) {
	//Invert the matrix 2x2
	
	//determinant matrix 2x2
	//F64 determinant = inMat22d.v00 * inMat22d.v11 - inMat22d.v01 * inMat22d.v10;
	F64 determinant = Mat22dDeterminant(inMat22d);
	
	//Determinant must be different from zero, else matrix can't be inverted.
	if (determinant == 0)
		return false;
	
	//Invert
	outMat->v00 =   (1/determinant) * inMat22d.v11;
	outMat->v01 =  -(1/determinant) * inMat22d.v01;
	outMat->v10 =  -(1/determinant) * inMat22d.v10;
	outMat->v11 =   (1/determinant) * inMat22d.v00;
	return true;
}

void 	Mat22dTranspose(const Mat22d& FDK_RESTRICT inMat22d, Mat22d* FDK_RESTRICT outMat) {
	//transpose the matrix 2x2
	outMat->v00 = inMat22d.v00;
	outMat->v01 = inMat22d.v10;
	outMat->v10 = inMat22d.v01;
	outMat->v11 = inMat22d.v11;
}

void  Mat22dMultVector(const Mat22d&  inMat22d, const Vec2d& inVec2d, Vec2d* outVec) {
	outVec->x = inMat22d.v00 * inVec2d.x +  inMat22d.v01 * inVec2d.y;
	outVec->y = inMat22d.v10 * inVec2d.x +  inMat22d.v11 * inVec2d.y;
}

//Inplace

void    Mat22dSumInplace(const Mat22d& FDK_RESTRICT r, Mat22d* FDK_RESTRICT outMat) {
	//outMat = outMat + r
	outMat->v00 = outMat->v00 + r.v00;
	outMat->v01 = outMat->v01 + r.v01;
	outMat->v10 = outMat->v10 + r.v10;
	outMat->v11 = outMat->v11 + r.v11;
}

void    Mat22dSubInplace(const Mat22d& FDK_RESTRICT r, Mat22d* FDK_RESTRICT outMat) {
	//outMat = outMat + r
	outMat->v00 = outMat->v00 - r.v00;
	outMat->v01 = outMat->v01 - r.v01;
	outMat->v10 = outMat->v10 - r.v10;
	outMat->v11 = outMat->v11 - r.v11;
}

void    Mat22dMultInplace(const Mat22d& FDK_RESTRICT r, Mat22d* FDK_RESTRICT outMat) {
	//outMat = outMat * r
	Mat22d temp = *outMat;
	outMat->v00 = temp.v00 * r.v00 + temp.v01 * r.v10;
	outMat->v01 = temp.v00 * r.v01 + temp.v01 * r.v11;
	outMat->v10 = temp.v10 * r.v00 + temp.v11 * r.v10;
	outMat->v11 = temp.v10 * r.v01 + temp.v11 * r.v11;
}

bool 	Mat22dInvertInplace(Mat22d* FDK_RESTRICT outMat) {
	//Invert the matrix 2x2
	
	Mat22d temp = *outMat;
	
	//determinant matrix 2x2
	//F64 determinant = outMat->v00 * outMat->v11 - outMat->v01 * outMat->v10;
	F64 determinant = Mat22dDeterminant(*outMat);
	
	//Determinant must be different from zero, else matrix can't be inverted.
	if (determinant == 0)
		return false;
	
	//Invert
	outMat->v00 =   (1/determinant) * temp.v11;
	outMat->v01 =  -(1/determinant) * temp.v01;
	outMat->v10 =  -(1/determinant) * temp.v10;
	outMat->v11 =   (1/determinant) * temp.v00;
	return true;
}

void 	Mat22dTransposeInplace(Mat22d* FDK_RESTRICT outMat) {
	//transpose the matrix 2x2
	Mat22d temp = Mat22d( outMat->v00, outMat->v01, outMat->v10, outMat->v11);
	
	outMat->v00 = temp.v00;
	outMat->v01 = temp.v10;
	outMat->v10 = temp.v01;
	outMat->v11 = temp.v11;
}

FDK_NS_END