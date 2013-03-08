// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MAT43D_H__
#define __FDK_MAT43D_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/vec4d.h"
#include "fdk/vec3d.h"

FDK_NS_BEGIN

struct Mat43d {
	
	Mat43d(F64 _v00, F64 _v01, F64 _v02, F64 _v10, F64 _v11, F64 _v12, F64 _v20, F64 _v21, F64 _v22, F64 _v30, F64 _v31, F64 _v32 ): v00(_v00), v01(_v01), v02(_v02), v10(_v10), v11(_v11), v12(_v12), v20(_v20), v21(_v21), v22(_v22), v30(_v30), v31(_v31), v32(_v32)  {}
	
	Mat43d(Vec3d& _row0, Vec3d& _row1, Vec3d& _row2, Vec3d& _row3) : v00(_row0.x), v01(_row0.y), v02(_row0.z), v10(_row1.x), v11(_row1.y), v12(_row1.z), v20(_row2.x), v21(_row2.y), v22(_row2.z), v30(_row3.x), v31(_row3.y), v32(_row3.z)  {}
	
	Mat43d() {}
	
	operator const F64*() const { return (const F64*)(void*)this; }
	operator F64* () const { return (F64*)(void*)this; }
	
	F64& operator()(int rowIndex, int colIndex) {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 4);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 4);
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
	F64 v22;
	
	F64 v30;
	F64 v31;
	F64 v32;
};

FDK_FORGE_API   void    Mat43dInit              (Mat43d* outMat);
FDK_FORGE_API   void    Mat43dInitWithValue     (const F64 value, Mat43d* outMat);
FDK_FORGE_API   void    Mat43dInitWithRowVec    (const Vec3d& row0, const Vec3d& row1, const Vec3d& row2, const Vec3d& row3, Mat43d* outMat);
FDK_FORGE_API   void    Mat43dInitWithColumnVec (const Vec4d& column0, const Vec4d& column1, const Vec4d& column2, Mat43d* outMat);
FDK_FORGE_API   void    Mat43dGetColumn         (const Mat43d& FDK_RESTRICT  inMat43d, int column, Vec4d* outVec);
FDK_FORGE_API   void    Mat43dGetRow            (const Mat43d& FDK_RESTRICT  inMat43d, int row, Vec3d* outVec);
FDK_FORGE_API   void    Mat43dSum               (const Mat43d& FDK_RESTRICT  l, const Mat43d& FDK_RESTRICT r, Mat43d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat43dSub               (const Mat43d& FDK_RESTRICT  l, const Mat43d& FDK_RESTRICT r, Mat43d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat43dAbs               (const Mat43d& FDK_RESTRICT  l, Mat43d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat43dMultVector        (const Mat43d& FDK_RESTRICT  inMat43d, const Vec3d& FDK_RESTRICT inVec3d, Vec4d* FDK_RESTRICT outVec);

//Inplace

FDK_FORGE_API   void    Mat43dSumInplace (const Mat43d& FDK_RESTRICT r, Mat43d* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat43dSubInplace (const Mat43d& FDK_RESTRICT r, Mat43d* FDK_RESTRICT outMat);


FDK_NS_END

#endif