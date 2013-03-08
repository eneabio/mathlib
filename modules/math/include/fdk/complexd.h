// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_FORGE_COMPLEXD_H__
#define __FDK_FORGE_COMPLEXD_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"

FDK_NS_BEGIN

struct Complexd {
	
	Complexd(F64 _real,F64 _img) : real(_real),img(_img) {}
	Complexd() {}
	
	operator const F64*() const { return (const F64*)(void*)this; }
	operator F64* () const { return (F64*)(void*)this; }
	
	F64& operator()(int index) {
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 2);
		return ((F64*)this)[index];
	}
	const F64& operator()(int index) const {
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 2);
		return ((F64*)this)[index];
	}
	
	F64 real;
	F64 img;
	
};

FDK_FORGE_API   void   ComplexdInit         (Complexd* outComplex);
FDK_FORGE_API   void   ComplexdConj         (const Complexd& FDK_RESTRICT  inComplex, Complexd* FDK_RESTRICT outComplex);
FDK_FORGE_API   F64    ComplexdAbs          (const Complexd& FDK_RESTRICT  inComplex);
FDK_FORGE_API   F64    ComplexdNorm         (const Complexd& FDK_RESTRICT  inComplex);
FDK_FORGE_API   F64    ComplexdArg          (const Complexd& FDK_RESTRICT  inComplex);
FDK_FORGE_API   F64    ComplexdImag         (const Complexd& FDK_RESTRICT  inComplex);
FDK_FORGE_API   F64    ComplexdReal         (const Complexd& FDK_RESTRICT  inComplex);
FDK_FORGE_API   void   ComplexdSum          (const Complexd& FDK_RESTRICT  l, const Complexd& FDK_RESTRICT r, Complexd* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexdSub          (const Complexd& FDK_RESTRICT  l, const Complexd& FDK_RESTRICT r, Complexd* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexdMult         (const Complexd& FDK_RESTRICT  l, const Complexd& FDK_RESTRICT r, Complexd* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexdMultScalar   (const Complexd& FDK_RESTRICT  inComplex, const F64 scalar, Complexd* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexdDiv          (const Complexd& FDK_RESTRICT  num, const Complexd& FDK_RESTRICT den, Complexd* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexdFromPolar    (const F64 radius, const F64 angle, Complexd*  outComplex);

//Inplace

FDK_NS_END

#endif

