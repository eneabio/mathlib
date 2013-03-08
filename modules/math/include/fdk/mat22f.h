// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MAT22F_H__
#define __FDK_MAT22F_H__


#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
//#include "fdk/quatf.h"
#include "fdk/vec2f.h"

FDK_NS_BEGIN

struct Mat22f {
	
	Mat22f(F32 _v00,F32 _v01, F32 _v10,F32 _v11) : v00(_v00),v01(_v01), v10(_v10),v11(_v11) {}
	
	Mat22f(Vec2f& _row0, Vec2f& _row1) : v00(_row0.x), v01(_row0.y), v10(_row1.x), v11(_row1.y)  {}
	
	Mat22f() {}
	
	operator const F32*() const { return (const F32*)(void*)this; }
	operator F32* () const { return (F32*)(void*)this; }
	
	F32& operator()(int rowIndex, int colIndex) {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 2);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 2);
		//return ((F32**)(void*)this)[rowIndex][colIndex];
		return ((F32*)this)[rowIndex*2+colIndex];
	}
	
	const F32& operator()(int rowIndex, int colIndex) const {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 2);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 2);
		//return ((F32**)(void*)this)[rowIndex][colIndex];
		return ((F32*)this)[rowIndex*2+colIndex];
	}
	
	F32 v00; //Value to set in this matrix[0,0]
	F32 v01; //Value to set in this matrix[0,1]
	
	F32 v10; //Value to set in this matrix[1,0]
	F32 v11; //Value to set in this matrix[1,1]
	
};

FDK_FORGE_API   void    Mat22fInit              (Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22fInitWithValue     (const F32 value, Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22fInitWithRowVec    (const Vec2f& FDK_RESTRICT row0, const Vec2f& FDK_RESTRICT row1, Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22fInitWithColumnVec (const Vec2f& FDK_RESTRICT column0, const Vec2f& FDK_RESTRICT column1, Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22fGetColumn         (const Mat22f& FDK_RESTRICT  inMat22f, int column, Vec2f* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Mat22fGetRow            (const Mat22f& FDK_RESTRICT  inMat22f, int row, Vec2f* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Mat22fSum               (const Mat22f& FDK_RESTRICT  l, const Mat22f& FDK_RESTRICT r, Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22fSub               (const Mat22f& FDK_RESTRICT  l, const Mat22f& FDK_RESTRICT r, Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22fAbs               (const Mat22f& FDK_RESTRICT  l, Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22fMult              (const Mat22f& FDK_RESTRICT  l, const Mat22f& FDK_RESTRICT r, Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   F32     Mat22fDeterminant       (const Mat22f& FDK_RESTRICT  inMat22f);
FDK_FORGE_API   bool 	Mat22fInvert            (const Mat22f& FDK_RESTRICT  inMat22f, Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   void 	Mat22fTranspose         (const Mat22f& FDK_RESTRICT  inMat22f, Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22fMultVector        (const Mat22f& FDK_RESTRICT  inMat22f, const Vec2f& FDK_RESTRICT inVec2f, Vec2f* FDK_RESTRICT outVec);
//Inplace

FDK_FORGE_API   void    Mat22fMultInplace      (const Mat22f& FDK_RESTRICT r, Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22fSumInplace       (const Mat22f& FDK_RESTRICT r, Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22fSubInplace       (const Mat22f& FDK_RESTRICT r, Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   bool 	Mat22fInvertInplace    (Mat22f* FDK_RESTRICT outMat);
FDK_FORGE_API   void 	Mat22fTransposeInplace (Mat22f* FDK_RESTRICT outMat);


FDK_NS_END

#endif
