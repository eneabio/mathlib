// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MAT22D_H__
#define __FDK_MAT22D_H__


#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
//#include "fdk/quatd.h"
#include "fdk/vec2d.h"

FDK_NS_BEGIN

struct Mat22d {
	
	Mat22d(F64 _v00,F64 _v01, F64 _v10,F64 _v11) : v00(_v00),v01(_v01), v10(_v10),v11(_v11) {}
	
	Mat22d(Vec2d& _row0, Vec2d& _row1) : v00(_row0.x), v01(_row0.y), v10(_row1.x), v11(_row1.y)  {}
	
	Mat22d() {}
	
	operator const F64*() const { return (const F64*)(void*)this; }
	operator F64* () const { return (F64*)(void*)this; }
	
	F64& operator()(int rowIndex, int colIndex) {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 2);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 2);
		//return ((F64**)(void*)this)[rowIndex][colIndex];
		return ((F64*)this)[rowIndex*2+colIndex];
	}
	
	const F64& operator()(int rowIndex, int colIndex) const {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 2);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 2);
		//return ((F64**)(void*)this)[rowIndex][colIndex];
		return ((F64*)this)[rowIndex*2+colIndex];
	}
	
	F64 v00; //Value to set in this matrix[0,0]
	F64 v01; //Value to set in this matrix[0,1]
	
	F64 v10; //Value to set in this matrix[1,0]
	F64 v11; //Value to set in this matrix[1,1]
	
};

FDK_FORGE_API   void    Mat22dInit              (Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22dInitWithValue     (const F64 value, Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22dInitWithRowVec    (const Vec2d& FDK_RESTRICT row0, const Vec2d& FDK_RESTRICT row1, Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22dInitWithColumnVec (const Vec2d& FDK_RESTRICT column0, const Vec2d& FDK_RESTRICT column1, Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22dGetColumn         (const Mat22d& FDK_RESTRICT  inMat22d, int column, Vec2d* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Mat22dGetRow            (const Mat22d& FDK_RESTRICT  inMat22d, int row, Vec2d* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Mat22dSum               (const Mat22d& FDK_RESTRICT  l, const Mat22d& FDK_RESTRICT r, Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22dSub               (const Mat22d& FDK_RESTRICT  l, const Mat22d& FDK_RESTRICT r, Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22dAbs               (const Mat22d& FDK_RESTRICT  l, Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22dMult              (const Mat22d& FDK_RESTRICT  l, const Mat22d& FDK_RESTRICT r, Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   F64     Mat22dDeterminant       (const Mat22d& FDK_RESTRICT  inMat22d);
FDK_FORGE_API   bool 	Mat22dInvert            (const Mat22d& FDK_RESTRICT  inMat22d, Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   void 	Mat22dTranspose         (const Mat22d& FDK_RESTRICT  inMat22d, Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22dMultVector        (const Mat22d& FDK_RESTRICT  inMat22d, const Vec2d& FDK_RESTRICT inVec2d, Vec2d* FDK_RESTRICT outVec);
//Inplace

FDK_FORGE_API   void    Mat22dMultInplace      (const Mat22d& FDK_RESTRICT r, Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22dSumInplace       (const Mat22d& FDK_RESTRICT r, Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22dSubInplace       (const Mat22d& FDK_RESTRICT r, Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   bool 	Mat22dInvertInplace    (Mat22d* FDK_RESTRICT outMat);
FDK_FORGE_API   void 	Mat22dTransposeInplace (Mat22d* FDK_RESTRICT outMat);

FDK_NS_END

#endif
