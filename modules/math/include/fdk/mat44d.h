// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MAT44D_H__
#define __FDK_MAT44D_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/vec4d.h"
#include "fdk/vec3d.h"
#include "fdk/quatd.h"

FDK_NS_BEGIN

struct Mat44d {
	
	Mat44d(F64 _v00, F64 _v01, F64 _v02, F64 _v03, F64 _v10, F64 _v11, F64 _v12, F64 _v13, F64 _v20, F64 _v21, F64 _v22, F64 _v23, F64 _v30, F64 _v31, F64 _v32, F64 _v33) : v00(_v00), v01(_v01), v02(_v02), v03(_v03), v10(_v10), v11(_v11), v12(_v12), v13(_v13), v20(_v20), v21(_v21), v22(_v22),  v23(_v23), v30(_v30), v31(_v31), v32(_v32),  v33(_v33)  {}
	
	Mat44d(Vec4d& _row0, Vec4d& _row1, Vec4d& _row2, Vec4d& _row3) : v00(_row0.x), v01(_row0.y), v02(_row0.z), v03(_row0.w), v10(_row1.x), v11(_row1.y), v12(_row1.z), v13(_row1.w), v20(_row2.x), v21(_row2.y), v22(_row2.z), v23(_row2.w), v30(_row3.x), v31(_row3.y), v32(_row3.z), v33(_row3.w)   {}
	
	Mat44d() {}
	
	operator const F64*() const { return (const F64*)(void*)this; }
	operator F64* () const { return (F64*)(void*)this; }
	
	F64& operator()(int rowIndex, int colIndex) {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 4);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 4);
		//return ((F64**)(void*)this)[rowIndex][colIndex];
		return ((F64*)this)[rowIndex*4+colIndex];
	}
	const F64& operator()(int rowIndex, int colIndex) const {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 4);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 4);
		//return ((F64**)(void*)this)[rowIndex][colIndex];
		return ((F64*)this)[rowIndex*4+colIndex];
	}
	
	F64 v00;  //Value to set in this matrix[0,0]
	F64 v01;  //...
	F64 v02;
	F64 v03;
	
	F64 v10;
	F64 v11;
	F64 v12;
	F64 v13;
	
	F64 v20;
	F64 v21;
	F64 v22;
	F64 v23;
	
	F64 v30;
	F64 v31;
	F64 v32;
	F64 v33;  //Value to set in this matrix[3,3]
};

FDK_FORGE_API   void    Mat44dInit               (Mat44d* outMat);
FDK_FORGE_API   void    Mat44dInitWithMatrix     (const Mat44d& FDK_RESTRICT inMat, Mat44d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44dInitWithValue      (const F64 value, Mat44d* outMat);
FDK_FORGE_API   void    Mat44dInitWithRowVec     (const Vec4d& row0, const Vec4d& row1, const Vec4d& row2, const Vec4d& row3, Mat44d* outMat);
FDK_FORGE_API   void    Mat44dInitWithColumnVec  (const Vec4d& column0, const Vec4d& column1, const Vec4d& column2, const Vec4d& column3, Mat44d* outMat);
FDK_FORGE_API   void    Mat44dInitFromQuaternion (const Quatd& FDK_RESTRICT quat, Mat44d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44dGetColumn          (const Mat44d& FDK_RESTRICT  inMat44d, int column, Vec4d* outVec);
FDK_FORGE_API   void    Mat44dGetRow             (const Mat44d& FDK_RESTRICT  inMat44d, int row, Vec4d* outVec);
FDK_FORGE_API   void    Mat44dSum                (const Mat44d& FDK_RESTRICT  l, const Mat44d& FDK_RESTRICT r, Mat44d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44dSub                (const Mat44d& FDK_RESTRICT  l, const Mat44d& FDK_RESTRICT r, Mat44d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44dAbs                (const Mat44d& FDK_RESTRICT  l, Mat44d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44dMult               (const Mat44d& FDK_RESTRICT  l, const Mat44d& FDK_RESTRICT r, Mat44d* FDK_RESTRICT outMat);
FDK_FORGE_API   F64     Mat44dCoFactor           (const Mat44d& FDK_RESTRICT  inMat44d, const int row, const int col);
FDK_FORGE_API   F64     Mat44dDeterminant        (const Mat44d& FDK_RESTRICT  inMat44d);
FDK_FORGE_API   bool 	Mat44dInvert             (const Mat44d& FDK_RESTRICT inMat44d, Mat44d* FDK_RESTRICT outMat);
FDK_FORGE_API   void 	Mat44dTranspose          (const Mat44d& FDK_RESTRICT inMat44d, Mat44d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44dMultVector         (const Mat44d& FDK_RESTRICT  inMat44d, const Vec4d& FDK_RESTRICT inVec4d, Vec4d* FDK_RESTRICT outVec);

//Inplace

FDK_FORGE_API   void    Mat44dMultInplace        (const Mat44d& FDK_RESTRICT r, Mat44d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44dSumInplace         (const Mat44d& FDK_RESTRICT r, Mat44d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44dSubInplace         (const Mat44d& FDK_RESTRICT r, Mat44d* FDK_RESTRICT outMat);
FDK_FORGE_API   bool 	Mat44dInvertInplace      (Mat44d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44dTransposeInplace   (Mat44d* FDK_RESTRICT outMat);


FDK_NS_END

#endif