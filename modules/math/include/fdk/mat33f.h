// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt


#ifndef __FDK_MAT33F_H__
#define __FDK_MAT33F_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/vec3f.h"
#include "fdk/quatf.h"
#include "fdk/mat22f.h"

FDK_NS_BEGIN

struct Mat33f {
	
	Mat33f(F32 _v00, F32 _v01, F32 _v02, F32 _v10, F32 _v11, F32 _v12, F32 _v20, F32 _v21, F32 _v22) : v00(_v00), v01(_v01), v02(_v02), v10(_v10), v11(_v11), v12(_v12), v20(_v20), v21(_v21), v22(_v22)  {}
	
	Mat33f(Vec3f& _row0, Vec3f& _row1, Vec3f& _row2) : v00(_row0.x), v01(_row0.y), v02(_row0.z), v10(_row1.x), v11(_row1.y), v12(_row1.z),  v20(_row2.x), v21(_row2.y), v22(_row2.z)  {}
	
	Mat33f(Mat22f& _matRotation, Vec2f& _transfXY) : v00(_matRotation.v00), v01(_matRotation.v01), v02(_transfXY.x), v10(_matRotation.v10), v11(_matRotation.v11), v12(_transfXY.y), v20(0.f), v21(0.f), v22(1.f)  {}
	
	Mat33f() {}
	
	operator const F32*() const { return (const F32*)(void*)this; }
	operator F32* () const { return (F32*)(void*)this; }
	
	F32& operator()(int rowIndex, int colIndex) {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 3);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 3);
		//return ((F32**)(void*)this)[rowIndex][colIndex];
		return ((F32*)this)[rowIndex*3+colIndex];
	}
	const F32& operator()(int rowIndex, int colIndex) const {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 3);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 3);
		//return ((F32**)(void*)this)[rowIndex][colIndex];
		return ((F32*)this)[rowIndex*3+colIndex];
	}
	
	
	F32 v00;  //Value to set in this matrix[0,0]
	F32 v01;  //...
	F32 v02;
	
	F32 v10;
	F32 v11;
	F32 v12;
	
	F32 v20;
	F32 v21;
	F32 v22;  //Value to set in this matrix[2,2]
};

FDK_FORGE_API   void Mat33fInit               (Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33fInitWithMatrix     (const Mat33f& FDK_RESTRICT inMat, Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33fInitWithValue      (const F32 value, Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33fInitWithRowVec     (const Vec3f& FDK_RESTRICT row0, const Vec3f& FDK_RESTRICT row1, const Vec3f& FDK_RESTRICT row2, Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33fInitWithColumnVec  (const Vec3f& FDK_RESTRICT column0, const Vec3f& FDK_RESTRICT column1, const Vec3f& FDK_RESTRICT column2, Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33fInitFromQuaternion (const Quatf& FDK_RESTRICT quat, Mat33f* FDK_RESTRICT outMat);
		     
FDK_FORGE_API   void Mat33fGetColumn          (const Mat33f& FDK_RESTRICT  inMat33f, int column, Vec3f* FDK_RESTRICT outVec);
FDK_FORGE_API   void Mat33fGetRow             (const Mat33f& FDK_RESTRICT  inMat33f, int row, Vec3f* FDK_RESTRICT outVec);
FDK_FORGE_API   void Mat33fSum                (const Mat33f& FDK_RESTRICT  l, const Mat33f& FDK_RESTRICT r, Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33fSub                (const Mat33f& FDK_RESTRICT  l, const Mat33f& FDK_RESTRICT r, Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33fAbs                (const Mat33f& FDK_RESTRICT  l, Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33fMult               (const Mat33f& FDK_RESTRICT  l, const Mat33f& FDK_RESTRICT r, Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   F32  Mat33fDeterminant        (const Mat33f& FDK_RESTRICT  inMat33f);
FDK_FORGE_API   bool Mat33fInvert             (const Mat33f& FDK_RESTRICT inMat33f, Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33fTranspose          (const Mat33f& FDK_RESTRICT inMat33f, Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33fMultVector         (const Mat33f& FDK_RESTRICT  inMat33f, const Vec3f& FDK_RESTRICT inVec3f, Vec3f* FDK_RESTRICT outVec);

//Inplace

FDK_FORGE_API   void    Mat33fMultInplace      (const Mat33f& FDK_RESTRICT r, Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat33fSumInplace       (const Mat33f& FDK_RESTRICT r, Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat33fSubInplace       (const Mat33f& FDK_RESTRICT r, Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   bool 	Mat33fInvertInplace    (Mat33f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat33fTransposeInplace (Mat33f* FDK_RESTRICT outMat);


FDK_NS_END

#endif
