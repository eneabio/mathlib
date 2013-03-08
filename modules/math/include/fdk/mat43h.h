// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MAT43H_H__
#define __FDK_MAT43H_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/vec4h.h"
#include "fdk/vec3h.h"
#include "fdk/mat43f.h"

FDK_NS_BEGIN

struct Mat43h {
	
	Mat43h(F16 _v00, F16 _v01, F16 _v02, F16 _v10, F16 _v11, F16 _v12, F16 _v20, F16 _v21, F16 _v22, F16 _v30, F16 _v31, F16 _v32 ): v00(_v00), v01(_v01), v02(_v02), v10(_v10), v11(_v11), v12(_v12), v20(_v20), v21(_v21), v22(_v22), v30(_v30), v31(_v31), v32(_v32)  {}
	
	Mat43h(Vec3h& _row0, Vec3h& _row1, Vec3h& _row2, Vec3h& _row3) : v00(_row0.x), v01(_row0.y), v02(_row0.z), v10(_row1.x), v11(_row1.y), v12(_row1.z), v20(_row2.x), v21(_row2.y), v22(_row2.z), v30(_row3.x), v31(_row3.y), v32(_row3.z)  {}
	
	Mat43h() {}
	
	operator const F16*() const { return (const F16*)(void*)this; }
	operator F16* () const { return (F16*)(void*)this; }
	
	F16& operator()(int rowIndex, int colIndex) {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 4);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 4);
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
	F16 v22;
	
	F16 v30;
	F16 v31;
	F16 v32;
};

FDK_FORGE_API   void    Mat43hInit              (Mat43h* outMat);
FDK_FORGE_API   void    Mat43hInitWithValue     (const F16 value, Mat43h* outMat);
FDK_FORGE_API   void    Mat43hInitWithRowVec    (const Vec3h&  FDK_RESTRICT row0, const Vec3h& FDK_RESTRICT row1, const Vec3h& FDK_RESTRICT row2, const Vec3h& FDK_RESTRICT row3, Mat43h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat43hInitWithColumnVec (const Vec4h&  FDK_RESTRICT column0, const Vec4h& FDK_RESTRICT column1, const Vec4h& FDK_RESTRICT column2, Mat43h* outMat);
FDK_FORGE_API   void    Mat43hGetColumn         (const Mat43h& FDK_RESTRICT  inMat43h, int column, Vec4h* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Mat43hGetRow            (const Mat43h& FDK_RESTRICT  inMat43h, int row, Vec3h* FDK_RESTRICT outVec);
FDK_FORGE_API   void    Mat43hSum               (const Mat43h& FDK_RESTRICT  l, const Mat43h& FDK_RESTRICT r, Mat43h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat43hSub               (const Mat43h& FDK_RESTRICT  l, const Mat43h& FDK_RESTRICT r, Mat43h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat43hAbs               (const Mat43h& FDK_RESTRICT  l, Mat43h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat43hMultVector        (const Mat43h& FDK_RESTRICT  inMat43h, const Vec3h& FDK_RESTRICT inVec3h, Vec4h* FDK_RESTRICT outVec);

FDK_FORGE_API   void   Mat43hToMat43f        (const Mat43h&   FDK_RESTRICT  inMat43h, Mat43f*  FDK_RESTRICT outMat43f);
FDK_FORGE_API   void   Mat43fToMat43h        (const Mat43f&   FDK_RESTRICT  inMat43f, Mat43h*  FDK_RESTRICT outMat43h);

//Inplace

FDK_FORGE_API   void    Mat43hSumInplace (const Mat43h& FDK_RESTRICT r, Mat43h* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat43hSubInplace (const Mat43h& FDK_RESTRICT r, Mat43h* FDK_RESTRICT outMat);


FDK_NS_END

#endif