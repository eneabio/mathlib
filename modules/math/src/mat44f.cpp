// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/mathf.h"
#include "fdk/mat44f.h"
#include "fdk/mat33f.h"
//#include "fdk/memory.h"

FDK_NS_BEGIN

void    Mat44fInit(Mat44f* outMat) {
	//with identity matrix
	outMat->v00 = 1.f;
	outMat->v01 = 0.f;
	outMat->v02 = 0.f;
	outMat->v03 = 0.f;
	
	outMat->v10 = 0.f;
	outMat->v11 = 1.f;
	outMat->v12 = 0.f;
	outMat->v13 = 0.f;
	
	outMat->v20 = 0.f;
	outMat->v21 = 0.f;
	outMat->v22 = 1.f;
	outMat->v23 = 0.f;
	
	outMat->v30 = 0.f;
	outMat->v31 = 0.f;
	outMat->v32 = 0.f;
	outMat->v33 = 1.f;
	
}

void    Mat44fInitWithMatrix(const Mat44f& inMat, Mat44f* outMat) {
	outMat->v00 = inMat.v00;
	outMat->v01 = inMat.v01;
	outMat->v02 = inMat.v02;
	outMat->v03 = inMat.v03;
	
	outMat->v10 = inMat.v10;
	outMat->v11 = inMat.v11;
	outMat->v12 = inMat.v12;
	outMat->v13 = inMat.v13;
	
	outMat->v20 = inMat.v20;
	outMat->v21 = inMat.v21;
	outMat->v22 = inMat.v22;
	outMat->v23 = inMat.v23;
	
	outMat->v30 = inMat.v30;
	outMat->v31 = inMat.v31;
	outMat->v32 = inMat.v32;
	outMat->v33 = inMat.v33;
	
}

void    Mat44fInitWithValue(const F32 value, Mat44f* outMat) {
	outMat->v00 = value;
	outMat->v01 = value;
	outMat->v02 = value;
	outMat->v03 = value;
	
	outMat->v10 = value;
	outMat->v11 = value;
	outMat->v12 = value;
	outMat->v13 = value;
	
	outMat->v20 = value;
	outMat->v21 = value;
	outMat->v22 = value;
	outMat->v23 = value;
	
	outMat->v30 = value;
	outMat->v31 = value;
	outMat->v32 = value;
	outMat->v33 = value;
	
}

void    Mat44fInitWithRowVec(const Vec4f& row0, const Vec4f& row1, const Vec4f& row2, const Vec4f& row3, Mat44f* outMat) {
	//row 0
	outMat->v00 = row0.x;
	outMat->v01 = row0.y;
	outMat->v02 = row0.z;
	outMat->v03 = row0.w;
	
	//row 1
	outMat->v10 = row1.x;
	outMat->v11 = row1.y;
	outMat->v12 = row1.z;
	outMat->v13 = row1.w;
	
	//row 2
	outMat->v20 = row2.x;
	outMat->v21 = row2.y;
	outMat->v22 = row2.z;
	outMat->v23 = row2.w;
	
	//row 3
	outMat->v30 = row3.x;
	outMat->v31 = row3.y;
	outMat->v32 = row3.z;
	outMat->v33 = row3.w;
	
}

void    Mat44fInitWithColumnVec(const Vec4f& column0, const Vec4f& column1, const Vec4f& column2, const Vec4f& column3, Mat44f* outMat) {
	//column 0
	outMat->v00 = column0.x;
	outMat->v10 = column0.y;
	outMat->v20 = column0.z;
	outMat->v30 = column0.w;
	
	//column 1
	outMat->v01 = column1.x;
	outMat->v11 = column1.y;
	outMat->v21 = column1.z;
	outMat->v31 = column1.w;
	
	//column 2
	outMat->v02 = column2.x;
	outMat->v12 = column2.y;
	outMat->v22 = column2.z;
	outMat->v32 = column2.w;
	
	//column 3
	outMat->v03 = column3.x;
	outMat->v13 = column3.y;
	outMat->v23 = column3.z;
	outMat->v33 = column3.w;
	
}

void    Mat44fInitFromQuaternion(const Quatf& quat, Mat44f* outMat) {
	Mat33f matQuat;
	Mat33fInitFromQuaternion(quat, &matQuat);
	Mat44fInit(outMat);
	
	outMat->v00 = matQuat.v00;
	outMat->v01 = matQuat.v01;
	outMat->v02 = matQuat.v02;
	
	outMat->v10 = matQuat.v10;
	outMat->v11 = matQuat.v11;
	outMat->v12 = matQuat.v12;
	
	outMat->v20 = matQuat.v20;
	outMat->v21 = matQuat.v21;
	outMat->v22 = matQuat.v22;
	
}

void    Mat44fGetColumn(const Mat44f& FDK_RESTRICT  inMat44f, int column, Vec4f* outVec) {
	
	FDK_ASSERT(column >= 0 && column <=3);
	
	if (column == 0) {
		outVec->x = inMat44f.v00;
		outVec->y = inMat44f.v10;
		outVec->z = inMat44f.v20;
		outVec->w = inMat44f.v30;
	}
	if (column == 1) {
		outVec->x = inMat44f.v01;
		outVec->y = inMat44f.v11;
		outVec->z = inMat44f.v21;
		outVec->w = inMat44f.v31;
	}
	if (column == 2) {
		outVec->x = inMat44f.v02;
		outVec->y = inMat44f.v12;
		outVec->z = inMat44f.v22;
		outVec->w = inMat44f.v32;
	}
	if (column == 3) {
		outVec->x = inMat44f.v03;
		outVec->y = inMat44f.v13;
		outVec->z = inMat44f.v23;
		outVec->w = inMat44f.v33;
	}
}

void    Mat44fGetRow(const Mat44f& FDK_RESTRICT  inMat44f, int row, Vec4f* outVec) {
	
	FDK_ASSERT(row >= 0 && row <=3);
	
	if (row == 0) {
		outVec->x = inMat44f.v00;
		outVec->y = inMat44f.v01;
		outVec->z = inMat44f.v02;
		outVec->w = inMat44f.v03;
	}
	if (row == 1) {
		outVec->x = inMat44f.v10;
		outVec->y = inMat44f.v11;
		outVec->z = inMat44f.v12;
		outVec->w = inMat44f.v13;
	}
	if (row == 2) {
		outVec->x = inMat44f.v20;
		outVec->y = inMat44f.v21;
		outVec->z = inMat44f.v22;
		outVec->w = inMat44f.v23;
	}
	if (row == 3) {
		outVec->x = inMat44f.v30;
		outVec->y = inMat44f.v31;
		outVec->z = inMat44f.v32;
		outVec->w = inMat44f.v33;
	}
}

void    Mat44fSum(const Mat44f& FDK_RESTRICT  l, const Mat44f& FDK_RESTRICT r, Mat44f* FDK_RESTRICT outMat) {
	//outMat = l + r
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			outMat->mVec128[0] = _mm_add_ps(l.mVec128[0], r.mVec128[0]);
			outMat->mVec128[1] = _mm_add_ps(l.mVec128[1], r.mVec128[1]);
			outMat->mVec128[2] = _mm_add_ps(l.mVec128[2], r.mVec128[2]);
			outMat->mVec128[3] = _mm_add_ps(l.mVec128[3], r.mVec128[3]);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//outVec->mVec128 = vaddq_f32(l.mVec128, r.mVec128);
		#endif
	#else
		outMat->v00 = l.v00 + r.v00;
		outMat->v01 = l.v01 + r.v01;
		outMat->v02 = l.v02 + r.v02;
		outMat->v03 = l.v03 + r.v03;
		
		outMat->v10 = l.v10 + r.v10;
		outMat->v11 = l.v11 + r.v11;
		outMat->v12 = l.v12 + r.v12;
		outMat->v13 = l.v13 + r.v13;
		
		outMat->v20 = l.v20 + r.v20;
		outMat->v21 = l.v21 + r.v21;
		outMat->v22 = l.v22 + r.v22;
		outMat->v23 = l.v23 + r.v23;
		
		outMat->v30 = l.v30 + r.v30;
		outMat->v31 = l.v31 + r.v31;
		outMat->v32 = l.v32 + r.v32;
		outMat->v33 = l.v33 + r.v33;
	#endif
	
	
}

void    Mat44fSub(const Mat44f& FDK_RESTRICT  l, const Mat44f& FDK_RESTRICT r, Mat44f* FDK_RESTRICT outMat) {
	//outMat = l - r
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			outMat->mVec128[0] = _mm_sub_ps(l.mVec128[0], r.mVec128[0]);
			outMat->mVec128[1] = _mm_sub_ps(l.mVec128[1], r.mVec128[1]);
			outMat->mVec128[2] = _mm_sub_ps(l.mVec128[2], r.mVec128[2]);
			outMat->mVec128[3] = _mm_sub_ps(l.mVec128[3], r.mVec128[3]);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//outVec->mVec128 = vaddq_f32(l.mVec128, r.mVec128);
		#endif
	#else
		outMat->v00 = l.v00 - r.v00;
		outMat->v01 = l.v01 - r.v01;
		outMat->v02 = l.v02 - r.v02;
		outMat->v03 = l.v03 - r.v03;
		
		outMat->v10 = l.v10 - r.v10;
		outMat->v11 = l.v11 - r.v11;
		outMat->v12 = l.v12 - r.v12;
		outMat->v13 = l.v13 - r.v13;
		
		outMat->v20 = l.v20 - r.v20;
		outMat->v21 = l.v21 - r.v21;
		outMat->v22 = l.v22 - r.v22;
		outMat->v23 = l.v23 - r.v23;
		
		outMat->v30 = l.v30 - r.v30;
		outMat->v31 = l.v31 - r.v31;
		outMat->v32 = l.v32 - r.v32;
		outMat->v33 = l.v33 - r.v33;
	#endif
	
}

void    Mat44fAbs(const Mat44f& FDK_RESTRICT  l, Mat44f* FDK_RESTRICT outMat) {
	//outMat = l - r
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			__m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF));
			outMat->mVec128[0] = _mm_and_ps(l.mVec128[0],mask);
			outMat->mVec128[1] = _mm_and_ps(l.mVec128[1],mask);
			outMat->mVec128[2] = _mm_and_ps(l.mVec128[2],mask);
			outMat->mVec128[3] = _mm_and_ps(l.mVec128[3],mask);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//outVec->mVec128 = vaddq_f32(l.mVec128, r.mVec128);
		#endif
	#else
		outMat->v00 = Fabsf(l.v00);
		outMat->v01 = Fabsf(l.v01);
		outMat->v02 = Fabsf(l.v02);
		outMat->v03 = Fabsf(l.v03);
	
		outMat->v10 = Fabsf(l.v10);
		outMat->v11 = Fabsf(l.v11);
		outMat->v12 = Fabsf(l.v12);
		outMat->v13 = Fabsf(l.v13);
	
		outMat->v20 = Fabsf(l.v20);
		outMat->v21 = Fabsf(l.v21);
		outMat->v22 = Fabsf(l.v22);
		outMat->v23 = Fabsf(l.v23);
	
		outMat->v30 = Fabsf(l.v30);
		outMat->v31 = Fabsf(l.v31);
		outMat->v32 = Fabsf(l.v32);
		outMat->v33 = Fabsf(l.v33);
	#endif
}

F32 Mat44fCoFactor(const Mat44f& FDK_RESTRICT  m, int row, int col) {
	return	 (( m((row+1)&3,(col+1)&3) * m((row+2)&3,(col+2)&3) * m((row+3)&3,(col+3)&3) +
		   m((row+1)&3,(col+2)&3) * m((row+2)&3,(col+3)&3)* m((row+3)&3,(col+1)&3) +
		   m((row+1)&3,(col+3)&3) * m((row+2)&3,(col+1)&3) *m((row+3)&3,(col+2)&3))
		  -  (m((row+3)&3,(col+1)&3) *m ((row+2)&3,(col+2)&3) * m((row+1)&3,(col+3)&3) +
		      m((row+3)&3,(col+2)&3) * m((row+2)&3,(col+3)&3) * m((row+1)&3,(col+1)&3) +
		      m((row+3)&3,(col+3)&3) * m((row+2)&3,(col+1)&3) * m((row+1)&3,(col+2)&3))) * ((row + col) & 1 ? -1.0f : +1.0f);
}

F32     Mat44fDeterminant(const Mat44f& FDK_RESTRICT  inMat44f) {
	//determinant matrix 4x4
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			__m128 Fac0;
			{
				//      valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
				//      valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
				//      valType SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
				//      valType SubFactor13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
			
				__m128 Swp0a = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(3, 3, 3, 3));
				__m128 Swp0b = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(2, 2, 2, 2));
			
				__m128 Swp00 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(2, 2, 2, 2));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(3, 3, 3, 3));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac0 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 Fac1;
			{
				//      valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
				//      valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
				//      valType SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
				//      valType SubFactor14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
			
				__m128 Swp0a = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(3, 3, 3, 3));
				__m128 Swp0b = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(1, 1, 1, 1));
			
				__m128 Swp00 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(1, 1, 1, 1));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(3, 3, 3, 3));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac1 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
		
			__m128 Fac2;
			{
				//      valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
				//      valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
				//      valType SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
				//      valType SubFactor15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
			
				__m128 Swp0a = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(2, 2, 2, 2));
				__m128 Swp0b = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(1, 1, 1, 1));
			
				__m128 Swp00 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(1, 1, 1, 1));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(2, 2, 2, 2));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac2 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 Fac3;
			{
				//      valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
				//      valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
				//      valType SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
				//      valType SubFactor16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
			
				__m128 Swp0a = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(3, 3, 3, 3));
				__m128 Swp0b = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(0, 0, 0, 0));
			
				__m128 Swp00 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(0, 0, 0, 0));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(3, 3, 3, 3));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac3 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 Fac4;
			{
				//      valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
				//      valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
				//      valType SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
				//      valType SubFactor17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
			
				__m128 Swp0a = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(2, 2, 2, 2));
				__m128 Swp0b = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(0, 0, 0, 0));
			
				__m128 Swp00 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(0, 0, 0, 0));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(2, 2, 2, 2));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac4 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 Fac5;
			{
				//      valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
				//      valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
				//      valType SubFactor12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
				//      valType SubFactor18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];
			
				__m128 Swp0a = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(1, 1, 1, 1));
				__m128 Swp0b = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(0, 0, 0, 0));
			
				__m128 Swp00 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(0, 0, 0, 0));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(1, 1, 1, 1));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac5 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 SignA = _mm_set_ps( 1.0f,-1.0f, 1.0f,-1.0f);
			__m128 SignB = _mm_set_ps(-1.0f, 1.0f,-1.0f, 1.0f);
		
			// m[1][0]
			// m[0][0]
			// m[0][0]
			// m[0][0]
			__m128 Temp0 = _mm_shuffle_ps(inMat44f.mVec128[1], inMat44f.mVec128[0], _MM_SHUFFLE(0, 0, 0, 0));
			__m128 Vec0 = _mm_shuffle_ps(Temp0, Temp0, _MM_SHUFFLE(2, 2, 2, 0));
		
			// m[1][1]
			// m[0][1]
			// m[0][1]
			// m[0][1]
			__m128 Temp1 = _mm_shuffle_ps(inMat44f.mVec128[1], inMat44f.mVec128[0], _MM_SHUFFLE(1, 1, 1, 1));
			__m128 Vec1 = _mm_shuffle_ps(Temp1, Temp1, _MM_SHUFFLE(2, 2, 2, 0));
		
			// m[1][2]
			// m[0][2]
			// m[0][2]
			// m[0][2]
			__m128 Temp2 = _mm_shuffle_ps(inMat44f.mVec128[1], inMat44f.mVec128[0], _MM_SHUFFLE(2, 2, 2, 2));
			__m128 Vec2 = _mm_shuffle_ps(Temp2, Temp2, _MM_SHUFFLE(2, 2, 2, 0));
		
			// m[1][3]
			// m[0][3]
			// m[0][3]
			// m[0][3]
			__m128 Temp3 = _mm_shuffle_ps(inMat44f.mVec128[1], inMat44f.mVec128[0], _MM_SHUFFLE(3, 3, 3, 3));
			__m128 Vec3 = _mm_shuffle_ps(Temp3, Temp3, _MM_SHUFFLE(2, 2, 2, 0));
		
			// col0
			// + (Vec1[0] * Fac0[0] - Vec2[0] * Fac1[0] + Vec3[0] * Fac2[0]),
			// - (Vec1[1] * Fac0[1] - Vec2[1] * Fac1[1] + Vec3[1] * Fac2[1]),
			// + (Vec1[2] * Fac0[2] - Vec2[2] * Fac1[2] + Vec3[2] * Fac2[2]),
			// - (Vec1[3] * Fac0[3] - Vec2[3] * Fac1[3] + Vec3[3] * Fac2[3]),
			__m128 Mul00 = _mm_mul_ps(Vec1, Fac0);
			__m128 Mul01 = _mm_mul_ps(Vec2, Fac1);
			__m128 Mul02 = _mm_mul_ps(Vec3, Fac2);
			__m128 Sub00 = _mm_sub_ps(Mul00, Mul01);
			__m128 Add00 = _mm_add_ps(Sub00, Mul02);
			__m128 Inv0 = _mm_mul_ps(SignB, Add00);
		
			// col1
			// - (Vec0[0] * Fac0[0] - Vec2[0] * Fac3[0] + Vec3[0] * Fac4[0]),
			// + (Vec0[0] * Fac0[1] - Vec2[1] * Fac3[1] + Vec3[1] * Fac4[1]),
			// - (Vec0[0] * Fac0[2] - Vec2[2] * Fac3[2] + Vec3[2] * Fac4[2]),
			// + (Vec0[0] * Fac0[3] - Vec2[3] * Fac3[3] + Vec3[3] * Fac4[3]),
			__m128 Mul03 = _mm_mul_ps(Vec0, Fac0);
			__m128 Mul04 = _mm_mul_ps(Vec2, Fac3);
			__m128 Mul05 = _mm_mul_ps(Vec3, Fac4);
			__m128 Sub01 = _mm_sub_ps(Mul03, Mul04);
			__m128 Add01 = _mm_add_ps(Sub01, Mul05);
			__m128 Inv1 = _mm_mul_ps(SignA, Add01);
		
			// col2
			// + (Vec0[0] * Fac1[0] - Vec1[0] * Fac3[0] + Vec3[0] * Fac5[0]),
			// - (Vec0[0] * Fac1[1] - Vec1[1] * Fac3[1] + Vec3[1] * Fac5[1]),
			// + (Vec0[0] * Fac1[2] - Vec1[2] * Fac3[2] + Vec3[2] * Fac5[2]),
			// - (Vec0[0] * Fac1[3] - Vec1[3] * Fac3[3] + Vec3[3] * Fac5[3]),
			__m128 Mul06 = _mm_mul_ps(Vec0, Fac1);
			__m128 Mul07 = _mm_mul_ps(Vec1, Fac3);
			__m128 Mul08 = _mm_mul_ps(Vec3, Fac5);
			__m128 Sub02 = _mm_sub_ps(Mul06, Mul07);
			__m128 Add02 = _mm_add_ps(Sub02, Mul08);
			__m128 Inv2 = _mm_mul_ps(SignB, Add02);
		
			// col3
			// - (Vec1[0] * Fac2[0] - Vec1[0] * Fac4[0] + Vec2[0] * Fac5[0]),
			// + (Vec1[0] * Fac2[1] - Vec1[1] * Fac4[1] + Vec2[1] * Fac5[1]),
			// - (Vec1[0] * Fac2[2] - Vec1[2] * Fac4[2] + Vec2[2] * Fac5[2]),
			// + (Vec1[0] * Fac2[3] - Vec1[3] * Fac4[3] + Vec2[3] * Fac5[3]));
			__m128 Mul09 = _mm_mul_ps(Vec0, Fac2);
			__m128 Mul10 = _mm_mul_ps(Vec1, Fac4);
			__m128 Mul11 = _mm_mul_ps(Vec2, Fac5);
			__m128 Sub03 = _mm_sub_ps(Mul09, Mul10);
			__m128 Add03 = _mm_add_ps(Sub03, Mul11);
			__m128 Inv3 = _mm_mul_ps(SignA, Add03);
		
			__m128 Row0 = _mm_shuffle_ps(Inv0, Inv1, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 Row1 = _mm_shuffle_ps(Inv2, Inv3, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 Row2 = _mm_shuffle_ps(Row0, Row1, _MM_SHUFFLE(2, 0, 2, 0));
		
			//      valType DeterminMat44f.mVec128ant = m[0][0] * Inverse[0][0]
			//                                              + m[0][1] * Inverse[1][0]
			//                                              + m[0][2] * Inverse[2][0]
			//                                              + m[0][3] * Inverse[3][0];
			#if defined (__SSE4_1__)
				__m128 Det0 = _mm_dp_ps(inMat44f.mVec128[0], Row2, 0xff);
				return _mm_cvtss_f32(Det0);
			#elif defined (_M_IX86_FP )
				__m128 Det0 = _mm_dp_ps(inMat44f.mVec128[0], Row2, 0xff);
				return _mm_cvtss_f32(Det0);
			#else
				__m128 mul0 = _mm_mul_ps(inMat44f.mVec128[0], Row2);
				__m128 swp0 = _mm_shuffle_ps(mul0, mul0, _MM_SHUFFLE(2, 3, 0, 1));
				__m128 add0 = _mm_add_ps(mul0, swp0);
				__m128 swp1 = _mm_shuffle_ps(add0, add0, _MM_SHUFFLE(0, 1, 2, 3));
				__m128 Det0 = _mm_add_ps(add0, swp1);
				return _mm_cvtss_f32(Det0);
			#endif
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
		#endif
	#else
		return	inMat44f(0,0) * Mat44fCoFactor(inMat44f, 0, 0) +
	inMat44f(0,1) * Mat44fCoFactor(inMat44f, 0, 1) +
	inMat44f(0,2) * Mat44fCoFactor(inMat44f, 0, 2) +
	inMat44f(0,3) * Mat44fCoFactor(inMat44f, 0, 3);
	#endif
}

void    Mat44fMult(const Mat44f& FDK_RESTRICT  l, const Mat44f& FDK_RESTRICT r, Mat44f* FDK_RESTRICT outMat) {
	
	//outMat = l * r
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			__m128 row0;
			__m128 row1;
			__m128 row2;
			__m128 row3;
			__m128 value0;

			// Compute row 0 of the matrix product:
			value0	= _mm_shuffle_ps(l.mVec128[0], l.mVec128[0], _MM_SHUFFLE(0, 0, 0, 0));
			row0 	= _mm_mul_ps(r.mVec128[0], value0);

			value0	= _mm_shuffle_ps(l.mVec128[0], l.mVec128[0], _MM_SHUFFLE(1, 1, 1, 1));
			row0	= _mm_add_ps(row0, _mm_mul_ps(r.mVec128[1], value0));

			value0	= _mm_shuffle_ps(l.mVec128[0], l.mVec128[0], _MM_SHUFFLE(2, 2, 2, 2));
			row0	= _mm_add_ps(row0, _mm_mul_ps(r.mVec128[2], value0));

			value0	= _mm_shuffle_ps(l.mVec128[0], l.mVec128[0], _MM_SHUFFLE(3, 3, 3, 3));
			row0	= _mm_add_ps(row0, _mm_mul_ps(r.mVec128[3], value0));

			// Compute row 1 of the matrix product:
			value0	= _mm_shuffle_ps(l.mVec128[1], l.mVec128[1], _MM_SHUFFLE(0, 0, 0, 0));
			row1 	= _mm_mul_ps(r.mVec128[0], value0);

			value0	= _mm_shuffle_ps(l.mVec128[1], l.mVec128[1], _MM_SHUFFLE(1, 1, 1, 1));
			row1	= _mm_add_ps(row1, _mm_mul_ps(r.mVec128[1], value0));

			value0	= _mm_shuffle_ps(l.mVec128[1], l.mVec128[1], _MM_SHUFFLE(2, 2, 2, 2));
			row1	= _mm_add_ps(row1, _mm_mul_ps(r.mVec128[2], value0));

			value0	= _mm_shuffle_ps(l.mVec128[1], l.mVec128[1], _MM_SHUFFLE(3, 3, 3, 3));
			row1	= _mm_add_ps(row1, _mm_mul_ps(r.mVec128[3], value0));

			// Compute row 2 of the matrix product:
			value0	= _mm_shuffle_ps(l.mVec128[2], l.mVec128[2], _MM_SHUFFLE(0, 0, 0, 0));
			row2	= _mm_mul_ps(r.mVec128[0], value0);

			value0	= _mm_shuffle_ps(l.mVec128[2], l.mVec128[2], _MM_SHUFFLE(1, 1, 1, 1));
			row2	= _mm_add_ps(row2, _mm_mul_ps(r.mVec128[1], value0));

			value0	= _mm_shuffle_ps(l.mVec128[2], l.mVec128[2], _MM_SHUFFLE(2, 2, 2, 2));
			row2	= _mm_add_ps(row2, _mm_mul_ps(r.mVec128[2], value0));

			value0	= _mm_shuffle_ps(l.mVec128[2], l.mVec128[2], _MM_SHUFFLE(3, 3, 3, 3));
			row2	= _mm_add_ps(row2, _mm_mul_ps(r.mVec128[3], value0));

			// Compute row 3 of the matrix product:
			value0	= _mm_shuffle_ps(l.mVec128[3], l.mVec128[3], _MM_SHUFFLE(0, 0, 0, 0));
			row3 	= _mm_mul_ps(r.mVec128[0], value0);

			value0	= _mm_shuffle_ps(l.mVec128[3], l.mVec128[3], _MM_SHUFFLE(1, 1, 1, 1));
			row3	= _mm_add_ps(row3, _mm_mul_ps(r.mVec128[1], value0));

			value0	= _mm_shuffle_ps(l.mVec128[3], l.mVec128[3], _MM_SHUFFLE(2, 2, 2, 2));
			row3	= _mm_add_ps(row3, _mm_mul_ps(r.mVec128[2], value0));

			value0	= _mm_shuffle_ps(l.mVec128[3], l.mVec128[3], _MM_SHUFFLE(3, 3, 3, 3));
			row3	= _mm_add_ps(row3, _mm_mul_ps(r.mVec128[3], value0));

			// Write results back to memory:
			outMat->mVec128[0]	= row0;
			outMat->mVec128[1]	= row1;
			outMat->mVec128[2]	= row2;
			outMat->mVec128[3]	= row3;
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do

		#endif
	#else
		outMat->v00 = l.v00 * r.v00 + l.v01 * r.v10 + l.v02 * r.v20 + l.v03 * r.v30;
		outMat->v01 = l.v00 * r.v01 + l.v01 * r.v11 + l.v02 * r.v21 + l.v03 * r.v31;
		outMat->v02 = l.v00 * r.v02 + l.v01 * r.v12 + l.v02 * r.v22 + l.v03 * r.v32;
		outMat->v03 = l.v00 * r.v03 + l.v01 * r.v13 + l.v02 * r.v23 + l.v03 * r.v33;
	
		outMat->v10 = l.v10 * r.v00 + l.v11 * r.v10 + l.v12 * r.v20 + l.v13 * r.v30;
		outMat->v11 = l.v10 * r.v01 + l.v11 * r.v11 + l.v12 * r.v21 + l.v13 * r.v31;
		outMat->v12 = l.v10 * r.v02 + l.v11 * r.v12 + l.v12 * r.v22 + l.v13 * r.v32;
		outMat->v13 = l.v10 * r.v03 + l.v11 * r.v13 + l.v12 * r.v23 + l.v13 * r.v33;
	
		outMat->v20 = l.v20 * r.v00 + l.v21 * r.v10 + l.v22 * r.v20 + l.v23 * r.v30;
		outMat->v21 = l.v20 * r.v01 + l.v21 * r.v11 + l.v22 * r.v21 + l.v23 * r.v31;
		outMat->v22 = l.v20 * r.v02 + l.v21 * r.v12 + l.v22 * r.v22 + l.v23 * r.v32;
		outMat->v23 = l.v20 * r.v03 + l.v21 * r.v13 + l.v22 * r.v23 + l.v23 * r.v33;
	
		outMat->v30 = l.v30 * r.v00 + l.v31 * r.v10 + l.v32 * r.v20 + l.v33 * r.v30;
		outMat->v31 = l.v30 * r.v01 + l.v31 * r.v11 + l.v32 * r.v21 + l.v33 * r.v31;
		outMat->v32 = l.v30 * r.v02 + l.v31 * r.v12 + l.v32 * r.v22 + l.v33 * r.v32;
		outMat->v33 = l.v30 * r.v03 + l.v31 * r.v13 + l.v32 * r.v23 + l.v33 * r.v33;
	#endif
}

bool 	Mat44fInvert(const Mat44f& FDK_RESTRICT inMat44f, Mat44f* FDK_RESTRICT outMat) {
	//Invert the matrix 4x4
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			__m128 Fac0;
			{
				//      valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
				//      valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
				//      valType SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
				//      valType SubFactor13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
			
				__m128 Swp0a = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(3, 3, 3, 3));
				__m128 Swp0b = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(2, 2, 2, 2));
			
				__m128 Swp00 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(2, 2, 2, 2));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(3, 3, 3, 3));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac0 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 Fac1;
			{
				//      valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
				//      valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
				//      valType SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
				//      valType SubFactor14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
			
				__m128 Swp0a = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(3, 3, 3, 3));
				__m128 Swp0b = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(1, 1, 1, 1));
			
				__m128 Swp00 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(1, 1, 1, 1));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(3, 3, 3, 3));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac1 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
		
			__m128 Fac2;
			{
				//      valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
				//      valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
				//      valType SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
				//      valType SubFactor15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
			
				__m128 Swp0a = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(2, 2, 2, 2));
				__m128 Swp0b = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(1, 1, 1, 1));
			
				__m128 Swp00 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(1, 1, 1, 1));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(2, 2, 2, 2));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac2 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 Fac3;
			{
				//      valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
				//      valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
				//      valType SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
				//      valType SubFactor16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
			
				__m128 Swp0a = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(3, 3, 3, 3));
				__m128 Swp0b = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(0, 0, 0, 0));
			
				__m128 Swp00 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(0, 0, 0, 0));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(3, 3, 3, 3));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac3 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 Fac4;
			{
				//      valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
				//      valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
				//      valType SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
				//      valType SubFactor17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
			
				__m128 Swp0a = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(2, 2, 2, 2));
				__m128 Swp0b = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(0, 0, 0, 0));
			
				__m128 Swp00 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(0, 0, 0, 0));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(2, 2, 2, 2));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac4 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 Fac5;
			{
				//      valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
				//      valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
				//      valType SubFactor12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
				//      valType SubFactor18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];
			
				__m128 Swp0a = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(1, 1, 1, 1));
				__m128 Swp0b = _mm_shuffle_ps(inMat44f.mVec128[3], inMat44f.mVec128[2], _MM_SHUFFLE(0, 0, 0, 0));
			
				__m128 Swp00 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(0, 0, 0, 0));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[1], _MM_SHUFFLE(1, 1, 1, 1));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac5 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 SignA = _mm_set_ps( 1.0f,-1.0f, 1.0f,-1.0f);
			__m128 SignB = _mm_set_ps(-1.0f, 1.0f,-1.0f, 1.0f);
		
			// m[1][0]
			// m[0][0]
			// m[0][0]
			// m[0][0]
			__m128 Temp0 = _mm_shuffle_ps(inMat44f.mVec128[1], inMat44f.mVec128[0], _MM_SHUFFLE(0, 0, 0, 0));
			__m128 Vec0 = _mm_shuffle_ps(Temp0, Temp0, _MM_SHUFFLE(2, 2, 2, 0));
		
			// m[1][1]
			// m[0][1]
			// m[0][1]
			// m[0][1]
			__m128 Temp1 = _mm_shuffle_ps(inMat44f.mVec128[1], inMat44f.mVec128[0], _MM_SHUFFLE(1, 1, 1, 1));
			__m128 Vec1 = _mm_shuffle_ps(Temp1, Temp1, _MM_SHUFFLE(2, 2, 2, 0));
		
			// m[1][2]
			// m[0][2]
			// m[0][2]
			// m[0][2]
			__m128 Temp2 = _mm_shuffle_ps(inMat44f.mVec128[1], inMat44f.mVec128[0], _MM_SHUFFLE(2, 2, 2, 2));
			__m128 Vec2 = _mm_shuffle_ps(Temp2, Temp2, _MM_SHUFFLE(2, 2, 2, 0));
		
			// m[1][3]
			// m[0][3]
			// m[0][3]
			// m[0][3]
			__m128 Temp3 = _mm_shuffle_ps(inMat44f.mVec128[1], inMat44f.mVec128[0], _MM_SHUFFLE(3, 3, 3, 3));
			__m128 Vec3 = _mm_shuffle_ps(Temp3, Temp3, _MM_SHUFFLE(2, 2, 2, 0));
		
			// col0
			// + (Vec1[0] * Fac0[0] - Vec2[0] * Fac1[0] + Vec3[0] * Fac2[0]),
			// - (Vec1[1] * Fac0[1] - Vec2[1] * Fac1[1] + Vec3[1] * Fac2[1]),
			// + (Vec1[2] * Fac0[2] - Vec2[2] * Fac1[2] + Vec3[2] * Fac2[2]),
			// - (Vec1[3] * Fac0[3] - Vec2[3] * Fac1[3] + Vec3[3] * Fac2[3]),
			__m128 Mul00 = _mm_mul_ps(Vec1, Fac0);
			__m128 Mul01 = _mm_mul_ps(Vec2, Fac1);
			__m128 Mul02 = _mm_mul_ps(Vec3, Fac2);
			__m128 Sub00 = _mm_sub_ps(Mul00, Mul01);
			__m128 Add00 = _mm_add_ps(Sub00, Mul02);
			__m128 Inv0 = _mm_mul_ps(SignB, Add00);
		
			// col1
			// - (Vec0[0] * Fac0[0] - Vec2[0] * Fac3[0] + Vec3[0] * Fac4[0]),
			// + (Vec0[0] * Fac0[1] - Vec2[1] * Fac3[1] + Vec3[1] * Fac4[1]),
			// - (Vec0[0] * Fac0[2] - Vec2[2] * Fac3[2] + Vec3[2] * Fac4[2]),
			// + (Vec0[0] * Fac0[3] - Vec2[3] * Fac3[3] + Vec3[3] * Fac4[3]),
			__m128 Mul03 = _mm_mul_ps(Vec0, Fac0);
			__m128 Mul04 = _mm_mul_ps(Vec2, Fac3);
			__m128 Mul05 = _mm_mul_ps(Vec3, Fac4);
			__m128 Sub01 = _mm_sub_ps(Mul03, Mul04);
			__m128 Add01 = _mm_add_ps(Sub01, Mul05);
			__m128 Inv1 = _mm_mul_ps(SignA, Add01);
		
			// col2
			// + (Vec0[0] * Fac1[0] - Vec1[0] * Fac3[0] + Vec3[0] * Fac5[0]),
			// - (Vec0[0] * Fac1[1] - Vec1[1] * Fac3[1] + Vec3[1] * Fac5[1]),
			// + (Vec0[0] * Fac1[2] - Vec1[2] * Fac3[2] + Vec3[2] * Fac5[2]),
			// - (Vec0[0] * Fac1[3] - Vec1[3] * Fac3[3] + Vec3[3] * Fac5[3]),
			__m128 Mul06 = _mm_mul_ps(Vec0, Fac1);
			__m128 Mul07 = _mm_mul_ps(Vec1, Fac3);
			__m128 Mul08 = _mm_mul_ps(Vec3, Fac5);
			__m128 Sub02 = _mm_sub_ps(Mul06, Mul07);
			__m128 Add02 = _mm_add_ps(Sub02, Mul08);
			__m128 Inv2 = _mm_mul_ps(SignB, Add02);
		
			// col3
			// - (Vec1[0] * Fac2[0] - Vec1[0] * Fac4[0] + Vec2[0] * Fac5[0]),
			// + (Vec1[0] * Fac2[1] - Vec1[1] * Fac4[1] + Vec2[1] * Fac5[1]),
			// - (Vec1[0] * Fac2[2] - Vec1[2] * Fac4[2] + Vec2[2] * Fac5[2]),
			// + (Vec1[0] * Fac2[3] - Vec1[3] * Fac4[3] + Vec2[3] * Fac5[3]));
			__m128 Mul09 = _mm_mul_ps(Vec0, Fac2);
			__m128 Mul10 = _mm_mul_ps(Vec1, Fac4);
			__m128 Mul11 = _mm_mul_ps(Vec2, Fac5);
			__m128 Sub03 = _mm_sub_ps(Mul09, Mul10);
			__m128 Add03 = _mm_add_ps(Sub03, Mul11);
			__m128 Inv3 = _mm_mul_ps(SignA, Add03);
		
			__m128 Row0 = _mm_shuffle_ps(Inv0, Inv1, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 Row1 = _mm_shuffle_ps(Inv2, Inv3, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 Row2 = _mm_shuffle_ps(Row0, Row1, _MM_SHUFFLE(2, 0, 2, 0));
		
			//      valType DeterminMat44f.mVec128ant = m[0][0] * inMat44f.mVec128verse[0][0]
			//                                              + m[0][1] * inMat44f.mVec128verse[1][0]
			//                                              + m[0][2] * inMat44f.mVec128verse[2][0]
			//                                              + m[0][3] * inMat44f.mVec128verse[3][0];
			#if defined (__SSE4_1__)
				__m128 Det0 = _mm_dp_ps(inMat44f.mVec128[0], Row2, 0xff);
			#elif defined (_M_IX86_FP )
				__m128 Det0 = _mm_dp_ps(inMat44f.mVec128[0], Row2, 0xff);
			#else
				__m128 mul0 = _mm_mul_ps(inMat44f.mVec128[0], Row2);
				__m128 swp0 = _mm_shuffle_ps(mul0, mul0, _MM_SHUFFLE(2, 3, 0, 1));
				__m128 add0 = _mm_add_ps(mul0, swp0);
				__m128 swp1 = _mm_shuffle_ps(add0, add0, _MM_SHUFFLE(0, 1, 2, 3));
				__m128 Det0 = _mm_add_ps(add0, swp1);	
			#endif

			__m128 one = _mm_set_ps( 1.0,1.0f, 1.0f,1.0f); //Enea to do: verify one...
			__m128 Rcp0 = _mm_div_ps(one, Det0);
			//__m128 Rcp0 = _mm_rcp_ps(Det0);
		
			//      inMat44f.mVec128verse /= DeterminMat44f.mVec128ant;
			outMat->mVec128[0] = _mm_mul_ps(Inv0, Rcp0);
			outMat->mVec128[1] = _mm_mul_ps(Inv1, Rcp0);
			outMat->mVec128[2] = _mm_mul_ps(Inv2, Rcp0);
			outMat->mVec128[3] = _mm_mul_ps(Inv3, Rcp0);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
		#endif
	#else
		//determinant matrix 4x4
		F32 determinant = Mat44fDeterminant(inMat44f);
	
		//Determinant must be different from zero, else matrix can't be inverted.
		if (FdkEqf32(determinant, 0.f, FDK_F32_EPSILON))
			return false;
	
		F32 rhDet = (1.f/determinant);
		//Invert
	
		outMat->v00 = rhDet * (inMat44f.v11 * inMat44f.v22 * inMat44f.v33 + inMat44f.v12 * inMat44f.v23 * inMat44f.v31 + inMat44f.v13 * inMat44f.v21 * inMat44f.v32 - inMat44f.v11 * inMat44f.v23 * inMat44f.v32 - inMat44f.v12 * inMat44f.v21 * inMat44f.v33 - inMat44f.v13 * inMat44f.v22 * inMat44f.v31);
	
		outMat->v01 = rhDet * (inMat44f.v01 * inMat44f.v23 * inMat44f.v32 + inMat44f.v02 * inMat44f.v21 * inMat44f.v33 + inMat44f.v03 * inMat44f.v22 * inMat44f.v31 - inMat44f.v01 * inMat44f.v22 * inMat44f.v33 - inMat44f.v02 * inMat44f.v23 * inMat44f.v31 - inMat44f.v03 * inMat44f.v21 * inMat44f.v32);
	
		outMat->v02 = rhDet * (inMat44f.v01 * inMat44f.v12 * inMat44f.v33 + inMat44f.v02 * inMat44f.v13 * inMat44f.v31 + inMat44f.v03 * inMat44f.v11 * inMat44f.v32 - inMat44f.v01 * inMat44f.v13 * inMat44f.v32 - inMat44f.v02 * inMat44f.v11 * inMat44f.v33 - inMat44f.v03 * inMat44f.v12 * inMat44f.v31);
	
		outMat->v03 = rhDet * (inMat44f.v01 * inMat44f.v13 * inMat44f.v22 + inMat44f.v02 * inMat44f.v11 * inMat44f.v23 + inMat44f.v03 * inMat44f.v12 * inMat44f.v21 - inMat44f.v01 * inMat44f.v12 * inMat44f.v23 - inMat44f.v02 * inMat44f.v13 * inMat44f.v21 - inMat44f.v03 * inMat44f.v11 * inMat44f.v22);
	
		outMat->v10 = rhDet * (inMat44f.v10 * inMat44f.v23 * inMat44f.v32 + inMat44f.v12 * inMat44f.v20 * inMat44f.v33 + inMat44f.v13 * inMat44f.v22 * inMat44f.v30 - inMat44f.v10 * inMat44f.v22 * inMat44f.v33 - inMat44f.v12 * inMat44f.v23 * inMat44f.v30 - inMat44f.v13 * inMat44f.v20 * inMat44f.v32);
	
		outMat->v11 = rhDet * (inMat44f.v00 * inMat44f.v22 * inMat44f.v33 + inMat44f.v02 * inMat44f.v23 * inMat44f.v30 + inMat44f.v03 * inMat44f.v20 * inMat44f.v32 - inMat44f.v00 * inMat44f.v23 * inMat44f.v32 - inMat44f.v02 * inMat44f.v20 * inMat44f.v33 - inMat44f.v03 * inMat44f.v22 * inMat44f.v30);
	
		outMat->v12 = rhDet * (inMat44f.v00 * inMat44f.v13 * inMat44f.v32 + inMat44f.v02 * inMat44f.v10 * inMat44f.v33 + inMat44f.v03 * inMat44f.v12 * inMat44f.v30 - inMat44f.v00 * inMat44f.v12 * inMat44f.v33 - inMat44f.v02 * inMat44f.v13 * inMat44f.v30 - inMat44f.v03 * inMat44f.v10 * inMat44f.v32);
	
		outMat->v13 = rhDet * (inMat44f.v00 * inMat44f.v12 * inMat44f.v23 + inMat44f.v02 * inMat44f.v13 * inMat44f.v20 + inMat44f.v03 * inMat44f.v10 * inMat44f.v22 - inMat44f.v00 * inMat44f.v13 * inMat44f.v22 - inMat44f.v02 * inMat44f.v10 * inMat44f.v23 - inMat44f.v03 * inMat44f.v12 * inMat44f.v20);
	
		outMat->v20 = rhDet * (inMat44f.v10 * inMat44f.v21 * inMat44f.v33 + inMat44f.v11 * inMat44f.v23 * inMat44f.v30 + inMat44f.v13 * inMat44f.v20 * inMat44f.v31 - inMat44f.v10 * inMat44f.v23 * inMat44f.v31 - inMat44f.v11 * inMat44f.v20 * inMat44f.v33 - inMat44f.v13 * inMat44f.v21 * inMat44f.v30);
	
		outMat->v21 = rhDet * (inMat44f.v00 * inMat44f.v23 * inMat44f.v31 + inMat44f.v01 * inMat44f.v20 * inMat44f.v33 + inMat44f.v03 * inMat44f.v21 * inMat44f.v30 - inMat44f.v00 * inMat44f.v21 * inMat44f.v33 - inMat44f.v01 * inMat44f.v23 * inMat44f.v30 - inMat44f.v03 * inMat44f.v20 * inMat44f.v31);
	
		outMat->v22 = rhDet * (inMat44f.v00 * inMat44f.v11 * inMat44f.v33 + inMat44f.v01 * inMat44f.v13 * inMat44f.v30 + inMat44f.v03 * inMat44f.v10 * inMat44f.v31 - inMat44f.v00 * inMat44f.v13 * inMat44f.v31 - inMat44f.v01 * inMat44f.v10 * inMat44f.v33 - inMat44f.v03 * inMat44f.v11 * inMat44f.v30);
	
		outMat->v23 = rhDet * (inMat44f.v00 * inMat44f.v13 * inMat44f.v21 + inMat44f.v01 * inMat44f.v10 * inMat44f.v23 + inMat44f.v03 * inMat44f.v11 * inMat44f.v20 - inMat44f.v00 * inMat44f.v11 * inMat44f.v23 - inMat44f.v01 * inMat44f.v13 * inMat44f.v20 - inMat44f.v03 * inMat44f.v10 * inMat44f.v21);
	
		outMat->v30 = rhDet * (inMat44f.v10 * inMat44f.v22 * inMat44f.v31 + inMat44f.v11 * inMat44f.v20 * inMat44f.v32 + inMat44f.v12 * inMat44f.v21 * inMat44f.v30 - inMat44f.v10 * inMat44f.v21 * inMat44f.v32 - inMat44f.v11 * inMat44f.v22 * inMat44f.v30 - inMat44f.v12 * inMat44f.v20 * inMat44f.v31);
	
		outMat->v31 = rhDet * (inMat44f.v00 * inMat44f.v21 * inMat44f.v32 + inMat44f.v01 * inMat44f.v22 * inMat44f.v30 + inMat44f.v02 * inMat44f.v20 * inMat44f.v31 - inMat44f.v00 * inMat44f.v22 * inMat44f.v31 - inMat44f.v01 * inMat44f.v20 * inMat44f.v32 - inMat44f.v02 * inMat44f.v21 * inMat44f.v30);
	
		outMat->v32 = rhDet * (inMat44f.v00 * inMat44f.v12 * inMat44f.v31 + inMat44f.v01 * inMat44f.v10 * inMat44f.v32 + inMat44f.v02 * inMat44f.v11 * inMat44f.v30 - inMat44f.v00 * inMat44f.v11 * inMat44f.v32 - inMat44f.v01 * inMat44f.v12 * inMat44f.v30 - inMat44f.v02 * inMat44f.v10 * inMat44f.v31);
	
		outMat->v33 = rhDet * (inMat44f.v00 * inMat44f.v11 * inMat44f.v22 + inMat44f.v01 * inMat44f.v12 * inMat44f.v20 + inMat44f.v02 * inMat44f.v10 * inMat44f.v21 - inMat44f.v00 * inMat44f.v12 * inMat44f.v21 - inMat44f.v01 * inMat44f.v10 * inMat44f.v22 - inMat44f.v02 * inMat44f.v11 * inMat44f.v20);
	#endif
	return true;
}

void 	Mat44fTranspose(const Mat44f& FDK_RESTRICT inMat44f, Mat44f* FDK_RESTRICT outMat) {
	//transpose the matrix 4x4
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			__m128 tmp3, tmp2, tmp1, tmp0; 
			tmp0   = _mm_shuffle_ps(inMat44f.mVec128[0], inMat44f.mVec128[1], 0x44);          
            tmp2   = _mm_shuffle_ps(inMat44f.mVec128[0], inMat44f.mVec128[1], 0xEE);          
            tmp1   = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[3], 0x44);          
            tmp3   = _mm_shuffle_ps(inMat44f.mVec128[2], inMat44f.mVec128[3], 0xEE);          
                                                                    
            outMat->mVec128[0] = _mm_shuffle_ps(tmp0, tmp1, 0x88);              
            outMat->mVec128[1] = _mm_shuffle_ps(tmp0, tmp1, 0xDD);              
            outMat->mVec128[2] = _mm_shuffle_ps(tmp2, tmp3, 0x88);              
            outMat->mVec128[3] = _mm_shuffle_ps(tmp2, tmp3, 0xDD); 
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//outVec->mVec128 = vaddq_f32(l.mVec128, r.mVec128);
		#endif
	#else
		outMat->v00 = inMat44f.v00;
		outMat->v01 = inMat44f.v10;
		outMat->v02 = inMat44f.v20;
		outMat->v03 = inMat44f.v30;
	
		outMat->v10 = inMat44f.v01;
		outMat->v11 = inMat44f.v11;
		outMat->v12 = inMat44f.v21;
		outMat->v13 = inMat44f.v31;
	
		outMat->v20 = inMat44f.v02;
		outMat->v21 = inMat44f.v12;
		outMat->v22 = inMat44f.v22;
		outMat->v23 = inMat44f.v32;
	
		outMat->v30 = inMat44f.v03;
		outMat->v31 = inMat44f.v13;
		outMat->v32 = inMat44f.v23;
		outMat->v33 = inMat44f.v33;
	#endif
}

void    Mat44fMultVector(const Mat44f&  inMat44f, const Vec4f& inVec4f, Vec4f* outVec) {
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			#if defined (__SSE4_1__)
				__m128 prod1 = _mm_dp_ps (inMat44f.mVec128[0], inVec4f.mVec128, 0xFF);
				__m128 prod2 = _mm_dp_ps (inMat44f.mVec128[1], inVec4f.mVec128, 0xFF);
				__m128 prod3 = _mm_dp_ps (inMat44f.mVec128[2], inVec4f.mVec128, 0xFF);
				__m128 prod4 = _mm_dp_ps (inMat44f.mVec128[3], inVec4f.mVec128, 0xFF);

				outVec->mVec128 = _mm_shuffle_ps(_mm_movelh_ps(prod1, prod2), _mm_movelh_ps(prod3, prod4),  _MM_SHUFFLE(2, 0, 2, 0));
			#elif defined (_M_IX86_FP )
				__m128 prod1 = _mm_dp_ps (inMat44f.mVec128[0], inVec4f.mVec128, 0xFF);
				__m128 prod2 = _mm_dp_ps (inMat44f.mVec128[1], inVec4f.mVec128, 0xFF);
				__m128 prod3 = _mm_dp_ps (inMat44f.mVec128[2], inVec4f.mVec128, 0xFF);
				__m128 prod4 = _mm_dp_ps (inMat44f.mVec128[3], inVec4f.mVec128, 0xFF);

				outVec->mVec128 = _mm_shuffle_ps(_mm_movelh_ps(prod1, prod2), _mm_movelh_ps(prod3, prod4),  _MM_SHUFFLE(2, 0, 2, 0));
			#else
				__m128 prod1 = _mm_mul_ps(inMat44f.mVec128[0], inVec4f.mVec128);
				__m128 prod2 = _mm_mul_ps(inMat44f.mVec128[1], inVec4f.mVec128);
				__m128 prod3 = _mm_mul_ps(inMat44f.mVec128[2], inVec4f.mVec128);
				__m128 prod4 = _mm_mul_ps(inMat44f.mVec128[3], inVec4f.mVec128);

				outVec->mVec128 = _mm_hadd_ps(_mm_hadd_ps(prod1, prod2), _mm_hadd_ps(prod3, prod4));
			#endif
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//outVec->mVec128 = vaddq_f32(l.mVec128, r.mVec128);
		#endif
	#else
		outVec->x = inMat44f.v00 * inVec4f.x +  inMat44f.v01 * inVec4f.y + inMat44f.v02 * inVec4f.z + inMat44f.v03 * inVec4f.w;
		outVec->y = inMat44f.v10 * inVec4f.x +  inMat44f.v11 * inVec4f.y + inMat44f.v12 * inVec4f.z + inMat44f.v13 * inVec4f.w;
		outVec->z = inMat44f.v20 * inVec4f.x +  inMat44f.v21 * inVec4f.y + inMat44f.v22 * inVec4f.z + inMat44f.v23 * inVec4f.w;
		outVec->w = inMat44f.v30 * inVec4f.x +  inMat44f.v31 * inVec4f.y + inMat44f.v32 * inVec4f.z + inMat44f.v33 * inVec4f.w;
	#endif
}

//Inplace

void    Mat44fSumInplace(const Mat44f& FDK_RESTRICT r, Mat44f* FDK_RESTRICT outMat) {
	//outMat = outMat + r
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			outMat->mVec128[0] = _mm_add_ps(outMat->mVec128[0], r.mVec128[0]);
			outMat->mVec128[1] = _mm_add_ps(outMat->mVec128[1], r.mVec128[1]);
			outMat->mVec128[2] = _mm_add_ps(outMat->mVec128[2], r.mVec128[2]);
			outMat->mVec128[3] = _mm_add_ps(outMat->mVec128[3], r.mVec128[3]);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//vaddq_f32(v1.mVec128, v2.mVec128);
		#endif
	#else
		outMat->v00 = outMat->v00 + r.v00;
		outMat->v01 = outMat->v01 + r.v01;
		outMat->v02 = outMat->v02 + r.v02;
		outMat->v03 = outMat->v03 + r.v03;
	
		outMat->v10 = outMat->v10 + r.v10;
		outMat->v11 = outMat->v11 + r.v11;
		outMat->v12 = outMat->v12 + r.v12;
		outMat->v13 = outMat->v13 + r.v13;
	
		outMat->v20 = outMat->v20 + r.v20;
		outMat->v21 = outMat->v21 + r.v21;
		outMat->v22 = outMat->v22 + r.v22;
		outMat->v23 = outMat->v23 + r.v23;
	
		outMat->v30 = outMat->v30 + r.v30;
		outMat->v31 = outMat->v31 + r.v31;
		outMat->v32 = outMat->v32 + r.v32;
		outMat->v33 = outMat->v33 + r.v33;
	#endif
}

void    Mat44fSubInplace(const Mat44f& FDK_RESTRICT r, Mat44f* FDK_RESTRICT outMat) {
	//outMat = outMat + r
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			outMat->mVec128[0] = _mm_sub_ps(outMat->mVec128[0], r.mVec128[0]);
			outMat->mVec128[1] = _mm_sub_ps(outMat->mVec128[1], r.mVec128[1]);
			outMat->mVec128[2] = _mm_sub_ps(outMat->mVec128[2], r.mVec128[2]);
			outMat->mVec128[3] = _mm_sub_ps(outMat->mVec128[3], r.mVec128[3]);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//vaddq_f32(v1.mVec128, v2.mVec128);
		#endif
	#else
		outMat->v00 = outMat->v00 - r.v00;
		outMat->v01 = outMat->v01 - r.v01;
		outMat->v02 = outMat->v02 - r.v02;
		outMat->v03 = outMat->v03 - r.v03;
	
		outMat->v10 = outMat->v10 - r.v10;
		outMat->v11 = outMat->v11 - r.v11;
		outMat->v12 = outMat->v12 - r.v12;
		outMat->v13 = outMat->v13 - r.v13;
	
		outMat->v20 = outMat->v20 - r.v20;
		outMat->v21 = outMat->v21 - r.v21;
		outMat->v22 = outMat->v22 - r.v22;
		outMat->v23 = outMat->v23 - r.v23;
	
		outMat->v30 = outMat->v30 - r.v30;
		outMat->v31 = outMat->v31 - r.v31;
		outMat->v32 = outMat->v32 - r.v32;
		outMat->v33 = outMat->v33 - r.v33;
	#endif
}


void    Mat44fMultInplace(const Mat44f& FDK_RESTRICT r, Mat44f* FDK_RESTRICT outMat) {
	//outMat = outMat * r
	Mat44f temp = *outMat;
	
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			__m128 row0;
			__m128 row1;
			__m128 row2;
			__m128 row3;
			__m128 value0;

			// Compute row 0 of the matrix product:
			value0	= _mm_shuffle_ps(temp.mVec128[0], temp.mVec128[0], _MM_SHUFFLE(0, 0, 0, 0));
			row0 	= _mm_mul_ps(r.mVec128[0], value0);

			value0	= _mm_shuffle_ps(temp.mVec128[0], temp.mVec128[0], _MM_SHUFFLE(1, 1, 1, 1));
			row0	= _mm_add_ps(row0, _mm_mul_ps(r.mVec128[1], value0));

			value0	= _mm_shuffle_ps(temp.mVec128[0], temp.mVec128[0], _MM_SHUFFLE(2, 2, 2, 2));
			row0	= _mm_add_ps(row0, _mm_mul_ps(r.mVec128[2], value0));

			value0	= _mm_shuffle_ps(temp.mVec128[0], temp.mVec128[0], _MM_SHUFFLE(3, 3, 3, 3));
			row0	= _mm_add_ps(row0, _mm_mul_ps(r.mVec128[3], value0));

			// Compute row 1 of the matrix product:
			value0	= _mm_shuffle_ps(temp.mVec128[1], temp.mVec128[1], _MM_SHUFFLE(0, 0, 0, 0));
			row1 	= _mm_mul_ps(r.mVec128[0], value0);

			value0	= _mm_shuffle_ps(temp.mVec128[1], temp.mVec128[1], _MM_SHUFFLE(1, 1, 1, 1));
			row1	= _mm_add_ps(row1, _mm_mul_ps(r.mVec128[1], value0));

			value0	= _mm_shuffle_ps(temp.mVec128[1], temp.mVec128[1], _MM_SHUFFLE(2, 2, 2, 2));
			row1	= _mm_add_ps(row1, _mm_mul_ps(r.mVec128[2], value0));

			value0	= _mm_shuffle_ps(temp.mVec128[1], temp.mVec128[1], _MM_SHUFFLE(3, 3, 3, 3));
			row1	= _mm_add_ps(row1, _mm_mul_ps(r.mVec128[3], value0));

			// Compute row 2 of the matrix product:
			value0	= _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[2], _MM_SHUFFLE(0, 0, 0, 0));
			row2	= _mm_mul_ps(r.mVec128[0], value0);

			value0	= _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[2], _MM_SHUFFLE(1, 1, 1, 1));
			row2	= _mm_add_ps(row2, _mm_mul_ps(r.mVec128[1], value0));

			value0	= _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[2], _MM_SHUFFLE(2, 2, 2, 2));
			row2	= _mm_add_ps(row2, _mm_mul_ps(r.mVec128[2], value0));

			value0	= _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[2], _MM_SHUFFLE(3, 3, 3, 3));
			row2	= _mm_add_ps(row2, _mm_mul_ps(r.mVec128[3], value0));

			// Compute row 3 of the matrix product:
			value0	= _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[3], _MM_SHUFFLE(0, 0, 0, 0));
			row3 	= _mm_mul_ps(r.mVec128[0], value0);

			value0	= _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[3], _MM_SHUFFLE(1, 1, 1, 1));
			row3	= _mm_add_ps(row3, _mm_mul_ps(r.mVec128[1], value0));

			value0	= _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[3], _MM_SHUFFLE(2, 2, 2, 2));
			row3	= _mm_add_ps(row3, _mm_mul_ps(r.mVec128[2], value0));

			value0	= _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[3], _MM_SHUFFLE(3, 3, 3, 3));
			row3	= _mm_add_ps(row3, _mm_mul_ps(r.mVec128[3], value0));

			// Write results back to memory:
			outMat->mVec128[0]	= row0;
			outMat->mVec128[1]	= row1;
			outMat->mVec128[2]	= row2;
			outMat->mVec128[3]	= row3;
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//vaddq_f32(v1.mVec128, v2.mVec128);
		#endif
	#else
		outMat->v00 = temp.v00 * r.v00 + temp.v01 * r.v10 + temp.v02 * r.v20 + temp.v03 * r.v30;
		outMat->v01 = temp.v00 * r.v01 + temp.v01 * r.v11 + temp.v02 * r.v21 + temp.v03 * r.v31;
		outMat->v02 = temp.v00 * r.v02 + temp.v01 * r.v12 + temp.v02 * r.v22 + temp.v03 * r.v32;
		outMat->v03 = temp.v00 * r.v03 + temp.v01 * r.v13 + temp.v02 * r.v23 + temp.v03 * r.v33;
	
		outMat->v10 = temp.v10 * r.v00 + temp.v11 * r.v10 + temp.v12 * r.v20 + temp.v13 * r.v30;
		outMat->v11 = temp.v10 * r.v01 + temp.v11 * r.v11 + temp.v12 * r.v21 + temp.v13 * r.v31;
		outMat->v12 = temp.v10 * r.v02 + temp.v11 * r.v12 + temp.v12 * r.v22 + temp.v13 * r.v32;
		outMat->v13 = temp.v10 * r.v03 + temp.v11 * r.v13 + temp.v12 * r.v23 + temp.v13 * r.v33;
	
		outMat->v20 = temp.v20 * r.v00 + temp.v21 * r.v10 + temp.v22 * r.v20 + temp.v23 * r.v30;
		outMat->v21 = temp.v20 * r.v01 + temp.v21 * r.v11 + temp.v22 * r.v21 + temp.v23 * r.v31;
		outMat->v22 = temp.v20 * r.v02 + temp.v21 * r.v12 + temp.v22 * r.v22 + temp.v23 * r.v32;
		outMat->v23 = temp.v20 * r.v03 + temp.v21 * r.v13 + temp.v22 * r.v23 + temp.v23 * r.v33;
	
		outMat->v30 = temp.v30 * r.v00 + temp.v31 * r.v10 + temp.v32 * r.v20 + temp.v33 * r.v30;
		outMat->v31 = temp.v30 * r.v01 + temp.v31 * r.v11 + temp.v32 * r.v21 + temp.v33 * r.v31;
		outMat->v32 = temp.v30 * r.v02 + temp.v31 * r.v12 + temp.v32 * r.v22 + temp.v33 * r.v32;
		outMat->v33 = temp.v30 * r.v03 + temp.v31 * r.v13 + temp.v32 * r.v23 + temp.v33 * r.v33;
	#endif
}

bool 	Mat44fInvertInplace(Mat44f* FDK_RESTRICT outMat) {
	Mat44f temp = *outMat;
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			__m128 Fac0;
			{
				//      valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
				//      valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
				//      valType SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
				//      valType SubFactor13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
			
				__m128 Swp0a = _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[2], _MM_SHUFFLE(3, 3, 3, 3));
				__m128 Swp0b = _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[2], _MM_SHUFFLE(2, 2, 2, 2));
			
				__m128 Swp00 = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[1], _MM_SHUFFLE(2, 2, 2, 2));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[1], _MM_SHUFFLE(3, 3, 3, 3));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac0 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 Fac1;
			{
				//      valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
				//      valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
				//      valType SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
				//      valType SubFactor14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
			
				__m128 Swp0a = _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[2], _MM_SHUFFLE(3, 3, 3, 3));
				__m128 Swp0b = _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[2], _MM_SHUFFLE(1, 1, 1, 1));
			
				__m128 Swp00 = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[1], _MM_SHUFFLE(1, 1, 1, 1));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[1], _MM_SHUFFLE(3, 3, 3, 3));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac1 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
		
			__m128 Fac2;
			{
				//      valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
				//      valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
				//      valType SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
				//      valType SubFactor15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
			
				__m128 Swp0a = _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[2], _MM_SHUFFLE(2, 2, 2, 2));
				__m128 Swp0b = _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[2], _MM_SHUFFLE(1, 1, 1, 1));
			
				__m128 Swp00 = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[1], _MM_SHUFFLE(1, 1, 1, 1));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[1], _MM_SHUFFLE(2, 2, 2, 2));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac2 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 Fac3;
			{
				//      valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
				//      valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
				//      valType SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
				//      valType SubFactor16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
			
				__m128 Swp0a = _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[2], _MM_SHUFFLE(3, 3, 3, 3));
				__m128 Swp0b = _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[2], _MM_SHUFFLE(0, 0, 0, 0));
			
				__m128 Swp00 = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[1], _MM_SHUFFLE(0, 0, 0, 0));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[1], _MM_SHUFFLE(3, 3, 3, 3));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac3 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 Fac4;
			{
				//      valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
				//      valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
				//      valType SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
				//      valType SubFactor17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
			
				__m128 Swp0a = _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[2], _MM_SHUFFLE(2, 2, 2, 2));
				__m128 Swp0b = _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[2], _MM_SHUFFLE(0, 0, 0, 0));
			
				__m128 Swp00 = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[1], _MM_SHUFFLE(0, 0, 0, 0));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[1], _MM_SHUFFLE(2, 2, 2, 2));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac4 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 Fac5;
			{
				//      valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
				//      valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
				//      valType SubFactor12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
				//      valType SubFactor18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];
			
				__m128 Swp0a = _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[2], _MM_SHUFFLE(1, 1, 1, 1));
				__m128 Swp0b = _mm_shuffle_ps(temp.mVec128[3], temp.mVec128[2], _MM_SHUFFLE(0, 0, 0, 0));
			
				__m128 Swp00 = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[1], _MM_SHUFFLE(0, 0, 0, 0));
				__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
				__m128 Swp03 = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[1], _MM_SHUFFLE(1, 1, 1, 1));
			
				__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
				__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
				Fac5 = _mm_sub_ps(Mul00, Mul01);
			
			}
		
			__m128 SignA = _mm_set_ps( 1.0f,-1.0f, 1.0f,-1.0f);
			__m128 SignB = _mm_set_ps(-1.0f, 1.0f,-1.0f, 1.0f);
		
			// m[1][0]
			// m[0][0]
			// m[0][0]
			// m[0][0]
			__m128 Temp0 = _mm_shuffle_ps(temp.mVec128[1], temp.mVec128[0], _MM_SHUFFLE(0, 0, 0, 0));
			__m128 Vec0 = _mm_shuffle_ps(Temp0, Temp0, _MM_SHUFFLE(2, 2, 2, 0));
		
			// m[1][1]
			// m[0][1]
			// m[0][1]
			// m[0][1]
			__m128 Temp1 = _mm_shuffle_ps(temp.mVec128[1], temp.mVec128[0], _MM_SHUFFLE(1, 1, 1, 1));
			__m128 Vec1 = _mm_shuffle_ps(Temp1, Temp1, _MM_SHUFFLE(2, 2, 2, 0));
		
			// m[1][2]
			// m[0][2]
			// m[0][2]
			// m[0][2]
			__m128 Temp2 = _mm_shuffle_ps(temp.mVec128[1], temp.mVec128[0], _MM_SHUFFLE(2, 2, 2, 2));
			__m128 Vec2 = _mm_shuffle_ps(Temp2, Temp2, _MM_SHUFFLE(2, 2, 2, 0));
		
			// m[1][3]
			// m[0][3]
			// m[0][3]
			// m[0][3]
			__m128 Temp3 = _mm_shuffle_ps(temp.mVec128[1], temp.mVec128[0], _MM_SHUFFLE(3, 3, 3, 3));
			__m128 Vec3 = _mm_shuffle_ps(Temp3, Temp3, _MM_SHUFFLE(2, 2, 2, 0));
		
			// col0
			// + (Vec1[0] * Fac0[0] - Vec2[0] * Fac1[0] + Vec3[0] * Fac2[0]),
			// - (Vec1[1] * Fac0[1] - Vec2[1] * Fac1[1] + Vec3[1] * Fac2[1]),
			// + (Vec1[2] * Fac0[2] - Vec2[2] * Fac1[2] + Vec3[2] * Fac2[2]),
			// - (Vec1[3] * Fac0[3] - Vec2[3] * Fac1[3] + Vec3[3] * Fac2[3]),
			__m128 Mul00 = _mm_mul_ps(Vec1, Fac0);
			__m128 Mul01 = _mm_mul_ps(Vec2, Fac1);
			__m128 Mul02 = _mm_mul_ps(Vec3, Fac2);
			__m128 Sub00 = _mm_sub_ps(Mul00, Mul01);
			__m128 Add00 = _mm_add_ps(Sub00, Mul02);
			__m128 Inv0 = _mm_mul_ps(SignB, Add00);
		
			// col1
			// - (Vec0[0] * Fac0[0] - Vec2[0] * Fac3[0] + Vec3[0] * Fac4[0]),
			// + (Vec0[0] * Fac0[1] - Vec2[1] * Fac3[1] + Vec3[1] * Fac4[1]),
			// - (Vec0[0] * Fac0[2] - Vec2[2] * Fac3[2] + Vec3[2] * Fac4[2]),
			// + (Vec0[0] * Fac0[3] - Vec2[3] * Fac3[3] + Vec3[3] * Fac4[3]),
			__m128 Mul03 = _mm_mul_ps(Vec0, Fac0);
			__m128 Mul04 = _mm_mul_ps(Vec2, Fac3);
			__m128 Mul05 = _mm_mul_ps(Vec3, Fac4);
			__m128 Sub01 = _mm_sub_ps(Mul03, Mul04);
			__m128 Add01 = _mm_add_ps(Sub01, Mul05);
			__m128 Inv1 = _mm_mul_ps(SignA, Add01);
		
			// col2
			// + (Vec0[0] * Fac1[0] - Vec1[0] * Fac3[0] + Vec3[0] * Fac5[0]),
			// - (Vec0[0] * Fac1[1] - Vec1[1] * Fac3[1] + Vec3[1] * Fac5[1]),
			// + (Vec0[0] * Fac1[2] - Vec1[2] * Fac3[2] + Vec3[2] * Fac5[2]),
			// - (Vec0[0] * Fac1[3] - Vec1[3] * Fac3[3] + Vec3[3] * Fac5[3]),
			__m128 Mul06 = _mm_mul_ps(Vec0, Fac1);
			__m128 Mul07 = _mm_mul_ps(Vec1, Fac3);
			__m128 Mul08 = _mm_mul_ps(Vec3, Fac5);
			__m128 Sub02 = _mm_sub_ps(Mul06, Mul07);
			__m128 Add02 = _mm_add_ps(Sub02, Mul08);
			__m128 Inv2 = _mm_mul_ps(SignB, Add02);
		
			// col3
			// - (Vec1[0] * Fac2[0] - Vec1[0] * Fac4[0] + Vec2[0] * Fac5[0]),
			// + (Vec1[0] * Fac2[1] - Vec1[1] * Fac4[1] + Vec2[1] * Fac5[1]),
			// - (Vec1[0] * Fac2[2] - Vec1[2] * Fac4[2] + Vec2[2] * Fac5[2]),
			// + (Vec1[0] * Fac2[3] - Vec1[3] * Fac4[3] + Vec2[3] * Fac5[3]));
			__m128 Mul09 = _mm_mul_ps(Vec0, Fac2);
			__m128 Mul10 = _mm_mul_ps(Vec1, Fac4);
			__m128 Mul11 = _mm_mul_ps(Vec2, Fac5);
			__m128 Sub03 = _mm_sub_ps(Mul09, Mul10);
			__m128 Add03 = _mm_add_ps(Sub03, Mul11);
			__m128 Inv3 = _mm_mul_ps(SignA, Add03);
		
			__m128 Row0 = _mm_shuffle_ps(Inv0, Inv1, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 Row1 = _mm_shuffle_ps(Inv2, Inv3, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 Row2 = _mm_shuffle_ps(Row0, Row1, _MM_SHUFFLE(2, 0, 2, 0));
		
			//      valType DeterminMat44f.mVec128ant = m[0][0] * inMat44f.mVec128verse[0][0]
			//                                              + m[0][1] * inMat44f.mVec128verse[1][0]
			//                                              + m[0][2] * inMat44f.mVec128verse[2][0]
			//                                              + m[0][3] * inMat44f.mVec128verse[3][0];
			#if defined (__SSE4_1__)
				__m128 Det0 = _mm_dp_ps(temp.mVec128[0], Row2, 0xff);
			#elif defined (_M_IX86_FP )
				__m128 Det0 = _mm_dp_ps(temp.mVec128[0], Row2, 0xff);
			#else
				__m128 mul0 = _mm_mul_ps(temp.mVec128[0], Row2);
				__m128 swp0 = _mm_shuffle_ps(mul0, mul0, _MM_SHUFFLE(2, 3, 0, 1));
				__m128 add0 = _mm_add_ps(mul0, swp0);
				__m128 swp1 = _mm_shuffle_ps(add0, add0, _MM_SHUFFLE(0, 1, 2, 3));
				__m128 Det0 = _mm_add_ps(add0, swp1);	
			#endif

			__m128 one = _mm_set_ps( 1.0,1.0f, 1.0f,1.0f); //Enea to do: verify one...
			__m128 Rcp0 = _mm_div_ps(one, Det0);
			//__m128 Rcp0 = _mm_rcp_ps(Det0);
		
			//      inMat44f.mVec128verse /= DeterminMat44f.mVec128ant;
			outMat->mVec128[0] = _mm_mul_ps(Inv0, Rcp0);
			outMat->mVec128[1] = _mm_mul_ps(Inv1, Rcp0);
			outMat->mVec128[2] = _mm_mul_ps(Inv2, Rcp0);
			outMat->mVec128[3] = _mm_mul_ps(Inv3, Rcp0);
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
		#endif
	#else
		//determinant matrix 4x4
		F32 determinant = Mat44fDeterminant(*outMat);
	
		//Determinant must be different from zero, else matrix can't be inverted.
		if (determinant == 0)
			return false;

		F32 rhDet   = (1.f/determinant);
		//Invert
	
		outMat->v00 = rhDet * (temp.v11 * temp.v22 * temp.v33 + temp.v12 * temp.v23 * temp.v31 + temp.v13 * temp.v21 * temp.v32 - temp.v11 * temp.v23 * temp.v32 - temp.v12 * temp.v21 * temp.v33 - temp.v13 * temp.v22 * temp.v31);
	
		outMat->v01 = rhDet * (temp.v01 * temp.v23 * temp.v32 + temp.v02 * temp.v21 * temp.v33 + temp.v03 * temp.v22 * temp.v31 - temp.v01 * temp.v22 * temp.v33 - temp.v02 * temp.v23 * temp.v31 - temp.v03 * temp.v21 * temp.v32);
	
		outMat->v02 = rhDet * (temp.v01 * temp.v12 * temp.v33 + temp.v02 * temp.v13 * temp.v31 + temp.v03 * temp.v11 * temp.v32 - temp.v01 * temp.v13 * temp.v32 - temp.v02 * temp.v11 * temp.v33 - temp.v03 * temp.v12 * temp.v31);
	
		outMat->v03 = rhDet * (temp.v01 * temp.v13 * temp.v22 + temp.v02 * temp.v11 * temp.v23 + temp.v03 * temp.v12 * temp.v21 - temp.v01 * temp.v12 * temp.v23 - temp.v02 * temp.v13 * temp.v21 - temp.v03 * temp.v11 * temp.v22);
	
		outMat->v10 = rhDet * (temp.v10 * temp.v23 * temp.v32 + temp.v12 * temp.v20 * temp.v33 + temp.v13 * temp.v22 * temp.v30 - temp.v10 * temp.v22 * temp.v33 - temp.v12 * temp.v23 * temp.v30 - temp.v13 * temp.v20 * temp.v32);
	
		outMat->v11 = rhDet * (temp.v00 * temp.v22 * temp.v33 + temp.v02 * temp.v23 * temp.v30 + temp.v03 * temp.v20 * temp.v32 - temp.v00 * temp.v23 * temp.v32 - temp.v02 * temp.v20 * temp.v33 - temp.v03 * temp.v22 * temp.v30);
	
		outMat->v12 = rhDet * (temp.v00 * temp.v13 * temp.v32 + temp.v02 * temp.v10 * temp.v33 + temp.v03 * temp.v12 * temp.v30 - temp.v00 * temp.v12 * temp.v33 - temp.v02 * temp.v13 * temp.v30 - temp.v03 * temp.v10 * temp.v32);
	
		outMat->v13 = rhDet * (temp.v00 * temp.v12 * temp.v23 + temp.v02 * temp.v13 * temp.v20 + temp.v03 * temp.v10 * temp.v22 - temp.v00 * temp.v13 * temp.v22 - temp.v02 * temp.v10 * temp.v23 - temp.v03 * temp.v12 * temp.v20);
	
		outMat->v20 = rhDet * (temp.v10 * temp.v21 * temp.v33 + temp.v11 * temp.v23 * temp.v30 + temp.v13 * temp.v20 * temp.v31 - temp.v10 * temp.v23 * temp.v31 - temp.v11 * temp.v20 * temp.v33 - temp.v13 * temp.v21 * temp.v30);
	
		outMat->v21 = rhDet * (temp.v00 * temp.v23 * temp.v31 + temp.v01 * temp.v20 * temp.v33 + temp.v03 * temp.v21 * temp.v30 - temp.v00 * temp.v21 * temp.v33 - temp.v01 * temp.v23 * temp.v30 - temp.v03 * temp.v20 * temp.v31);
	
		outMat->v22 = rhDet * (temp.v00 * temp.v11 * temp.v33 + temp.v01 * temp.v13 * temp.v30 + temp.v03 * temp.v10 * temp.v31 - temp.v00 * temp.v13 * temp.v31 - temp.v01 * temp.v10 * temp.v33 - temp.v03 * temp.v11 * temp.v30);
	
		outMat->v23 = rhDet * (temp.v00 * temp.v13 * temp.v21 + temp.v01 * temp.v10 * temp.v23 + temp.v03 * temp.v11 * temp.v20 - temp.v00 * temp.v11 * temp.v23 - temp.v01 * temp.v13 * temp.v20 - temp.v03 * temp.v10 * temp.v21);
	
		outMat->v30 = rhDet * (temp.v10 * temp.v22 * temp.v31 + temp.v11 * temp.v20 * temp.v32 + temp.v12 * temp.v21 * temp.v30 - temp.v10 * temp.v21 * temp.v32 - temp.v11 * temp.v22 * temp.v30 - temp.v12 * temp.v20 * temp.v31);
	
		outMat->v31 = rhDet * (temp.v00 * temp.v21 * temp.v32 + temp.v01 * temp.v22 * temp.v30 + temp.v02 * temp.v20 * temp.v31 - temp.v00 * temp.v22 * temp.v31 - temp.v01 * temp.v20 * temp.v32 - temp.v02 * temp.v21 * temp.v30);
	
		outMat->v32 = rhDet * (temp.v00 * temp.v12 * temp.v31 + temp.v01 * temp.v10 * temp.v32 + temp.v02 * temp.v11 * temp.v30 - temp.v00 * temp.v11 * temp.v32 - temp.v01 * temp.v12 * temp.v30 - temp.v02 * temp.v10 * temp.v31);
	
		outMat->v33 = rhDet * (temp.v00 * temp.v11 * temp.v22 + temp.v01 * temp.v12 * temp.v20 + temp.v02 * temp.v10 * temp.v21 - temp.v00 * temp.v12 * temp.v21 - temp.v01 * temp.v10 * temp.v22 - temp.v02 * temp.v11 * temp.v20);
	#endif
	
	return true;
}

void 	Mat44fTransposeInplace(Mat44f* FDK_RESTRICT outMat) {
	//transpose the matrix 3x3
	Mat44f temp = Mat44f( outMat->v00, outMat->v01, outMat->v02, outMat->v03, outMat->v10, outMat->v11, outMat->v12, outMat->v13, outMat->v20, outMat->v21, outMat->v22, outMat->v23, outMat->v30, outMat->v31, outMat->v32, outMat->v33);
	
	//transpose the matrix 4x4
	#if defined (FDK_USE_SIMD)
		#if defined(FDK_USE_SSE)// && defined (FDK_USE_SSE_IN_API) && (FDK_OS_OSX)
			__m128 tmp3, tmp2, tmp1, tmp0; 
			tmp0   = _mm_shuffle_ps(temp.mVec128[0], temp.mVec128[1], 0x44);          
            tmp2   = _mm_shuffle_ps(temp.mVec128[0], temp.mVec128[1], 0xEE);          
            tmp1   = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[3], 0x44);          
            tmp3   = _mm_shuffle_ps(temp.mVec128[2], temp.mVec128[3], 0xEE);          
                                                                    
            outMat->mVec128[0] = _mm_shuffle_ps(tmp0, tmp1, 0x88);              
            outMat->mVec128[1] = _mm_shuffle_ps(tmp0, tmp1, 0xDD);              
            outMat->mVec128[2] = _mm_shuffle_ps(tmp2, tmp3, 0x88);              
            outMat->mVec128[3] = _mm_shuffle_ps(tmp2, tmp3, 0xDD); 
		#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
			//to do
			//outVec->mVec128 = vaddq_f32(l.mVec128, r.mVec128);
		#endif
	#else
		outMat->v00 = temp.v00;
		outMat->v01 = temp.v10;
		outMat->v02 = temp.v20;
		outMat->v03 = temp.v30;
	
		outMat->v10 = temp.v01;
		outMat->v11 = temp.v11;
		outMat->v12 = temp.v21;
		outMat->v13 = temp.v31;
	
		outMat->v20 = temp.v02;
		outMat->v21 = temp.v12;
		outMat->v22 = temp.v22;
		outMat->v23 = temp.v32;
	
		outMat->v30 = temp.v03;
		outMat->v31 = temp.v13;
		outMat->v32 = temp.v23;
		outMat->v33 = temp.v33;
	#endif
}

FDK_NS_END