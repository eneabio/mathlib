// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/mat33f.h"
//#include "fdk/mat44f.h"
#include "fdk/mathf.h"

FDK_NS_BEGIN

void    Mat33fInit(Mat33f* outMat) {
	//with identity matrix
	outMat->v00 = 1.f;
	outMat->v01 = 0.f;
	outMat->v02 = 0.f;
	outMat->v10 = 0.f;
	outMat->v11 = 1.f;
	outMat->v12 = 0.f;
	outMat->v20 = 0.f;
	outMat->v21 = 0.f;
	outMat->v22 = 1.f;
}

void    Mat33fInitWithMatrix(const Mat33f& inMat,Mat33f* outMat) {
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

void    Mat33fInitWithValue(const F32 value, Mat33f* outMat) {
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

void    Mat33fInitWithRowVec(const Vec3f& row0, const Vec3f& row1, const Vec3f& row2, Mat33f* outMat) {
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

void    Mat33fInitWithColumnVec(const Vec3f& column0, const Vec3f& column1, const Vec3f& column2, Mat33f* outMat) {
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

void    Mat33fInitFromQuaternion(const Quatf& quat, Mat33f* outMat) {
	
	//from library Bullet
	F32 xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;
	
	F32 t  = 2.0f / QuatfSquaredModulus(quat);
	
	xs = quat.qX*t;   ys = quat.qY*t;   zs = quat.qZ*t;
	wx = quat.qW*xs;  wy = quat.qW*ys;  wz = quat.qW*zs;
	xx = quat.qX*xs;  xy = quat.qX*ys;  xz = quat.qX*zs;
	yy = quat.qY*ys;  yz = quat.qY*zs;  zz = quat.qZ*zs;
	
	*outMat = Mat33f(
			 1.0f-(yy+zz), xy-wz, xz+wy,
	                 xy+wz, 1.0f-(xx+zz), yz-wx,
	                 xz-wy, yz+wx, 1.0f-(xx+yy));
	
}

void    Mat33fGetColumn(const Mat33f& FDK_RESTRICT  inMat33f, int column, Vec3f* outVec) {
	
	FDK_ASSERT(column >= 0 && column < 3);
	
	if (column == 0) {
		outVec->x = inMat33f.v00;
		outVec->y = inMat33f.v10;
		outVec->z = inMat33f.v20;
	}
	if (column == 1) {
		outVec->x = inMat33f.v01;
		outVec->y = inMat33f.v11;
		outVec->z = inMat33f.v21;
	}
	if (column == 2) {
		outVec->x = inMat33f.v02;
		outVec->y = inMat33f.v12;
		outVec->z = inMat33f.v22;
	}
}

void    Mat33fGetRow(const Mat33f& FDK_RESTRICT  inMat33f, int row, Vec3f* outVec) {
	
	FDK_ASSERT(row >= 0 && row < 3);
	
	if (row == 0) {
		outVec->x = inMat33f.v00;
		outVec->y = inMat33f.v01;
		outVec->z = inMat33f.v02;
	}
	if (row == 1) {
		outVec->x = inMat33f.v10;
		outVec->y = inMat33f.v11;
		outVec->z = inMat33f.v12;
	}
	if (row == 2) {
		outVec->x = inMat33f.v20;
		outVec->y = inMat33f.v21;
		outVec->z = inMat33f.v22;
	}
}

void    Mat33fSum(const Mat33f& FDK_RESTRICT  l, const Mat33f& FDK_RESTRICT r, Mat33f* FDK_RESTRICT outMat) {
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
	
}

void    Mat33fSub(const Mat33f& FDK_RESTRICT  l, const Mat33f& FDK_RESTRICT r, Mat33f* FDK_RESTRICT outMat) {
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

}

void    Mat33fAbs(const Mat33f& FDK_RESTRICT  l, Mat33f* FDK_RESTRICT outMat) {
	
	outMat->v00 = Fabsf(l.v00);
	outMat->v01 = Fabsf(l.v01);
	outMat->v02 = Fabsf(l.v02);
	
	outMat->v10 = Fabsf(l.v10);
	outMat->v11 = Fabsf(l.v11);
	outMat->v12 = Fabsf(l.v12);
	
	outMat->v20 = Fabsf(l.v20);
	outMat->v21 = Fabsf(l.v21);
	outMat->v22 = Fabsf(l.v22);

}

F32     Mat33fDeterminant(const Mat33f& FDK_RESTRICT  inMat33f) {
	//determinant matrix 3x3
	F32 determinant = inMat33f.v00 * (inMat33f.v11 * inMat33f.v22 - inMat33f.v21 * inMat33f.v12) - inMat33f.v01 * (inMat33f.v10 * inMat33f.v22 - inMat33f.v12 * inMat33f.v20) + inMat33f.v02 * (inMat33f.v10 * inMat33f.v21 - inMat33f.v11 * inMat33f.v20) ;
	return determinant;
}

void    Mat33fMult(const Mat33f& FDK_RESTRICT  l, const Mat33f& FDK_RESTRICT r, Mat33f* FDK_RESTRICT outMat) {
	
	//outMat = l * r
	outMat->v00 = l.v00 * r.v00 + l.v01 * r.v10 + l.v02 * r.v20;
	outMat->v01 = l.v00 * r.v01 + l.v01 * r.v11 + l.v02 * r.v21;
	outMat->v02 = l.v00 * r.v02 + l.v01 * r.v12 + l.v02 * r.v22;
	outMat->v10 = l.v10 * r.v00 + l.v11 * r.v10 + l.v12 * r.v20;
	outMat->v11 = l.v10 * r.v01 + l.v11 * r.v11 + l.v12 * r.v21;
	outMat->v12 = l.v10 * r.v02 + l.v11 * r.v12 + l.v12 * r.v22;
	outMat->v20 = l.v20 * r.v00 + l.v21 * r.v10 + l.v22 * r.v20;
	outMat->v21 = l.v20 * r.v01 + l.v21 * r.v11 + l.v22 * r.v21;
	outMat->v22 = l.v20 * r.v02 + l.v21 * r.v12 + l.v22 * r.v22;
}

bool 	Mat33fInvert(const Mat33f& FDK_RESTRICT inMat33f, Mat33f* FDK_RESTRICT outMat) {
	//Invert the matrix 3x3
	
	//determinant matrix 3x3
	//F32 determinant = inMat33f.v00 * (inMat33f.v11 * inMat33f.v22 - inMat33f.v21 * inMat33f.v12) - inMat33f.v01 * (inMat33f.v10 * inMat33f.v22 - inMat33f.v12 * inMat33f.v20) + inMat33f.v02 * (inMat33f.v10 * inMat33f.v21 - inMat33f.v11 * inMat33f.v20) ;
	F32 determinant = Mat33fDeterminant(inMat33f);
	
	//Determinant must be different from zero, else matrix can't be inverted.
	if (determinant == 0)
		return false;
	
	//Invert
	outMat->v00 =  (1.f/determinant) * (inMat33f.v11 * inMat33f.v22 - inMat33f.v21 * inMat33f.v12);
	outMat->v01 = -(1.f/determinant) * (inMat33f.v01 * inMat33f.v22 - inMat33f.v02 * inMat33f.v21);
	outMat->v02 =  (1.f/determinant) * (inMat33f.v01 * inMat33f.v12 - inMat33f.v02 * inMat33f.v11);
	outMat->v10 = -(1.f/determinant) * (inMat33f.v10 * inMat33f.v22 - inMat33f.v12 * inMat33f.v20);
	outMat->v11 =  (1.f/determinant) * (inMat33f.v00 * inMat33f.v22 - inMat33f.v02 * inMat33f.v20);
	outMat->v12 = -(1.f/determinant) * (inMat33f.v00 * inMat33f.v12 - inMat33f.v10 * inMat33f.v02);
	outMat->v20 =  (1.f/determinant) * (inMat33f.v10 * inMat33f.v21 - inMat33f.v20 * inMat33f.v11);
	outMat->v21 = -(1.f/determinant) * (inMat33f.v00 * inMat33f.v21 - inMat33f.v20 * inMat33f.v01);
	outMat->v22 =  (1.f/determinant) * (inMat33f.v00 * inMat33f.v11 - inMat33f.v10 * inMat33f.v01);
	return true;
}

void 	Mat33fTranspose(const Mat33f& FDK_RESTRICT inMat33f, Mat33f* FDK_RESTRICT outMat) {
	//transpose the matrix 3x3
	outMat->v00 = inMat33f.v00;
	outMat->v01 = inMat33f.v10;
	outMat->v02 = inMat33f.v20;
	
	outMat->v10 = inMat33f.v01;
	outMat->v11 = inMat33f.v11;
	outMat->v12 = inMat33f.v21;
	
	outMat->v20 = inMat33f.v02;
	outMat->v21 = inMat33f.v12;
	outMat->v22 = inMat33f.v22;
}

void    Mat33fMultVector(const Mat33f&  inMat33f, const Vec3f& inVec3f, Vec3f* outVec) {
	outVec->x = inMat33f.v00 * inVec3f.x +  inMat33f.v01 * inVec3f.y + inMat33f.v02 * inVec3f.z;
	outVec->y = inMat33f.v10 * inVec3f.x +  inMat33f.v11 * inVec3f.y + inMat33f.v12 * inVec3f.z;
	outVec->z = inMat33f.v20 * inVec3f.x +  inMat33f.v21 * inVec3f.y + inMat33f.v22 * inVec3f.z;
}

//Inplace

void    Mat33fSumInplace(const Mat33f& FDK_RESTRICT r, Mat33f* FDK_RESTRICT outMat) {
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
}

void    Mat33fSubInplace(const Mat33f& FDK_RESTRICT r, Mat33f* FDK_RESTRICT outMat) {
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

}


void    Mat33fMultInplace(const Mat33f& FDK_RESTRICT r, Mat33f* FDK_RESTRICT outMat) {
	//outMat = outMat * r
	Mat33f temp = *outMat;
	
	outMat->v00 = temp.v00 * r.v00 + temp.v01 * r.v10 + temp.v02 * r.v20;
	outMat->v01 = temp.v00 * r.v01 + temp.v01 * r.v11 + temp.v02 * r.v21;
	outMat->v02 = temp.v00 * r.v02 + temp.v01 * r.v12 + temp.v02 * r.v22;
	outMat->v10 = temp.v10 * r.v00 + temp.v11 * r.v10 + temp.v12 * r.v20;
	outMat->v11 = temp.v10 * r.v01 + temp.v11 * r.v11 + temp.v12 * r.v21;
	outMat->v12 = temp.v10 * r.v02 + temp.v11 * r.v12 + temp.v12 * r.v22;
	outMat->v20 = temp.v20 * r.v00 + temp.v21 * r.v10 + temp.v22 * r.v20;
	outMat->v21 = temp.v20 * r.v01 + temp.v21 * r.v11 + temp.v22 * r.v21;
	outMat->v22 = temp.v20 * r.v02 + temp.v21 * r.v12 + temp.v22 * r.v22;
}

bool 	Mat33fInvertInplace(Mat33f* FDK_RESTRICT outMat) {
	//Invert the matrix 3x3
	
	Mat33f temp = *outMat;
	
	//determinant matrix 3x3
	//F32 determinant = temp.v00 * (temp.v11 * temp.v22 - temp.v21 * temp.v12) - temp.v01 * (temp.v10 * temp.v22 - temp.v12 * temp.v20) + temp.v02 * (temp.v10 * temp.v21 - temp.v11 * temp.v20);
	F32 determinant = Mat33fDeterminant(*outMat);
	
	//Determinant must be different from zero, else matrix can't be inverted.
	if (determinant == 0)
		return false;
	
	//Invert
	
	outMat->v00 =  (1.f/determinant) * (temp.v11 * temp.v22 - temp.v21 * temp.v12);
	outMat->v01 = -(1.f/determinant) * (temp.v01 * temp.v22 - temp.v02 * temp.v21);
	outMat->v02 =  (1.f/determinant) * (temp.v01 * temp.v12 - temp.v02 * temp.v11);
	outMat->v10 = -(1.f/determinant) * (temp.v10 * temp.v22 - temp.v12 * temp.v20);
	outMat->v11 =  (1.f/determinant) * (temp.v00 * temp.v22 - temp.v02 * temp.v20);
	outMat->v12 = -(1.f/determinant) * (temp.v00 * temp.v12 - temp.v10 * temp.v02);
	outMat->v20 =  (1.f/determinant) * (temp.v10 * temp.v21 - temp.v20 * temp.v11);
	outMat->v21 = -(1.f/determinant) * (temp.v00 * temp.v21 - temp.v20 * temp.v01);
	outMat->v22 =  (1.f/determinant) * (temp.v00 * temp.v11 - temp.v10 * temp.v01);
	return true;
}

void 	Mat33fTransposeInplace(Mat33f* FDK_RESTRICT outMat) {
	//transpose the matrix 3x3
	Mat33f temp = Mat33f( outMat->v00, outMat->v01, outMat->v02, outMat->v10, outMat->v11, outMat->v12,  outMat->v20, outMat->v21, outMat->v22);
	
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