// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/mat33d.h"
#include "fdk/mat44d.h"
#include "fdk/mathd.h"

FDK_NS_BEGIN

void    Mat33dInit(Mat33d* outMat) {
	//with identity matrix
	outMat->v00 = 1.0;
	outMat->v01 = 0.0;
	outMat->v02 = 0.0;
	outMat->v10 = 0.0;
	outMat->v11 = 1.0;
	outMat->v12 = 0.0;
	outMat->v20 = 0.0;
	outMat->v21 = 0.0;
	outMat->v22 = 1.0;
}

void    Mat33dInitWithMatrix(const Mat33d& inMat,Mat33d* outMat) {
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

void    Mat33dInitWithValue(const F64 value, Mat33d* outMat) {
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

void    Mat33dInitWithRowVec(const Vec3d& row0, const Vec3d& row1, const Vec3d& row2, Mat33d* outMat) {
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

void    Mat33dInitWithColumnVec(const Vec3d& column0, const Vec3d& column1, const Vec3d& column2, Mat33d* outMat) {
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

void    Mat33dInitFromQuaternion(const Quatd& quat, Mat33d* outMat) {
	
	//from library Bullet
	F64 xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;
	
	F64 t  = 2.0 / QuatdSquaredModulus(quat);
	
	xs = quat.qX*t;   ys = quat.qY*t;   zs = quat.qZ*t;
	wx = quat.qW*xs;  wy = quat.qW*ys;  wz = quat.qW*zs;
	xx = quat.qX*xs;  xy = quat.qX*ys;  xz = quat.qX*zs;
	yy = quat.qY*ys;  yz = quat.qY*zs;  zz = quat.qZ*zs;
	
	*outMat = Mat33d(
			 1.0-(yy+zz), xy-wz, xz+wy,
	                 xy+wz, 1.0-(xx+zz), yz-wx,
	                 xz-wy, yz+wx, 1.0-(xx+yy));
	
}

void    Mat33dGetColumn(const Mat33d& FDK_RESTRICT  inMat33d, int column, Vec3d* outVec) {
	
	FDK_ASSERT(column >= 0 && column < 3);
	
	if (column == 0) {
		outVec->x = inMat33d.v00;
		outVec->y = inMat33d.v10;
		outVec->z = inMat33d.v20;
	}
	if (column == 1) {
		outVec->x = inMat33d.v01;
		outVec->y = inMat33d.v11;
		outVec->z = inMat33d.v21;
	}
	if (column == 2) {
		outVec->x = inMat33d.v02;
		outVec->y = inMat33d.v12;
		outVec->z = inMat33d.v22;
	}
}

void    Mat33dGetRow(const Mat33d& FDK_RESTRICT  inMat33d, int row, Vec3d* outVec) {
	
	FDK_ASSERT(row >= 0 && row < 3);
	
	if (row == 0) {
		outVec->x = inMat33d.v00;
		outVec->y = inMat33d.v01;
		outVec->z = inMat33d.v02;
	}
	if (row == 1) {
		outVec->x = inMat33d.v10;
		outVec->y = inMat33d.v11;
		outVec->z = inMat33d.v12;
	}
	if (row == 2) {
		outVec->x = inMat33d.v20;
		outVec->y = inMat33d.v21;
		outVec->z = inMat33d.v22;
	}
}

void    Mat33dSum(const Mat33d& FDK_RESTRICT  l, const Mat33d& FDK_RESTRICT r, Mat33d* FDK_RESTRICT outMat) {
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

void    Mat33dSub(const Mat33d& FDK_RESTRICT  l, const Mat33d& FDK_RESTRICT r, Mat33d* FDK_RESTRICT outMat) {
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

void    Mat33dAbs(const Mat33d& FDK_RESTRICT  l, Mat33d* FDK_RESTRICT outMat) {
	
	outMat->v00 = Fabsd(l.v00);
	outMat->v01 = Fabsd(l.v01);
	outMat->v02 = Fabsd(l.v02);
	
	outMat->v10 = Fabsd(l.v10);
	outMat->v11 = Fabsd(l.v11);
	outMat->v12 = Fabsd(l.v12);
	
	outMat->v20 = Fabsd(l.v20);
	outMat->v21 = Fabsd(l.v21);
	outMat->v22 = Fabsd(l.v22);
	
}

F64     Mat33dDeterminant(const Mat33d& FDK_RESTRICT  inMat33d) {
	//determinant matrix 3x3
	F64 determinant = inMat33d.v00 * (inMat33d.v11 * inMat33d.v22 - inMat33d.v21 * inMat33d.v12) - inMat33d.v01 * (inMat33d.v10 * inMat33d.v22 - inMat33d.v12 * inMat33d.v20) + inMat33d.v02 * (inMat33d.v10 * inMat33d.v21 - inMat33d.v11 * inMat33d.v20) ;
	return determinant;
}

void    Mat33dMult(const Mat33d& FDK_RESTRICT  l, const Mat33d& FDK_RESTRICT r, Mat33d* FDK_RESTRICT outMat) {
	
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

bool 	Mat33dInvert(const Mat33d& FDK_RESTRICT inMat33d, Mat33d* FDK_RESTRICT outMat) {
	//Invert the matrix 3x3
	
	//determinant matrix 3x3
	//F64 determinant = inMat33d.v00 * (inMat33d.v11 * inMat33d.v22 - inMat33d.v21 * inMat33d.v12) - inMat33d.v01 * (inMat33d.v10 * inMat33d.v22 - inMat33d.v12 * inMat33d.v20) + inMat33d.v02 * (inMat33d.v10 * inMat33d.v21 - inMat33d.v11 * inMat33d.v20) ;
	F64 determinant = Mat33dDeterminant(inMat33d);
	
	//Determinant must be different from zero, else matrix can't be inverted.
	if (determinant == 0)
		return false;
	
	//Invert
	outMat->v00 =  (1.0/determinant) * (inMat33d.v11 * inMat33d.v22 - inMat33d.v21 * inMat33d.v12);
	outMat->v01 = -(1.0/determinant) * (inMat33d.v01 * inMat33d.v22 - inMat33d.v02 * inMat33d.v21);
	outMat->v02 =  (1.0/determinant) * (inMat33d.v01 * inMat33d.v12 - inMat33d.v02 * inMat33d.v11);
	outMat->v10 = -(1.0/determinant) * (inMat33d.v10 * inMat33d.v22 - inMat33d.v12 * inMat33d.v20);
	outMat->v11 =  (1.0/determinant) * (inMat33d.v00 * inMat33d.v22 - inMat33d.v02 * inMat33d.v20);
	outMat->v12 = -(1.0/determinant) * (inMat33d.v00 * inMat33d.v12 - inMat33d.v10 * inMat33d.v02);
	outMat->v20 =  (1.0/determinant) * (inMat33d.v10 * inMat33d.v21 - inMat33d.v20 * inMat33d.v11);
	outMat->v21 = -(1.0/determinant) * (inMat33d.v00 * inMat33d.v21 - inMat33d.v20 * inMat33d.v01);
	outMat->v22 =  (1.0/determinant) * (inMat33d.v00 * inMat33d.v11 - inMat33d.v10 * inMat33d.v01);
	return true;
}

void 	Mat33dTranspose(const Mat33d& FDK_RESTRICT inMat33d, Mat33d* FDK_RESTRICT outMat) {
	//transpose the matrix 3x3
	outMat->v00 = inMat33d.v00;
	outMat->v01 = inMat33d.v10;
	outMat->v02 = inMat33d.v20;
	
	outMat->v10 = inMat33d.v01;
	outMat->v11 = inMat33d.v11;
	outMat->v12 = inMat33d.v21;
	
	outMat->v20 = inMat33d.v02;
	outMat->v21 = inMat33d.v12;
	outMat->v22 = inMat33d.v22;
}

void    Mat33dMultVector(const Mat33d&  inMat33d, const Vec3d& inVec3d, Vec3d* outVec) {
	outVec->x = inMat33d.v00 * inVec3d.x +  inMat33d.v01 * inVec3d.y + inMat33d.v02 * inVec3d.z;
	outVec->y = inMat33d.v10 * inVec3d.x +  inMat33d.v11 * inVec3d.y + inMat33d.v12 * inVec3d.z;
	outVec->z = inMat33d.v20 * inVec3d.x +  inMat33d.v21 * inVec3d.y + inMat33d.v22 * inVec3d.z;
}

//Inplace

void    Mat33dSumInplace(const Mat33d& FDK_RESTRICT r, Mat33d* FDK_RESTRICT outMat) {
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

void    Mat33dSubInplace(const Mat33d& FDK_RESTRICT r, Mat33d* FDK_RESTRICT outMat) {
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


void    Mat33dMultInplace(const Mat33d& FDK_RESTRICT r, Mat33d* FDK_RESTRICT outMat) {
	//outMat = outMat * r
	Mat33d temp = *outMat;
	
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

bool 	Mat33dInvertInplace(Mat33d* FDK_RESTRICT outMat) {
	//Invert the matrix 3x3
	
	Mat33d temp = *outMat;
	
	//determinant matrix 3x3
	//F64 determinant = temp.v00 * (temp.v11 * temp.v22 - temp.v21 * temp.v12) - temp.v01 * (temp.v10 * temp.v22 - temp.v12 * temp.v20) + temp.v02 * (temp.v10 * temp.v21 - temp.v11 * temp.v20);
	F64 determinant = Mat33dDeterminant(*outMat);
	
	//Determinant must be different from zero, else matrix can't be inverted.
	if (determinant == 0)
		return false;
	
	//Invert
	
	outMat->v00 =  (1.0/determinant) * (temp.v11 * temp.v22 - temp.v21 * temp.v12);
	outMat->v01 = -(1.0/determinant) * (temp.v01 * temp.v22 - temp.v02 * temp.v21);
	outMat->v02 =  (1.0/determinant) * (temp.v01 * temp.v12 - temp.v02 * temp.v11);
	outMat->v10 = -(1.0/determinant) * (temp.v10 * temp.v22 - temp.v12 * temp.v20);
	outMat->v11 =  (1.0/determinant) * (temp.v00 * temp.v22 - temp.v02 * temp.v20);
	outMat->v12 = -(1.0/determinant) * (temp.v00 * temp.v12 - temp.v10 * temp.v02);
	outMat->v20 =  (1.0/determinant) * (temp.v10 * temp.v21 - temp.v20 * temp.v11);
	outMat->v21 = -(1.0/determinant) * (temp.v00 * temp.v21 - temp.v20 * temp.v01);
	outMat->v22 =  (1.0/determinant) * (temp.v00 * temp.v11 - temp.v10 * temp.v01);
	return true;
}

void 	Mat33dTransposeInplace(Mat33d* FDK_RESTRICT outMat) {
	//transpose the matrix 3x3
	Mat33d temp = Mat33d( outMat->v00, outMat->v01, outMat->v02, outMat->v10, outMat->v11, outMat->v12,  outMat->v20, outMat->v21, outMat->v22);
	
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