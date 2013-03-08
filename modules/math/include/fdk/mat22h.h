// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MAT22H_H__
#define __FDK_MAT22H_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/vec2h.h"
#include "fdk/mat22f.h"

FDK_NS_BEGIN

struct Mat22h {
	
	Mat22h(F16 _v00,F16 _v01, F16 _v10,F16 _v11) : v00(_v00),v01(_v01), v10(_v10),v11(_v11) {}
	
	Mat22h(Vec2h& _row0, Vec2h& _row1) : v00(_row0.x), v01(_row0.y), v10(_row1.x), v11(_row1.y)  {}
	
	Mat22h() {}
	
	operator const F16*() const { return (const F16*)(void*)this; }
	operator F16* () const { return (F16*)(void*)this; }
	
	F16& operator()(int rowIndex, int colIndex) {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 2);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 2);
		//return ((F16**)(void*)this)[rowIndex][colIndex];
		return ((F16*)this)[rowIndex*2+colIndex];
	}
	
	const F16& operator()(int rowIndex, int colIndex) const {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 2);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 2);
		//return ((F16**)(void*)this)[rowIndex][colIndex];
		return ((F16*)this)[rowIndex*2+colIndex];
	}
	
	F16 v00; //Value to set in this matrix[0,0]
	F16 v01; //Value to set in this matrix[0,1]
	
	F16 v10; //Value to set in this matrix[1,0]
	F16 v11; //Value to set in this matrix[1,1]
	
};

FDK_FORGE_API   void    Mat22hInit              (Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22hInitWithValue     (const F16 value, Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22hInitWithRowVec    (const Vec2h& FDK_RESTRICT row0, const Vec2h& FDK_RESTRICT row1, Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22hInitWithColumnVec (const Vec2h& FDK_RESTRICT column0, const Vec2h& FDK_RESTRICT column1, Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22hGetColumn         (const Mat22h& FDK_RESTRICT  inMat22h, int column, Vec2h* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Mat22hGetRow            (const Mat22h& FDK_RESTRICT  inMat22h, int row, Vec2h* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Mat22hSum               (const Mat22h& FDK_RESTRICT  l, const Mat22h& FDK_RESTRICT r, Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22hSub               (const Mat22h& FDK_RESTRICT  l, const Mat22h& FDK_RESTRICT r, Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22hAbs               (const Mat22h& FDK_RESTRICT  l, Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22hMult              (const Mat22h& FDK_RESTRICT  l, const Mat22h& FDK_RESTRICT r, Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   F16     Mat22hDeterminant       (const Mat22h& FDK_RESTRICT  inMat22h);
FDK_FORGE_API   bool 	Mat22hInvert            (const Mat22h& FDK_RESTRICT  inMat22h, Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   void 	Mat22hTranspose         (const Mat22h& FDK_RESTRICT  inMat22h, Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22hMultVector        (const Mat22h& FDK_RESTRICT  inMat22h, const Vec2h& FDK_RESTRICT inVec2h, Vec2h* FDK_RESTRICT outVec);

FDK_FORGE_API   void   Mat22hToMat22f        (const Mat22h& FDK_RESTRICT  inMat22h, Mat22f* FDK_RESTRICT outMat22f);
FDK_FORGE_API   void   Mat22fToMat22h        (const Mat22f& FDK_RESTRICT  inMat22f, Mat22h* FDK_RESTRICT outMat22h);

//Inplace

FDK_FORGE_API   void    Mat22hMultInplace      (const Mat22h& FDK_RESTRICT r, Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22hSumInplace       (const Mat22h& FDK_RESTRICT r, Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat22hSubInplace       (const Mat22h& FDK_RESTRICT r, Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   bool 	Mat22hInvertInplace    (Mat22h* FDK_RESTRICT outMat);
FDK_FORGE_API   void 	Mat22hTransposeInplace (Mat22h* FDK_RESTRICT outMat);

FDK_NS_END

#endif
