// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/mat22f.h"
#include "fdk/mathf.h"


FDK_NS_BEGIN

void    Mat22fInit(Mat22f* outMat) {
	//with identity matrix
	outMat->v00 = 1.f;
	outMat->v01 = 0.f;
	outMat->v10 = 0.f;
	outMat->v11 = 1.f;
}

void    Mat22fInitWithValue(const F32 value, Mat22f* outMat) {
	outMat->v00 = value;
	outMat->v01 = value;
	outMat->v10 = value;
	outMat->v11 = value;
}

void    Mat22fInitWithRowVec(const Vec2f& row0, const Vec2f& row1, Mat22f* outMat) {
	outMat->v00 = row0.x;
	outMat->v01 = row0.y;
	outMat->v10 = row1.x;
	outMat->v11 = row1.y;
}

void    Mat22fInitWithColumnVec(const Vec2f& column0, const Vec2f& column1, Mat22f* outMat) {
	outMat->v00 = column0.x;
	outMat->v10 = column0.y;
	outMat->v01 = column1.x;
	outMat->v11 = column1.y;
}

void    Mat22fGetColumn(const Mat22f& FDK_RESTRICT  inMat22f, int column, Vec2f* outVec) {
	
	FDK_ASSERT(column >= 0 && column < 2);
	
	if (column == 0) {
		outVec->x = inMat22f.v00;
		outVec->y = inMat22f.v10;
	}
	if (column == 1) {
		outVec->x = inMat22f.v01;
		outVec->y = inMat22f.v11;
	}
}

void    Mat22fGetRow(const Mat22f& FDK_RESTRICT  inMat22f, int row, Vec2f* outVec) {
	
	FDK_ASSERT(row >= 0 && row < 2);
	
	if (row == 0) {
		outVec->x = inMat22f.v00;
		outVec->y = inMat22f.v01;
	}
	if (row == 1) {
		outVec->x = inMat22f.v10;
		outVec->y = inMat22f.v11;
	}
}

void    Mat22fSum(const Mat22f& FDK_RESTRICT  l, const Mat22f& FDK_RESTRICT r, Mat22f* FDK_RESTRICT outMat) {
	//outMat = l + r
	outMat->v00 = l.v00 + r.v00;
	outMat->v01 = l.v01 + r.v01;
	outMat->v10 = l.v10 + r.v10;
	outMat->v11 = l.v11 + r.v11;
}

void    Mat22fSub(const Mat22f& FDK_RESTRICT  l, const Mat22f& FDK_RESTRICT r, Mat22f* FDK_RESTRICT outMat) {
	//outMat = l - r
	outMat->v00 = l.v00 - r.v00;
	outMat->v01 = l.v01 - r.v01;
	outMat->v10 = l.v10 - r.v10;
	outMat->v11 = l.v11 - r.v11;
}

void    Mat22fAbs(const Mat22f& FDK_RESTRICT  l, Mat22f* FDK_RESTRICT outMat) {
	outMat->v00 = Fabsf(l.v00);
	outMat->v01 = Fabsf(l.v01);
	outMat->v10 = Fabsf(l.v10);
	outMat->v11 = Fabsf(l.v11);
}

F32     Mat22fDeterminant(const Mat22f& FDK_RESTRICT  inMat22f) {
	return inMat22f.v00 * inMat22f.v11 - inMat22f.v01 * inMat22f.v10;
}

void    Mat22fMult(const Mat22f& FDK_RESTRICT  l, const Mat22f& FDK_RESTRICT r, Mat22f* FDK_RESTRICT outMat) {
	//outMat = l * r
	outMat->v00 = l.v00 * r.v00 + l.v01 * r.v10;
	outMat->v01 = l.v00 * r.v01 + l.v01 * r.v11;
	outMat->v10 = l.v10 * r.v00 + l.v11 * r.v10;
	outMat->v11 = l.v10 * r.v01 + l.v11 * r.v11;
	 
}

bool 	Mat22fInvert(const Mat22f& FDK_RESTRICT inMat22f, Mat22f* FDK_RESTRICT outMat) {
	//Invert the matrix 2x2

	//determinant matrix 2x2
	//F32 determinant = inMat22f.v00 * inMat22f.v11 - inMat22f.v01 * inMat22f.v10;
	F32 determinant = Mat22fDeterminant(inMat22f);
	
	//Determinant must be different from zero, else matrix can't be inverted.
	if (determinant == 0)
		return false;
	
	//Invert
	outMat->v00 =   (1/determinant) * inMat22f.v11;
	outMat->v01 =  -(1/determinant) * inMat22f.v01;
	outMat->v10 =  -(1/determinant) * inMat22f.v10;
	outMat->v11 =   (1/determinant) * inMat22f.v00;
	return true;
}

void 	Mat22fTranspose(const Mat22f& FDK_RESTRICT inMat22f, Mat22f* FDK_RESTRICT outMat) {
	//transpose the matrix 2x2
	outMat->v00 = inMat22f.v00;
	outMat->v01 = inMat22f.v10;
	outMat->v10 = inMat22f.v01;
	outMat->v11 = inMat22f.v11;
}

void  Mat22fMultVector(const Mat22f&  inMat22f, const Vec2f& inVec2f, Vec2f* outVec) {
	outVec->x = inMat22f.v00 * inVec2f.x +  inMat22f.v01 * inVec2f.y;
	outVec->y = inMat22f.v10 * inVec2f.x +  inMat22f.v11 * inVec2f.y;
}

//Inplace

void    Mat22fSumInplace(const Mat22f& FDK_RESTRICT r, Mat22f* FDK_RESTRICT outMat) {
	//outMat = outMat + r
	outMat->v00 = outMat->v00 + r.v00;
	outMat->v01 = outMat->v01 + r.v01;
	outMat->v10 = outMat->v10 + r.v10;
	outMat->v11 = outMat->v11 + r.v11;
}

void    Mat22fSubInplace(const Mat22f& FDK_RESTRICT r, Mat22f* FDK_RESTRICT outMat) {
	//outMat = outMat + r
	outMat->v00 = outMat->v00 - r.v00;
	outMat->v01 = outMat->v01 - r.v01;
	outMat->v10 = outMat->v10 - r.v10;
	outMat->v11 = outMat->v11 - r.v11;
}

void    Mat22fMultInplace(const Mat22f& FDK_RESTRICT r, Mat22f* FDK_RESTRICT outMat) {
	//outMat = outMat * r
	Mat22f temp = *outMat;
	outMat->v00 = temp.v00 * r.v00 + temp.v01 * r.v10;
	outMat->v01 = temp.v00 * r.v01 + temp.v01 * r.v11;
	outMat->v10 = temp.v10 * r.v00 + temp.v11 * r.v10;
	outMat->v11 = temp.v10 * r.v01 + temp.v11 * r.v11;
}

bool 	Mat22fInvertInplace(Mat22f* FDK_RESTRICT outMat) {
	//Invert the matrix 2x2
	
	Mat22f temp = *outMat;
	
	//determinant matrix 2x2
	//F32 determinant = outMat->v00 * outMat->v11 - outMat->v01 * outMat->v10;
	F32 determinant = Mat22fDeterminant(*outMat);
	
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

void 	Mat22fTransposeInplace(Mat22f* FDK_RESTRICT outMat) {
	//transpose the matrix 2x2
	Mat22f temp = Mat22f( outMat->v00, outMat->v01, outMat->v10, outMat->v11);
	
	outMat->v00 = temp.v00;
	outMat->v01 = temp.v10;
	outMat->v10 = temp.v01;
	outMat->v11 = temp.v11;
}

FDK_NS_END