// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MAT33H_H__
#define __FDK_MAT33H_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/vec3h.h"
#include "fdk/quatd.h"
#include "fdk/mat22h.h"
#include "fdk/mat33f.h"

FDK_NS_BEGIN

struct Mat33h {
	
	Mat33h(F16 _v00, F16 _v01, F16 _v02, F16 _v10, F16 _v11, F16 _v12, F16 _v20, F16 _v21, F16 _v22) : v00(_v00), v01(_v01), v02(_v02), v10(_v10), v11(_v11), v12(_v12), v20(_v20), v21(_v21), v22(_v22)  {}
	
	Mat33h(Vec3h& _row0, Vec3h& _row1, Vec3h& _row2) : v00(_row0.x), v01(_row0.y), v02(_row0.z), v10(_row1.x), v11(_row1.y), v12(_row1.z),  v20(_row2.x), v21(_row2.y), v22(_row2.z)  {}
	
	//Mat33h(Mat22h& _matRotation, Vec2d& _transfXY) : v00(_matRotation.v00), v01(_matRotation.v01), v02(_transfXY.x), v10(_matRotation.v10), v11(_matRotation.v11), v12(_transfXY.y), v20(0.0), v21(0.0), v22(1.0)  {}
	
	Mat33h() {}
	
	operator const F16*() const { return (const F16*)(void*)this; }
	operator F16* () const { return (F16*)(void*)this; }
	
	F16& operator()(int rowIndex, int colIndex) {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 3);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 3);
		//return ((F16**)(void*)this)[rowIndex][colIndex];
		return ((F16*)this)[rowIndex*3+colIndex];
	}
	const F16& operator()(int rowIndex, int colIndex) const {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 3);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 3);
		//return ((F16**)(void*)this)[rowIndex][colIndex];
		return ((F16*)this)[rowIndex*3+colIndex];
	}
	
	
	F16 v00;  //Value to set in this matrix[0,0]
	F16 v01;  //...
	F16 v02;
	
	F16 v10;
	F16 v11;
	F16 v12;
	
	F16 v20;
	F16 v21;
	F16 v22;  //Value to set in this matrix[2,2]
};

FDK_FORGE_API   void Mat33hInit               (Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33hInitWithMatrix     (const Mat33h& FDK_RESTRICT inMat, Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33hInitWithValue      (const F16 value, Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33hInitWithRowVec     (const Vec3h& FDK_RESTRICT row0, const Vec3h& FDK_RESTRICT row1, const Vec3h& FDK_RESTRICT row2, Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33hInitWithColumnVec  (const Vec3h& FDK_RESTRICT column0, const Vec3h& FDK_RESTRICT column1, const Vec3h& FDK_RESTRICT column2, Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33hInitFromQuaternion (const Quatd& FDK_RESTRICT quat, Mat33h* FDK_RESTRICT outMat);

FDK_FORGE_API   void Mat33hGetColumn          (const Mat33h& FDK_RESTRICT  inMat33h, int column, Vec3h* FDK_RESTRICT outVec);
FDK_FORGE_API   void Mat33hGetRow             (const Mat33h& FDK_RESTRICT  inMat33h, int row, Vec3h* FDK_RESTRICT outVec);
FDK_FORGE_API   void Mat33hSum                (const Mat33h& FDK_RESTRICT  l, const Mat33h& FDK_RESTRICT r, Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33hSub                (const Mat33h& FDK_RESTRICT  l, const Mat33h& FDK_RESTRICT r, Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33hAbs                (const Mat33h& FDK_RESTRICT  l, Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33hMult               (const Mat33h& FDK_RESTRICT  l, const Mat33h& FDK_RESTRICT r, Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   F16  Mat33hDeterminant        (const Mat33h& FDK_RESTRICT  inMat33h);
FDK_FORGE_API   bool Mat33hInvert             (const Mat33h& FDK_RESTRICT inMat33h, Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33hTranspose          (const Mat33h& FDK_RESTRICT inMat33h, Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   void Mat33hMultVector         (const Mat33h& FDK_RESTRICT  inMat33h, const Vec3h& FDK_RESTRICT inVec3h, Vec3h* FDK_RESTRICT outVec);

FDK_FORGE_API   void   Mat33hToMat33f        (const Mat33h&   FDK_RESTRICT inMat33h, Mat33f*  FDK_RESTRICT outMat33f);
FDK_FORGE_API   void   Mat33fToMat33h        (const Mat33f&   FDK_RESTRICT  inMat33f, Mat33h* FDK_RESTRICT outMat33h);

//Inplace

FDK_FORGE_API   void    Mat33hMultInplace      (const Mat33h& FDK_RESTRICT r, Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat33hSumInplace       (const Mat33h& FDK_RESTRICT r, Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat33hSubInplace       (const Mat33h& FDK_RESTRICT r, Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   bool 	Mat33hInvertInplace    (Mat33h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat33hTransposeInplace (Mat33h* FDK_RESTRICT outMat);

FDK_NS_END

#endif
