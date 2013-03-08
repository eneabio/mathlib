// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/mat33h.h"
#include "fdk/mathf.h"
#include "fdk/quatf.h"

FDK_NS_BEGIN

void Mat33hInit(Mat33h* outMat) {
	//with identity matrix
	F16 one  = toFloat16(1.0f);
	F16 zero = toFloat16(0.0f);
	outMat->v00 = one;
	outMat->v01 = zero;
	outMat->v02 = zero;
	outMat->v10 = zero;
	outMat->v11 = one;
	outMat->v12 = zero;
	outMat->v20 = zero;
	outMat->v21 = zero;
	outMat->v22 = one;
}

void    Mat33hInitWithMatrix(const Mat33h& inMat,Mat33h* outMat) {
	outMat->v00 = inMat.v00;
	outMat->v01 = inMat.v01;
	outMat->v02 = inMat.v02;
	outMat->v10 = inMat.v10;
	outMat->v11 = inMat.v11;
	outMat->v12 = inMat.v12;
	outMat->v20 = inMat.v20;
	outMat->v21 = inMat.v21;
	outMat->v22 = inMat.v22;
}

void    Mat33hInitWithValue(const F16 value, Mat33h* outMat) {
	outMat->v00 = value;
	outMat->v01 = value;
	outMat->v02 = value;
	outMat->v10 = value;
	outMat->v11 = value;
	outMat->v12 = value;
	outMat->v20 = value;
	outMat->v21 = value;
	outMat->v22 = value;
}

void    Mat33hInitWithRowVec(const Vec3h& row0, const Vec3h& row1, const Vec3h& row2, Mat33h* outMat) {
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
}

void    Mat33hInitWithColumnVec(const Vec3h& column0, const Vec3h& column1, const Vec3h& column2, Mat33h* outMat) {
	//column 0
	outMat->v00 = column0.x;
	outMat->v10 = column0.y;
	outMat->v20 = column0.z;
	
	//column 1
	outMat->v01 = column1.x;
	outMat->v11 = column1.y;
	outMat->v21 = column1.z;
	
	//column 2
	outMat->v02 = column2.x;
	outMat->v12 = column2.y;
	outMat->v22 = column2.z;
}

//void    Mat33hInitFromQuaternion(const Quath& quat, Mat33h* outMat) {
//	
//	//from library Bullet
//	F16 xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;
//	Quatf quatf;
//	QuathToQuadf(quat, quatf);
//	
//	F32 t  = 2.0f / QuatfSquaredModulus(quatf);
//	
//	xs = quat.qX*t;   ys = quat.qY*t;   zs = quat.qZ*t;
//	wx = quat.qW*xs;  wy = quat.qW*ys;  wz = quat.qW*zs;
//	xx = quat.qX*xs;  xy = quat.qX*ys;  xz = quat.qX*zs;
//	yy = quat.qY*ys;  yz = quat.qY*zs;  zz = quat.qZ*zs;
//	
//	*outMat = Mat33h(
//			 1.0-(yy+zz), xy-wz, xz+wy,
//	                 xy+wz, 1.0-(xx+zz), yz-wx,
//	                 xz-wy, yz+wx, 1.0-(xx+yy));
//	
//}

void    Mat33hGetColumn(const Mat33h&   inMat33h, int column, Vec3h* outVec) {
	
	FDK_ASSERT(column >= 0 && column < 3);
	
	if (column == 0) {
		outVec->x = inMat33h.v00;
		outVec->y = inMat33h.v10;
		outVec->z = inMat33h.v20;
	}
	if (column == 1) {
		outVec->x = inMat33h.v01;
		outVec->y = inMat33h.v11;
		outVec->z = inMat33h.v21;
	}
	if (column == 2) {
		outVec->x = inMat33h.v02;
		outVec->y = inMat33h.v12;
		outVec->z = inMat33h.v22;
	}
}

void    Mat33hGetRow(const Mat33h&   inMat33h, int row, Vec3h* outVec) {
	
	FDK_ASSERT(row >= 0 && row < 3);
	
	if (row == 0) {
		outVec->x = inMat33h.v00;
		outVec->y = inMat33h.v01;
		outVec->z = inMat33h.v02;
	}
	if (row == 1) {
		outVec->x = inMat33h.v10;
		outVec->y = inMat33h.v11;
		outVec->z = inMat33h.v12;
	}
	if (row == 2) {
		outVec->x = inMat33h.v20;
		outVec->y = inMat33h.v21;
		outVec->z = inMat33h.v22;
	}
}

void    Mat33hSum(const Mat33h&   l, const Mat33h&  r, Mat33h*  outMat) {
	//outMat = l + r
	Mat33f lf;
	Mat33hToMat33f(l, &lf);
	Mat33f rf;
	Mat33hToMat33f(r, &rf);
	Mat33f outMatF;
	Mat33fSum(lf, rf, &outMatF);
	Mat33fToMat33h(outMatF, outMat);
}

void    Mat33hSub(const Mat33h&   l, const Mat33h&  r, Mat33h*  outMat) {
	//outMat = l - r
	Mat33f lf;
	Mat33hToMat33f(l, &lf);
	Mat33f rf;
	Mat33hToMat33f(r, &rf);
	Mat33f outMatF;
	Mat33fSub(lf, rf, &outMatF);
	Mat33fToMat33h(outMatF, outMat);
	
}

void    Mat33hAbs(const Mat33h&   l, Mat33h*  outMat) {
	
	outMat->v00 = Fabsh(l.v00);
	outMat->v01 = Fabsh(l.v01);
	outMat->v02 = Fabsh(l.v02);
	
	outMat->v10 = Fabsh(l.v10);
	outMat->v11 = Fabsh(l.v11);
	outMat->v12 = Fabsh(l.v12);
	
	outMat->v20 = Fabsh(l.v20);
	outMat->v21 = Fabsh(l.v21);
	outMat->v22 = Fabsh(l.v22);
	
}

F16     Mat33hDeterminant(const Mat33h&   inMat33h) {
	//determinant matrix 3x3
	Mat33f mat33f;
	Mat33hToMat33f(inMat33h, &mat33f);
	F32 detf = mat33f.v00 * (mat33f.v11 * mat33f.v22 - mat33f.v21 * mat33f.v12) - mat33f.v01 * (mat33f.v10 * mat33f.v22 - mat33f.v12 * mat33f.v20) + mat33f.v02 * (mat33f.v10 * mat33f.v21 - mat33f.v11 * mat33f.v20) ;
	F16 deth = toFloat16(detf);
	return deth;
}

void    Mat33hMult(const Mat33h&   l, const Mat33h&  r, Mat33h*  outMat) {
	//outMat = l * r
	Mat33f lf;
	Mat33hToMat33f(l, &lf);
	Mat33f rf;
	Mat33hToMat33f(r, &rf);
	Mat33f outMatf;
	Mat33fMult(lf, rf, &outMatf);
	Mat33fToMat33h(outMatf, outMat);
}

bool 	Mat33hInvert(const Mat33h&  inMat33h, Mat33h*  outMat) {
	//Invert the matrix 3x3
	Mat33f outMatf;
	Mat33hToMat33f(inMat33h, &outMatf);
	bool ret = Mat33fInvertInplace(&outMatf);
	Mat33fToMat33h(outMatf, outMat);
	return ret;
}

void 	Mat33hTranspose(const Mat33h&  inMat33h, Mat33h*  outMat) {
	//transpose the matrix 3x3
	outMat->v00 = inMat33h.v00;
	outMat->v01 = inMat33h.v10;
	outMat->v02 = inMat33h.v20;
	
	outMat->v10 = inMat33h.v01;
	outMat->v11 = inMat33h.v11;
	outMat->v12 = inMat33h.v21;
	
	outMat->v20 = inMat33h.v02;
	outMat->v21 = inMat33h.v12;
	outMat->v22 = inMat33h.v22;
}

void    Mat33hMultVector(const Mat33h&  inMat33h, const Vec3h& inVec3h, Vec3h* outVec) {
	Mat33f outMatf;
	Mat33hToMat33f(inMat33h, &outMatf);
	Vec3f vecf;
	Vec3hToVec3f(inVec3h, &vecf);
	Vec3f outVecf;
	Mat33fMultVector(outMatf, vecf, &outVecf);
	outVec->x = toFloat16(outVecf.x);
	outVec->y = toFloat16(outVecf.y);
	outVec->z = toFloat16(outVecf.z);
}

void   Mat33hToMat33f        (const Mat33h&   inMat33h, Mat33f*  outMat33f) {
	outMat33f->v00 = toFloat32(inMat33h.v00);
	outMat33f->v01 = toFloat32(inMat33h.v01);
	outMat33f->v02 = toFloat32(inMat33h.v02);
	outMat33f->v10 = toFloat32(inMat33h.v10);
	outMat33f->v11 = toFloat32(inMat33h.v11);
	outMat33f->v12 = toFloat32(inMat33h.v12);
	outMat33f->v20 = toFloat32(inMat33h.v20);
	outMat33f->v21 = toFloat32(inMat33h.v21);
	outMat33f->v22 = toFloat32(inMat33h.v22);
}

void   Mat33fToMat33h        (const Mat33f&   inMat33f, Mat33h*  outMat33h) {
	outMat33h->v00 = toFloat16(inMat33f.v00);
	outMat33h->v01 = toFloat16(inMat33f.v01);
	outMat33h->v02 = toFloat16(inMat33f.v02);
	outMat33h->v10 = toFloat16(inMat33f.v10);
	outMat33h->v11 = toFloat16(inMat33f.v11);
	outMat33h->v12 = toFloat16(inMat33f.v12);
	outMat33h->v20 = toFloat16(inMat33f.v20);
	outMat33h->v21 = toFloat16(inMat33f.v21);
	outMat33h->v22 = toFloat16(inMat33f.v22);
}

//Inplace

void    Mat33hSumInplace(const Mat33h&  r, Mat33h*  outMat) {
	//outMat = outMat + r
	Mat33f rf;
	Mat33hToMat33f(r, &rf);
	Mat33f outMatf;
	Mat33hToMat33f(*outMat, &outMatf);
	Mat33fSumInplace(rf, &outMatf);
	Mat33fToMat33h(outMatf, outMat);
}

void    Mat33hSubInplace(const Mat33h&  r, Mat33h*  outMat) {
	//outMat = outMat + r
	Mat33f rf;
	Mat33hToMat33f(r, &rf);
	Mat33f outMatf;
	Mat33hToMat33f(*outMat, &outMatf);
	Mat33fSubInplace(rf, &outMatf);
	Mat33fToMat33h(outMatf, outMat);
}


void    Mat33hMultInplace(const Mat33h&  r, Mat33h*  outMat) {
	//outMat = outMat * r
	Mat33f rf;
	Mat33hToMat33f(r, &rf);
	Mat33f outMatf;
	Mat33hToMat33f(*outMat, &outMatf);
	Mat33fMultInplace(rf, &outMatf);
	Mat33fToMat33h(outMatf, outMat);
}

bool 	Mat33hInvertInplace(Mat33h*  outMat) {
	Mat33f outMatf;
	Mat33hToMat33f(*outMat, &outMatf);
	bool ret = Mat33fInvertInplace(&outMatf);
	Mat33fToMat33h(outMatf, outMat);
	return ret;
}

void 	Mat33hTransposeInplace(Mat33h*  outMat) {
	//transpose the matrix 3x3
	Mat33h temp = Mat33h( outMat->v00, outMat->v01, outMat->v02, outMat->v10, outMat->v11, outMat->v12, outMat->v20, outMat->v21, outMat->v22);
	
	outMat->v00 = temp.v00;
	outMat->v01 = temp.v10;
	outMat->v02 = temp.v20;
	outMat->v10 = temp.v01;
	outMat->v11 = temp.v11;
	outMat->v12 = temp.v21;
	outMat->v20 = temp.v02;
	outMat->v21 = temp.v12;
	outMat->v22 = temp.v22;
	
}

FDK_NS_END
