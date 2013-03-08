// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/mat22h.h"
#include "fdk/mathf.h"


FDK_NS_BEGIN

void    Mat22hInit(Mat22h* outMat) {
	//with identity matrix
	F16 one = toFloat16(1.0f);
	outMat->v00 = one;
	outMat->v01 = 0;
	outMat->v10 = 0;
	outMat->v11 = one;
}

void    Mat22hInitWithValue(const F16 value, Mat22h* outMat) {
	outMat->v00 = value;
	outMat->v01 = value;
	outMat->v10 = value;
	outMat->v11 = value;
}

void    Mat22hInitWithRowVec(const Vec2h& row0, const Vec2h& row1, Mat22h* outMat) {
	outMat->v00 = row0.x;
	outMat->v01 = row0.y;
	outMat->v10 = row1.x;
	outMat->v11 = row1.y;
}

void    Mat22hInitWithColumnVec(const Vec2h& column0, const Vec2h& column1, Mat22h* outMat) {
	outMat->v00 = column0.x;
	outMat->v10 = column0.y;
	outMat->v01 = column1.x;
	outMat->v11 = column1.y;
}

void    Mat22hGetColumn(const Mat22h&   inMat22h, int column, Vec2h* outVec) {
	
	FDK_ASSERT(column >= 0 && column < 2);
	
	if (column == 0) {
		outVec->x = inMat22h.v00;
		outVec->y = inMat22h.v10;
	}
	if (column == 1) {
		outVec->x = inMat22h.v01;
		outVec->y = inMat22h.v11;
	}
}

void    Mat22hGetRow(const Mat22h&   inMat22h, int row, Vec2h* outVec) {
	
	FDK_ASSERT(row >= 0 && row < 2);
	
	if (row == 0) {
		outVec->x = inMat22h.v00;
		outVec->y = inMat22h.v01;
	}
	if (row == 1) {
		outVec->x = inMat22h.v10;
		outVec->y = inMat22h.v11;
	}
}

void    Mat22hSum(const Mat22h&   l, const Mat22h&  r, Mat22h*  outMat) {
	//outMat = l + r
	Mat22f lf;
	Mat22hToMat22f(l, &lf);
	Mat22f rf;
	Mat22hToMat22f(r, &rf);
	Mat22f outMatF;
	Mat22fSum(lf, rf, &outMatF);
	Mat22fToMat22h(outMatF, outMat);
}

void    Mat22hSub(const Mat22h&   l, const Mat22h&  r, Mat22h*  outMat) {
	//outMat = l - r
	Mat22f lf;
	Mat22hToMat22f(l, &lf);
	Mat22f rf;
	Mat22hToMat22f(r, &rf);
	Mat22f outMatF;
	Mat22fSub(lf, rf, &outMatF);
	Mat22fToMat22h(outMatF, outMat);
}

void    Mat22hAbs(const Mat22h&   l, Mat22h*  outMat) {
	outMat->v00 = Fabsh(l.v00);
	outMat->v01 = Fabsh(l.v01);
	outMat->v10 = Fabsh(l.v10);
	outMat->v11 = Fabsh(l.v11);
}

F16     Mat22hDeterminant(const Mat22h&   inMat22h) {
	Mat22f mat22f;
	Mat22hToMat22f(inMat22h, &mat22f);
	F32 detf = mat22f.v00 * mat22f.v11 - mat22f.v01 * mat22f.v10;
	F16 deth = toFloat16(detf);
	return deth;
}

void    Mat22hMult(const Mat22h&   l, const Mat22h&  r, Mat22h*  outMat) {
	//outMat = l * r
	Mat22f lf;
	Mat22hToMat22f(l, &lf);
	Mat22f rf;
	Mat22hToMat22f(r, &rf);
	Mat22f outMatf;
	Mat22fMult(lf, rf, &outMatf);
	Mat22fToMat22h(outMatf, outMat);
}

bool 	Mat22hInvert(const Mat22h&  inMat22h, Mat22h*  outMat) {
	Mat22f outMatf;
	Mat22hToMat22f(inMat22h, &outMatf);
	bool ret = Mat22fInvertInplace(&outMatf);
	Mat22fToMat22h(outMatf, outMat);
	return ret;
}

void 	Mat22hTranspose(const Mat22h&  inMat22h, Mat22h*  outMat) {
	//transpose the matrix 2x2
	outMat->v00 = inMat22h.v00;
	outMat->v01 = inMat22h.v10;
	outMat->v10 = inMat22h.v01;
	outMat->v11 = inMat22h.v11;
}

void  Mat22hMultVector(const Mat22h&  inMat22h, const Vec2h& inVec2h, Vec2h* outVec) {
	Mat22f outMatf;
	Mat22hToMat22f(inMat22h, &outMatf);
	Vec2f vecf;
	Vec2hToVec2f(inVec2h, &vecf);
	Vec2f outVecf;
	Mat22fMultVector(outMatf, vecf, &outVecf);
	outVec->x = toFloat16(outVecf.x);
	outVec->y = toFloat16(outVecf.y);
}

void   Mat22hToMat22f        (const Mat22h&   inMat22h, Mat22f*  outMat22f) {
	outMat22f->v00 = toFloat32(inMat22h.v00);
	outMat22f->v01 = toFloat32(inMat22h.v01);
	outMat22f->v10 = toFloat32(inMat22h.v10);
	outMat22f->v11 = toFloat32(inMat22h.v11);
}

void   Mat22fToMat22h        (const Mat22f&   inMat22f, Mat22h*  outMat22h) {
	outMat22h->v00 = toFloat16(inMat22f.v00);
	outMat22h->v01 = toFloat16(inMat22f.v01);
	outMat22h->v10 = toFloat16(inMat22f.v10);
	outMat22h->v11 = toFloat16(inMat22f.v11);
}

//Inplace

void    Mat22hSumInplace(const Mat22h&  r, Mat22h*  outMat) {
	//outMat = outMat + r
	Mat22f rf;
	Mat22hToMat22f(r, &rf);
	Mat22f outMatf;
	Mat22hToMat22f(*outMat, &outMatf);
	Mat22fSumInplace(rf, &outMatf);
	Mat22fToMat22h(outMatf, outMat);
}

void    Mat22hSubInplace(const Mat22h&  r, Mat22h*  outMat) {
	//outMat = outMat + r
	Mat22f rf;
	Mat22hToMat22f(r, &rf);
	Mat22f outMatf;
	Mat22hToMat22f(*outMat, &outMatf);
	Mat22fSubInplace(rf, &outMatf);
	Mat22fToMat22h(outMatf, outMat);
}

void    Mat22hMultInplace(const Mat22h&  r, Mat22h*  outMat) {
	//outMat = outMat * r
	Mat22f rf;
	Mat22hToMat22f(r, &rf);
	Mat22f outMatf;
	Mat22hToMat22f(*outMat, &outMatf);
	Mat22fMultInplace(rf, &outMatf);
	Mat22fToMat22h(outMatf, outMat);
}

bool 	Mat22hInvertInplace(Mat22h*  outMat) {
	Mat22f outMatf;
	Mat22hToMat22f(*outMat, &outMatf);
	bool ret = Mat22fInvertInplace(&outMatf);
	Mat22fToMat22h(outMatf, outMat);
	return ret;
}

void 	Mat22hTransposeInplace(Mat22h*  outMat) {
	//transpose the matrix 2x2
	Mat22h temp = Mat22h( outMat->v00, outMat->v01, outMat->v10, outMat->v11);
	
	outMat->v00 = temp.v00;
	outMat->v01 = temp.v10;
	outMat->v10 = temp.v01;
	outMat->v11 = temp.v11;
}

FDK_NS_END