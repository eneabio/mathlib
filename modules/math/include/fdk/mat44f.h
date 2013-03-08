// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_MAT44F_H__
#define __FDK_MAT44F_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/vec4f.h"
#include "fdk/vec3f.h"
#include "fdk/quatf.h"

FDK_NS_BEGIN

FDK_DATA_ALIGN16 struct Mat44f {
	
	Mat44f(F32 _v00, F32 _v01, F32 _v02, F32 _v03, F32 _v10, F32 _v11, F32 _v12, F32 _v13, F32 _v20, F32 _v21, F32 _v22, F32 _v23, F32 _v30, F32 _v31, F32 _v32, F32 _v33) : v00(_v00), v01(_v01), v02(_v02), v03(_v03), v10(_v10), v11(_v11), v12(_v12), v13(_v13), v20(_v20), v21(_v21), v22(_v22),  v23(_v23), v30(_v30), v31(_v31), v32(_v32),  v33(_v33)  {}
	
	Mat44f(Vec4f& _row0, Vec4f& _row1, Vec4f& _row2, Vec4f& _row3) : v00(_row0.x), v01(_row0.y), v02(_row0.z), v03(_row0.w), v10(_row1.x), v11(_row1.y), v12(_row1.z), v13(_row1.w), v20(_row2.x), v21(_row2.y), v22(_row2.z), v23(_row2.w), v30(_row3.x), v31(_row3.y), v32(_row3.z), v33(_row3.w)   {}
	
	Mat44f() {}
	
	operator const F32*() const { return (const F32*)(void*)this; }
	operator F32* () const { return (F32*)(void*)this; }
	
	F32& operator()(int rowIndex, int colIndex) {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 4);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 4);
		//return ((F32**)(void*)this)[rowIndex][colIndex];
		return ((F32*)this)[rowIndex*4+colIndex];
	}
	const F32& operator()(int rowIndex, int colIndex) const {
		FDK_ASSERT(rowIndex >= 0);
		FDK_ASSERT(rowIndex < 4);
		FDK_ASSERT(colIndex >= 0);
		FDK_ASSERT(colIndex < 4);
		//return ((F32**)(void*)this)[rowIndex][colIndex];
		return ((F32*)this)[rowIndex*4+colIndex];
	}
	
	#if defined (FDK_USE_SSE) || defined(FDK_USE_NEON) // _WIN32 || ARM
		#if defined (FDK_OS_OSX) || (FDK_OS_IOS)
			union {
				struct {
					F32 v00;  //Value to set in this matrix[0,0]
					F32 v01;  //...
					F32 v02;
					F32 v03;
					
					F32 v10;
					F32 v11;
					F32 v12;
					F32 v13;
					
					F32 v20;
					F32 v21;
					F32 v22;
					F32 v23;
					
					F32 v30;
					F32 v31;
					F32 v32;
					F32 v33;  //Value to set in this matrix[3,3]
				};
				fdkSimdFloat4 mVec128[4];
			};
		#elif defined (FDK_OS_WIN)
		#pragma warning(disable : 4201) // disable nonstandard extension used: nameless struct/union
			union {
				FDK_DATA_ALIGN16 struct {
					F32 v00;  //Value to set in this matrix[0,0]
					F32 v01;  //...
					F32 v02;
					F32 v03;
					
					F32 v10;
					F32 v11;
					F32 v12;
					F32 v13;
					
					F32 v20;
					F32 v21;
					F32 v22;
					F32 v23;
					
					F32 v30;
					F32 v31;
					F32 v32;
					F32 v33;  //Value to set in this matrix[3,3]
				};
				fdkSimdFloat4 mVec128[4];
			};
		#endif
//	FDK_FORCE_INLINE fdkSimdFloat4	get128() const {
//		return mVec128;
//	}
//	FDK_FORCE_INLINE void	set128(fdkSimdFloat4 v128) {
//		mVec128 = v128;
//	}
	#else
		F32 v00;  //Value to set in this matrix[0,0]
		F32 v01;  //...
		F32 v02;
		F32 v03;
		
		F32 v10;
		F32 v11;
		F32 v12;
		F32 v13;
		
		F32 v20;
		F32 v21;
		F32 v22;
		F32 v23;
		
		F32 v30;
		F32 v31;
		F32 v32;
		F32 v33;  //Value to set in this matrix[3,3]
	#endif
};

FDK_FORGE_API   void    Mat44fInit               (Mat44f* outMat);
FDK_FORGE_API   void    Mat44fInitWithMatrix     (const Mat44f& FDK_RESTRICT inMat, Mat44f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44fInitWithValue      (const F32 value, Mat44f* outMat);
FDK_FORGE_API   void    Mat44fInitWithRowVec     (const Vec4f& row0, const Vec4f& row1, const Vec4f& row2, const Vec4f& row3, Mat44f* outMat);
FDK_FORGE_API   void    Mat44fInitWithColumnVec  (const Vec4f& column0, const Vec4f& column1, const Vec4f& column2, const Vec4f& column3, Mat44f* outMat);
FDK_FORGE_API   void    Mat44fInitFromQuaternion (const Quatf& FDK_RESTRICT quat, Mat44f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44fGetColumn          (const Mat44f& FDK_RESTRICT  inMat44f, int column, Vec4f* outVec);
FDK_FORGE_API   void    Mat44fGetRow             (const Mat44f& FDK_RESTRICT  inMat44f, int row, Vec4f* outVec);
FDK_FORGE_API   void    Mat44fSum                (const Mat44f& FDK_RESTRICT  l, const Mat44f& FDK_RESTRICT r, Mat44f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44fSub                (const Mat44f& FDK_RESTRICT  l, const Mat44f& FDK_RESTRICT r, Mat44f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44fAbs                (const Mat44f& FDK_RESTRICT  l, Mat44f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44fMult               (const Mat44f& FDK_RESTRICT  l, const Mat44f& FDK_RESTRICT r, Mat44f* FDK_RESTRICT outMat);
FDK_FORGE_API   F32     Mat44fCoFactor           (const Mat44f& FDK_RESTRICT  inMat44f, const int row, const int col);
FDK_FORGE_API   F32     Mat44fDeterminant        (const Mat44f& FDK_RESTRICT  inMat44f);
FDK_FORGE_API   bool 	Mat44fInvert             (const Mat44f& FDK_RESTRICT inMat44f, Mat44f* FDK_RESTRICT outMat);
FDK_FORGE_API   void 	Mat44fTranspose          (const Mat44f& FDK_RESTRICT inMat44f, Mat44f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44fMultVector         (const Mat44f& FDK_RESTRICT  inMat44f, const Vec4f& FDK_RESTRICT inVec4f, Vec4f* FDK_RESTRICT outVec);

//Inplace

FDK_FORGE_API   void    Mat44fMultInplace        (const Mat44f& FDK_RESTRICT r, Mat44f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44fSumInplace         (const Mat44f& FDK_RESTRICT r, Mat44f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44fSubInplace         (const Mat44f& FDK_RESTRICT r, Mat44f* FDK_RESTRICT outMat);
FDK_FORGE_API   bool 	Mat44fInvertInplace      (Mat44f* FDK_RESTRICT outMat);
FDK_FORGE_API   void    Mat44fTransposeInplace   (Mat44f* FDK_RESTRICT outMat);


FDK_NS_END

#endif