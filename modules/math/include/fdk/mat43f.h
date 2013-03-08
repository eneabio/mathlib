// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MAT43F_H__
#define __FDK_MAT43F_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/vec4f.h"
#include "fdk/vec3f.h"

FDK_NS_BEGIN

struct Mat43f {
	
	Mat43f(F32 _v00, F32 _v01, F32 _v02, F32 _v10, F32 _v11, F32 _v12, F32 _v20, F32 _v21, F32 _v22, F32 _v30, F32 _v31, F32 _v32 ): v00(_v00), v01(_v01), v02(_v02), v10(_v10), v11(_v11), v12(_v12), v20(_v20), v21(_v21), v22(_v22), v30(_v30), v31(_v31), v32(_v32)  {}
	
	Mat43f(Vec3f& _row0, Vec3f& _row1, Vec3f& _row2, Vec3f& _row3) : v00(_row0.x), v01(_row0.y), v02(_row0.z), v10(_row1.x), v11(_row1.y), v12(_row1.z), v20(_row2.x), v21(_row2.y), v22(_row2.z), v30(_row3.x), v31(_row3.y), v32(_row3.z)  {}
	
	Mat43f() {}
	
	operator const F32*() const { return (const F32*)(void*)this; }
	operator F32* () const { return (F32*)(void*)this; }
	
	F32& operator()(int rowIndex, int colIndex) {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 4);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 4);
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
	F32 v22;
	
	F32 v30;
	F32 v31;
	F32 v32;
};

FDK_FORGE_API   void    Mat43fInit              (Mat43f* outMat);
FDK_FORGE_API   void    Mat43fInitWithValue     (const F32 value, Mat43f* outMat);
FDK_FORGE_API   void    Mat43fInitWithRowVec    (const Vec3f& row0, const Vec3f& row1, const Vec3f& row2, const Vec3f& row3, Mat43f* outMat);
FDK_FORGE_API   void    Mat43fInitWithColumnVec (const Vec4f& column0, const Vec4f& column1, const Vec4f& column2, Mat43f* outMat);
FDK_FORGE_API   void    Mat43fGetColumn         (const Mat43f& FDK_RESTRICT  inMat43f, int column, Vec4f* outVec);
FDK_FORGE_API   void    Mat43fGetRow            (const Mat43f& FDK_RESTRICT  inMat43f, int row, Vec3f* outVec);
FDK_FORGE_API   void    Mat43fSum               (const Mat43f& FDK_RESTRICT  l, const Mat43f& FDK_RESTRICT r, Mat43f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat43fSub               (const Mat43f& FDK_RESTRICT  l, const Mat43f& FDK_RESTRICT r, Mat43f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat43fAbs               (const Mat43f& FDK_RESTRICT  l, Mat43f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat43fMultVector        (const Mat43f& FDK_RESTRICT  inMat43f, const Vec3f& FDK_RESTRICT inVec3f, Vec4f* FDK_RESTRICT outVec);

//Inplace

FDK_FORGE_API   void    Mat43fSumInplace (const Mat43f& FDK_RESTRICT r, Mat43f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat43fSubInplace (const Mat43f& FDK_RESTRICT r, Mat43f* FDK_RESTRICT outMat);


FDK_NS_END

#endif