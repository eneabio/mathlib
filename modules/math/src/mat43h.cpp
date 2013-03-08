// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/mat43h.h"
#include "fdk/mat43f.h"
#include "fdk/mathf.h"

FDK_NS_BEGIN

void    Mat43hInit(Mat43h* outMat) {
	F16 one = toFloat16(1.0f);
	outMat->v00 = one;
	outMat->v01 = 0;
	outMat->v02 = 0;
	
	outMat->v10 = 0;
	outMat->v11 = one;
	outMat->v12 = 0;
	
	outMat->v20 = 0;
	outMat->v21 = 0;
	outMat->v22 = one;
	
	outMat->v30 = 0;
	outMat->v31 = 0;
	outMat->v32 = one;
	
}

void    Mat43hInitWithValue(const F16 value, Mat43h* outMat) {
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

void    Mat43hInitWithRowVec(const Vec3h& row0, const Vec3h& row1, const Vec3h& row2, const Vec3h& row3,Mat43h* outMat) {
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

void    Mat43hInitWithColumnVec(const Vec4h& column0, const Vec4h& column1, const Vec4h& column2, Mat43h* outMat) {
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

void    Mat43hGetColumn(const Mat43h&   inMat43h, int column, Vec4h* outVec) {
	
	FDK_ASSERT(column >= 0 && column < 3);
	
	if (column == 0) {
		outVec->x = inMat43h.v00;
		outVec->y = inMat43h.v10;
		outVec->z = inMat43h.v20;
		outVec->w = inMat43h.v30;
	}
	if (column == 1) {
		outVec->x = inMat43h.v01;
		outVec->y = inMat43h.v11;
		outVec->z = inMat43h.v21;
		outVec->w = inMat43h.v31;
	}
	if (column == 2) {
		outVec->x = inMat43h.v02;
		outVec->y = inMat43h.v12;
		outVec->z = inMat43h.v22;
		outVec->w = inMat43h.v32;
	}
	
}

void    Mat43hGetRow(const Mat43h&   inMat43h, int row, Vec3h* outVec) {
	
	FDK_ASSERT(row >= 0 && row <= 3);
	
	if (row == 0) {
		outVec->x = inMat43h.v00;
		outVec->y = inMat43h.v01;
		outVec->z = inMat43h.v02;
	}
	if (row == 1) {
		outVec->x = inMat43h.v10;
		outVec->y = inMat43h.v11;
		outVec->z = inMat43h.v12;
	}
	if (row == 2) {
		outVec->x = inMat43h.v20;
		outVec->y = inMat43h.v21;
		outVec->z = inMat43h.v22;
	}
	if (row == 3) {
		outVec->x = inMat43h.v30;
		outVec->y = inMat43h.v31;
		outVec->z = inMat43h.v32;
	}
}

void    Mat43hSum(const Mat43h&   l, const Mat43h&  r, Mat43h*  outMat) {
	//outMat = l + r
	Mat43f lf;
	Mat43hToMat43f(l, &lf);
	Mat43f rf;
	Mat43hToMat43f(r, &rf);
	Mat43f outMatF;
	Mat43fSum(lf, rf, &outMatF);
	Mat43fToMat43h(outMatF, outMat);
	
}

void    Mat43hSub(const Mat43h&   l, const Mat43h&  r, Mat43h*  outMat) {
	//outMat = l - r
	Mat43f lf;
	Mat43hToMat43f(l, &lf);
	Mat43f rf;
	Mat43hToMat43f(r, &rf);
	Mat43f outMatF;
	Mat43fSub(lf, rf, &outMatF);
	Mat43fToMat43h(outMatF, outMat);
	
}

void    Mat43hAbs(const Mat43h&   l, Mat43h*  outMat) {
	
	outMat->v00 = Fabsh(l.v00);
	outMat->v01 = Fabsh(l.v01);
	outMat->v02 = Fabsh(l.v02);
	
	outMat->v10 = Fabsh(l.v10);
	outMat->v11 = Fabsh(l.v11);
	outMat->v12 = Fabsh(l.v12);
	
	outMat->v20 = Fabsh(l.v20);
	outMat->v21 = Fabsh(l.v21);
	outMat->v22 = Fabsh(l.v22);
	
	outMat->v30 = Fabsh(l.v30);
	outMat->v31 = Fabsh(l.v31);
	outMat->v32 = Fabsh(l.v32);
	
}

void    Mat43hMultVector(const Mat43h&  inMat43h, const Vec3h& inVec3h, Vec4h* outVec) {
	Mat43f outMatf;
	Mat43hToMat43f(inMat43h, &outMatf);
	Vec3f vecf;
	Vec3hToVec3f(inVec3h, &vecf);
	Vec4f outVecf;
	Mat43fMultVector(outMatf, vecf, &outVecf);
	outVec->x = toFloat16(outVecf.x);
	outVec->y = toFloat16(outVecf.y);
	outVec->z = toFloat16(outVecf.z);
	outVec->w = toFloat16(outVecf.w);
}

void   Mat43hToMat43f        (const Mat43h&   inMat43h, Mat43f*  outMat43f) {
	outMat43f->v00 = toFloat32(inMat43h.v00);
	outMat43f->v01 = toFloat32(inMat43h.v01);
	outMat43f->v02 = toFloat32(inMat43h.v02);
	
	outMat43f->v10 = toFloat32(inMat43h.v10);
	outMat43f->v11 = toFloat32(inMat43h.v11);
	outMat43f->v12 = toFloat32(inMat43h.v12);
	
	outMat43f->v20 = toFloat32(inMat43h.v20);
	outMat43f->v21 = toFloat32(inMat43h.v21);
	outMat43f->v22 = toFloat32(inMat43h.v22);
	
	outMat43f->v30 = toFloat32(inMat43h.v30);
	outMat43f->v31 = toFloat32(inMat43h.v31);
	outMat43f->v32 = toFloat32(inMat43h.v32);
}

void   Mat43fToMat43h        (const Mat43f&   inMat43f, Mat43h*  outMat43h) {
	outMat43h->v00 = toFloat16(inMat43f.v00);
	outMat43h->v01 = toFloat16(inMat43f.v01);
	outMat43h->v02 = toFloat16(inMat43f.v02);
	
	outMat43h->v10 = toFloat16(inMat43f.v10);
	outMat43h->v11 = toFloat16(inMat43f.v11);
	outMat43h->v12 = toFloat16(inMat43f.v12);
	
	outMat43h->v20 = toFloat16(inMat43f.v20);
	outMat43h->v21 = toFloat16(inMat43f.v21);
	outMat43h->v22 = toFloat16(inMat43f.v22);
	
	outMat43h->v30 = toFloat16(inMat43f.v30);
	outMat43h->v31 = toFloat16(inMat43f.v31);
	outMat43h->v32 = toFloat16(inMat43f.v32);
}


////Inplace

void    Mat43hSumInplace(const Mat43h& r, Mat43h* outMat) {
	//outMat = outMat + r
	Mat43f rf;
	Mat43hToMat43f(r, &rf);
	Mat43f outMatf;
	Mat43hToMat43f(*outMat, &outMatf);
	Mat43fSumInplace(rf, &outMatf);
	Mat43fToMat43h(outMatf, outMat);
}

void    Mat43hSubInplace(const Mat43h& r, Mat43h* outMat) {
	//outMat = outMat + r
	Mat43f rf;
	Mat43hToMat43f(r, &rf);
	Mat43f outMatf;
	Mat43hToMat43f(*outMat, &outMatf);
	Mat43fSubInplace(rf, &outMatf);
	Mat43fToMat43h(outMatf, outMat);
	
}

FDK_NS_END