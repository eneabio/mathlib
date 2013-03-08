// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/mathf.h"
#include "fdk/mat44h.h"
#include "fdk/mat33h.h"
//#include "fdk/memory.h"


FDK_NS_BEGIN

void    Mat44hInit(Mat44h* outMat) {
	//with identity matrix
	F16 one  = toFloat16(1.0f);
	F16 zero = toFloat16(0.0f);
	outMat->v00 = one;
	outMat->v01 = zero;
	outMat->v02 = zero;
	outMat->v03 = zero;
	
	outMat->v10 = zero;
	outMat->v11 = one;
	outMat->v12 = zero;
	outMat->v13 = zero;
	
	outMat->v20 = zero;
	outMat->v21 = zero;
	outMat->v22 = one;
	outMat->v23 = zero;
	
	outMat->v30 = zero;
	outMat->v31 = zero;
	outMat->v32 = zero;
	outMat->v33 = one;
	
}

void    Mat44hInitWithMatrix(const Mat44h& inMat, Mat44h* outMat) {
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

void    Mat44hInitWithValue(const F16 value, Mat44h* outMat) {
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

void    Mat44hInitWithRowVec(const Vec4h& row0, const Vec4h& row1, const Vec4h& row2, const Vec4h& row3, Mat44h* outMat) {
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

void    Mat44hInitWithColumnVec(const Vec4h& column0, const Vec4h& column1, const Vec4h& column2, const Vec4h& column3, Mat44h* outMat) {
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

//void    Mat44hInitFromQuaternion(const Quath& quat, Mat44h* outMat) {
//	Mat33h matQuat;
//	Mat33hInitFromQuaternion(quat, &matQuat);
//	Mat44hInit(outMat);
//	
//	outMat->v00 = matQuat.v00;
//	outMat->v01 = matQuat.v01;
//	outMat->v02 = matQuat.v02;
//	
//	outMat->v10 = matQuat.v10;
//	outMat->v11 = matQuat.v11;
//	outMat->v12 = matQuat.v12;
//	
//	outMat->v20 = matQuat.v20;
//	outMat->v21 = matQuat.v21;
//	outMat->v22 = matQuat.v22;
//	
//}

void    Mat44hGetColumn(const Mat44h&   inMat44h, int column, Vec4h* outVec) {
	
	FDK_ASSERT(column >= 0 && column <=3);
	
	if (column == 0) {
		outVec->x = inMat44h.v00;
		outVec->y = inMat44h.v10;
		outVec->z = inMat44h.v20;
		outVec->w = inMat44h.v30;
	}
	if (column == 1) {
		outVec->x = inMat44h.v01;
		outVec->y = inMat44h.v11;
		outVec->z = inMat44h.v21;
		outVec->w = inMat44h.v31;
	}
	if (column == 2) {
		outVec->x = inMat44h.v02;
		outVec->y = inMat44h.v12;
		outVec->z = inMat44h.v22;
		outVec->w = inMat44h.v32;
	}
	if (column == 3) {
		outVec->x = inMat44h.v03;
		outVec->y = inMat44h.v13;
		outVec->z = inMat44h.v23;
		outVec->w = inMat44h.v33;
	}
}

void    Mat44hGetRow(const Mat44h&   inMat44h, int row, Vec4h* outVec) {
	
	FDK_ASSERT(row >= 0 && row <=3);
	
	if (row == 0) {
		outVec->x = inMat44h.v00;
		outVec->y = inMat44h.v01;
		outVec->z = inMat44h.v02;
		outVec->w = inMat44h.v03;
	}
	if (row == 1) {
		outVec->x = inMat44h.v10;
		outVec->y = inMat44h.v11;
		outVec->z = inMat44h.v12;
		outVec->w = inMat44h.v13;
	}
	if (row == 2) {
		outVec->x = inMat44h.v20;
		outVec->y = inMat44h.v21;
		outVec->z = inMat44h.v22;
		outVec->w = inMat44h.v23;
	}
	if (row == 3) {
		outVec->x = inMat44h.v30;
		outVec->y = inMat44h.v31;
		outVec->z = inMat44h.v32;
		outVec->w = inMat44h.v33;
	}
}

void    Mat44hSum(const Mat44h&   l, const Mat44h&  r, Mat44h*  outMat) {
	//outMat = l + r
	Mat44f lf;
	Mat44hToMat44f(l, &lf);
	Mat44f rf;
	Mat44hToMat44f(r, &rf);
	Mat44f outMatF;
	Mat44fSum(lf, rf, &outMatF);
	Mat44fToMat44h(outMatF, outMat);
}

void    Mat44hSub(const Mat44h&   l, const Mat44h&  r, Mat44h*  outMat) {
	//outMat = l - r
	Mat44f lf;
	Mat44hToMat44f(l, &lf);
	Mat44f rf;
	Mat44hToMat44f(r, &rf);
	Mat44f outMatF;
	Mat44fSub(lf, rf, &outMatF);
	Mat44fToMat44h(outMatF, outMat);
	
}

void    Mat44hAbs(const Mat44h&   l, Mat44h*  outMat) {
	
	outMat->v00 = Fabsh(l.v00);
	outMat->v01 = Fabsh(l.v01);
	outMat->v02 = Fabsh(l.v02);
	outMat->v03 = Fabsh(l.v03);
	
	outMat->v10 = Fabsh(l.v10);
	outMat->v11 = Fabsh(l.v11);
	outMat->v12 = Fabsh(l.v12);
	outMat->v13 = Fabsh(l.v13);
	
	outMat->v20 = Fabsh(l.v20);
	outMat->v21 = Fabsh(l.v21);
	outMat->v22 = Fabsh(l.v22);
	outMat->v23 = Fabsh(l.v23);
	
	outMat->v30 = Fabsh(l.v30);
	outMat->v31 = Fabsh(l.v31);
	outMat->v32 = Fabsh(l.v32);
	outMat->v33 = Fabsh(l.v33);
	
}

F16 Mat44hCoFactor(const Mat44h&   m, int row, int col) {
	Mat44f mf;
	Mat44hToMat44f(m, &mf);
	F32 cofactorf = (( mf((row+1)&3,(col+1)&3) * mf((row+2)&3,(col+2)&3) * mf((row+3)&3,(col+3)&3) +
			 mf((row+1)&3,(col+2)&3) * mf((row+2)&3,(col+3)&3)* mf((row+3)&3,(col+1)&3) +
			 mf((row+1)&3,(col+3)&3) * mf((row+2)&3,(col+1)&3) *mf((row+3)&3,(col+2)&3))
			-  (mf((row+3)&3,(col+1)&3) * mf ((row+2)&3,(col+2)&3) * mf((row+1)&3,(col+3)&3) +
			    mf((row+3)&3,(col+2)&3) * mf((row+2)&3,(col+3)&3) * mf((row+1)&3,(col+1)&3) +
			    mf((row+3)&3,(col+3)&3) * mf((row+2)&3,(col+1)&3) * mf((row+1)&3,(col+2)&3))) * ((row + col) & 1 ? -1.0f : +1.0f);
	F16 cofactorh = toFloat16(cofactorf);
	return cofactorh;
}

F16     Mat44hDeterminant(const Mat44h&   inMat44h) {
	Mat44f inMat44f;
	Mat44hToMat44f(inMat44h, &inMat44f);
	F32 detf = Mat44fDeterminant(inMat44f);
	F16 deth = toFloat16(detf);
	return	deth;
	
}

void    Mat44hMult(const Mat44h&   l, const Mat44h&  r, Mat44h*  outMat) {
	//outMat = l * r
	Mat44f lf;
	Mat44hToMat44f(l, &lf);
	Mat44f rf;
	Mat44hToMat44f(r, &rf);
	Mat44f outMatf;
	Mat44fMult(lf, rf, &outMatf);
	Mat44fToMat44h(outMatf, outMat);
}

bool 	Mat44hInvert(const Mat44h&  inMat44h, Mat44h*  outMat) {
	Mat44f outMatf;
	Mat44hToMat44f(inMat44h, &outMatf);
	bool ret = Mat44fInvertInplace(&outMatf);
	Mat44fToMat44h(outMatf, outMat);
	return ret;
}

void 	Mat44hTranspose(const Mat44h&  inMat44h, Mat44h*  outMat) {
	//transpose the matrix 4x4
	outMat->v00 = inMat44h.v00;
	outMat->v01 = inMat44h.v10;
	outMat->v02 = inMat44h.v20;
	outMat->v03 = inMat44h.v30;
	
	outMat->v10 = inMat44h.v01;
	outMat->v11 = inMat44h.v11;
	outMat->v12 = inMat44h.v21;
	outMat->v13 = inMat44h.v31;
	
	outMat->v20 = inMat44h.v02;
	outMat->v21 = inMat44h.v12;
	outMat->v22 = inMat44h.v22;
	outMat->v23 = inMat44h.v32;
	
	outMat->v30 = inMat44h.v03;
	outMat->v31 = inMat44h.v13;
	outMat->v32 = inMat44h.v23;
	outMat->v33 = inMat44h.v33;
}

void    Mat44hMultVector(const Mat44h&  inMat44h, const Vec4h& inVec4h, Vec4h* outVec) {
	Mat44f outMatf;
	Mat44hToMat44f(inMat44h, &outMatf);
	Vec4f vecf;
	Vec4hToVec4f(inVec4h, &vecf);
	Vec4f outVecf;
	Mat44fMultVector(outMatf, vecf, &outVecf);
	outVec->x = toFloat16(outVecf.x);
	outVec->y = toFloat16(outVecf.y);
	outVec->z = toFloat16(outVecf.z);
	outVec->w = toFloat16(outVecf.w);
}

void   Mat44hToMat44f        (const Mat44h&   inMat44h, Mat44f*  outMat44f) {
	outMat44f->v00 = toFloat32(inMat44h.v00);
	outMat44f->v01 = toFloat32(inMat44h.v01);
	outMat44f->v02 = toFloat32(inMat44h.v02);
	outMat44f->v03 = toFloat32(inMat44h.v03);
	outMat44f->v10 = toFloat32(inMat44h.v10);
	outMat44f->v11 = toFloat32(inMat44h.v11);
	outMat44f->v12 = toFloat32(inMat44h.v12);
	outMat44f->v13 = toFloat32(inMat44h.v13);
	outMat44f->v20 = toFloat32(inMat44h.v20);
	outMat44f->v21 = toFloat32(inMat44h.v21);
	outMat44f->v22 = toFloat32(inMat44h.v22);
	outMat44f->v23 = toFloat32(inMat44h.v23);
	outMat44f->v30 = toFloat32(inMat44h.v30);
	outMat44f->v31 = toFloat32(inMat44h.v31);
	outMat44f->v32 = toFloat32(inMat44h.v32);
	outMat44f->v33 = toFloat32(inMat44h.v33);
}

void   Mat44fToMat44h        (const Mat44f&   inMat44f, Mat44h*  outMat44h) {
	outMat44h->v00 = toFloat16(inMat44f.v00);
	outMat44h->v01 = toFloat16(inMat44f.v01);
	outMat44h->v02 = toFloat16(inMat44f.v02);
	outMat44h->v03 = toFloat16(inMat44f.v03);
	outMat44h->v10 = toFloat16(inMat44f.v10);
	outMat44h->v11 = toFloat16(inMat44f.v11);
	outMat44h->v12 = toFloat16(inMat44f.v12);
	outMat44h->v13 = toFloat16(inMat44f.v13);
	outMat44h->v20 = toFloat16(inMat44f.v20);
	outMat44h->v21 = toFloat16(inMat44f.v21);
	outMat44h->v22 = toFloat16(inMat44f.v22);
	outMat44h->v23 = toFloat16(inMat44f.v23);
	outMat44h->v30 = toFloat16(inMat44f.v30);
	outMat44h->v31 = toFloat16(inMat44f.v31);
	outMat44h->v32 = toFloat16(inMat44f.v32);
	outMat44h->v33 = toFloat16(inMat44f.v33);
}


//Inplace

void    Mat44hSumInplace(const Mat44h&  r, Mat44h*  outMat) {
	//outMat = outMat + r
	Mat44f rf;
	Mat44hToMat44f(r, &rf);
	Mat44f outMatf;
	Mat44hToMat44f(*outMat, &outMatf);
	Mat44fSumInplace(rf, &outMatf);
	Mat44fToMat44h(outMatf, outMat);
}

void    Mat44hSubInplace(const Mat44h&  r, Mat44h*  outMat) {
	//outMat = outMat + r
	Mat44f rf;
	Mat44hToMat44f(r, &rf);
	Mat44f outMatf;
	Mat44hToMat44f(*outMat, &outMatf);
	Mat44fSubInplace(rf, &outMatf);
	Mat44fToMat44h(outMatf, outMat);
	
}


void    Mat44hMultInplace(const Mat44h&  r, Mat44h*  outMat) {
	//outMat = outMat * r
	Mat44f rf;
	Mat44hToMat44f(r, &rf);
	Mat44f outMatf;
	Mat44hToMat44f(*outMat, &outMatf);
	Mat44fMultInplace(rf, &outMatf);
	Mat44fToMat44h(outMatf, outMat);
}

bool 	Mat44hInvertInplace(Mat44h*  outMat) {
	Mat44f outMatf;
	Mat44hToMat44f(*outMat, &outMatf);
	bool ret = Mat44fInvertInplace(&outMatf);
	Mat44fToMat44h(outMatf, outMat);
	return ret;}

void 	Mat44hTransposeInplace(Mat44h*  outMat) {
	//transpose the matrix 3x3
	Mat44h temp = Mat44h( outMat->v00, outMat->v01, outMat->v02, outMat->v03, outMat->v10, outMat->v11, outMat->v12, outMat->v13, outMat->v20, outMat->v21, outMat->v22, outMat->v23, outMat->v30, outMat->v31, outMat->v32, outMat->v33);
	
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
