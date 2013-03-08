// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MAT33D_H__
#define __FDK_MAT33D_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/vec3d.h"
#include "fdk/quatd.h"
#include "fdk/mat22d.h"

FDK_NS_BEGIN

struct Mat33d {
	
	Mat33d(F64 _v00, F64 _v01, F64 _v02, F64 _v10, F64 _v11, F64 _v12, F64 _v20, F64 _v21, F64 _v22) : v00(_v00), v01(_v01), v02(_v02), v10(_v10), v11(_v11), v12(_v12), v20(_v20), v21(_v21), v22(_v22)  {}
	
	Mat33d(Vec3d& _row0, Vec3d& _row1, Vec3d& _row2) : v00(_row0.x), v01(_row0.y), v02(_row0.z), v10(_row1.x), v11(_row1.y), v12(_row1.z),  v20(_row2.x), v21(_row2.y), v22(_row2.z)  {}
	
	Mat33d(Mat22d& _matRotation, Vec2d& _transfXY) : v00(_matRotation.v00), v01(_matRotation.v01), v02(_transfXY.x), v10(_matRotation.v10), v11(_matRotation.v11), v12(_transfXY.y), v20(0.0), v21(0.0), v22(1.0)  {}
	
	Mat33d() {}
	
	operator const F64*() const { return (const F64*)(void*)this; }
	operator F64* () const { return (F64*)(void*)this; }
	
	F64& operator()(int rowIndex, int colIndex) {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 3);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 3);
		//return ((F64**)(void*)this)[rowIndex][colIndex];
		return ((F64*)this)[rowIndex*3+colIndex];
	}
	const F64& operator()(int rowIndex, int colIndex) const {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 3);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 3);
		//return ((F64**)(void*)this)[rowIndex][colIndex];
		return ((F64*)this)[rowIndex*3+colIndex];
	}
	
	
	F64 v00;  //Value to set in this matrix[0,0]
	F64 v01;  //...
	F64 v02;
	
	F64 v10;
	F64 v11;
	F64 v12;
	
	F64 v20;
	F64 v21;
	F64 v22;  //Value to set in this matrix[2,2]
};

FDK_FORGE_API   void Mat33dInit               (Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33dInitWithMatrix     (const Mat33d& FDK_RESTRICT inMat, Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33dInitWithValue      (const F64 value, Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33dInitWithRowVec     (const Vec3d& FDK_RESTRICT row0, const Vec3d& FDK_RESTRICT row1, const Vec3d& FDK_RESTRICT row2, Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33dInitWithColumnVec  (const Vec3d& FDK_RESTRICT column0, const Vec3d& FDK_RESTRICT column1, const Vec3d& FDK_RESTRICT column2, Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33dInitFromQuaternion (const Quatd& FDK_RESTRICT quat, Mat33d* FDK_RESTRICT outMat);

FDK_FORGE_API   void Mat33dGetColumn          (const Mat33d& FDK_RESTRICT  inMat33d, int column, Vec3d* FDK_RESTRICT outVec);
FDK_FORGE_API   void Mat33dGetRow             (const Mat33d& FDK_RESTRICT  inMat33d, int row, Vec3d* FDK_RESTRICT outVec);
FDK_FORGE_API   void Mat33dSum                (const Mat33d& FDK_RESTRICT  l, const Mat33d& FDK_RESTRICT r, Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33dSub                (const Mat33d& FDK_RESTRICT  l, const Mat33d& FDK_RESTRICT r, Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33dAbs                (const Mat33d& FDK_RESTRICT  l, Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33dMult               (const Mat33d& FDK_RESTRICT  l, const Mat33d& FDK_RESTRICT r, Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   F64  Mat33dDeterminant        (const Mat33d& FDK_RESTRICT  inMat33d);
FDK_FORGE_API   bool Mat33dInvert             (const Mat33d& FDK_RESTRICT inMat33d, Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33dTranspose          (const Mat33d& FDK_RESTRICT inMat33d, Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33dMultVector         (const Mat33d& FDK_RESTRICT  inMat33d, const Vec3d& FDK_RESTRICT inVec3d, Vec3d* FDK_RESTRICT outVec);

//Inplace

FDK_FORGE_API   void    Mat33dMultInplace      (const Mat33d& FDK_RESTRICT r, Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat33dSumInplace       (const Mat33d& FDK_RESTRICT r, Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat33dSubInplace       (const Mat33d& FDK_RESTRICT r, Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   bool 	Mat33dInvertInplace    (Mat33d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat33dTransposeInplace (Mat33d* FDK_RESTRICT outMat);

FDK_NS_END

#endif
