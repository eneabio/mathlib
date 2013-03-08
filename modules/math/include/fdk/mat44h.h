// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MAT44H_H__
#define __FDK_MAT44H_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/vec4h.h"
#include "fdk/vec3h.h"
#include "fdk/mat44f.h"
//#include "fdk/quath.h"

FDK_NS_BEGIN

struct Mat44h {
	
	Mat44h(F16 _v00, F16 _v01, F16 _v02, F16 _v03, F16 _v10, F16 _v11, F16 _v12, F16 _v13, F16 _v20, F16 _v21, F16 _v22, F16 _v23, F16 _v30, F16 _v31, F16 _v32, F16 _v33) : v00(_v00), v01(_v01), v02(_v02), v03(_v03), v10(_v10), v11(_v11), v12(_v12), v13(_v13), v20(_v20), v21(_v21), v22(_v22),  v23(_v23), v30(_v30), v31(_v31), v32(_v32),  v33(_v33)  {}
	
	Mat44h(Vec4h& _row0, Vec4h& _row1, Vec4h& _row2, Vec4h& _row3) : v00(_row0.x), v01(_row0.y), v02(_row0.z), v03(_row0.w), v10(_row1.x), v11(_row1.y), v12(_row1.z), v13(_row1.w), v20(_row2.x), v21(_row2.y), v22(_row2.z), v23(_row2.w), v30(_row3.x), v31(_row3.y), v32(_row3.z), v33(_row3.w)   {}
	
	Mat44h() {}
	
	operator const F16*() const { return (const F16*)(void*)this; }
	operator F16* () const { return (F16*)(void*)this; }
	
	F16& operator()(int rowIndex, int colIndex) {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 4);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 4);
		//return ((F16**)(void*)this)[rowIndex][colIndex];
		return ((F16*)this)[rowIndex*4+colIndex];
	}
	const F16& operator()(int rowIndex, int colIndex) const {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 4);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 4);
		//return ((F16**)(void*)this)[rowIndex][colIndex];
		return ((F16*)this)[rowIndex*4+colIndex];
	}
	
	F16 v00;  //Value to set in this matrix[0,0]
	F16 v01;  //...
	F16 v02;
	F16 v03;
	
	F16 v10;
	F16 v11;
	F16 v12;
	F16 v13;
	
	F16 v20;
	F16 v21;
	F16 v22;
	F16 v23;
	
	F16 v30;
	F16 v31;
	F16 v32;
	F16 v33;  //Value to set in this matrix[3,3]
};

FDK_FORGE_API   void    Mat44hInit               (Mat44h* outMat);
FDK_FORGE_API   void    Mat44hInitWithMatrix     (const Mat44h& FDK_RESTRICT inMat, Mat44h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44hInitWithValue      (const F16 value, Mat44h* outMat);
FDK_FORGE_API   void    Mat44hInitWithRowVec     (const Vec4h& row0, const Vec4h& row1, const Vec4h& row2, const Vec4h& row3, Mat44h* outMat);
FDK_FORGE_API   void    Mat44hInitWithColumnVec  (const Vec4h& column0, const Vec4h& column1, const Vec4h& column2, const Vec4h& column3, Mat44h* outMat);
//FDK_FORGE_API   void    Mat44hInitFromQuaternion (const Quath& FDK_RESTRICT quat, Mat44h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44hGetColumn          (const Mat44h& FDK_RESTRICT  inMat44h, int column, Vec4h* outVec);
FDK_FORGE_API   void    Mat44hGetRow             (const Mat44h& FDK_RESTRICT  inMat44h, int row, Vec4h* outVec);
FDK_FORGE_API   void    Mat44hSum                (const Mat44h& FDK_RESTRICT  l, const Mat44h& FDK_RESTRICT r, Mat44h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44hSub                (const Mat44h& FDK_RESTRICT  l, const Mat44h& FDK_RESTRICT r, Mat44h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44hAbs                (const Mat44h& FDK_RESTRICT  l, Mat44h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44hMult               (const Mat44h& FDK_RESTRICT  l, const Mat44h& FDK_RESTRICT r, Mat44h* FDK_RESTRICT outMat);
FDK_FORGE_API   F16     Mat44hCoFactor           (const Mat44h& FDK_RESTRICT  inMat44h, const int row, const int col);
FDK_FORGE_API   F16     Mat44hDeterminant        (const Mat44h& FDK_RESTRICT  inMat44h);
FDK_FORGE_API   bool 	Mat44hInvert             (const Mat44h& FDK_RESTRICT inMat44h, Mat44h* FDK_RESTRICT outMat);
FDK_FORGE_API   void 	Mat44hTranspose          (const Mat44h& FDK_RESTRICT inMat44h, Mat44h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44hMultVector         (const Mat44h& FDK_RESTRICT  inMat44h, const Vec4h& FDK_RESTRICT inVec4h, Vec4h* FDK_RESTRICT outVec);

FDK_FORGE_API   void   Mat44hToMat44f        (const Mat44h&   FDK_RESTRICT  inMat44h, Mat44f*  FDK_RESTRICT outMat44f);
FDK_FORGE_API   void   Mat44fToMat44h        (const Mat44f&   FDK_RESTRICT  inMat44f, Mat44h*  FDK_RESTRICT outMat44h);

//Inplace

FDK_FORGE_API   void    Mat44hMultInplace        (const Mat44h& FDK_RESTRICT r, Mat44h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44hSumInplace         (const Mat44h& FDK_RESTRICT r, Mat44h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44hSubInplace         (const Mat44h& FDK_RESTRICT r, Mat44h* FDK_RESTRICT outMat);
FDK_FORGE_API   bool 	Mat44hInvertInplace      (Mat44h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44hTransposeInplace   (Mat44h* FDK_RESTRICT outMat);


FDK_NS_END

#endif