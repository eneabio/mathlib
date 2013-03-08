// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_COMPLEXH_H__
#define __FDK_COMPLEXH_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"
#include "fdk/mathf.h"
#include "fdk/complexf.h"

FDK_NS_BEGIN

struct Complexh {
	
	Complexh(F16 _real,F16 _img) : real(_real),img(_img) {}
	Complexh() {}
	
	operator const F16*() const { return (const F16*)(void*)this; }
	operator F16* () const { return (F16*)(void*)this; }
	
	F16& operator()(int index) {
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 2);
		return ((F16*)this)[index];
	}
	const F16& operator()(int index) const {
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 2);
		return ((F16*)this)[index];
	}
	
	F16 real;
	F16 img;
	
};

FDK_FORGE_API   void   ComplexhInit         (Complexh* outComplex);
FDK_FORGE_API   void   ComplexhConj         (const Complexh& FDK_RESTRICT  inComplex, Complexh* FDK_RESTRICT outComplex);
FDK_FORGE_API   F16    ComplexhAbs          (const Complexh& FDK_RESTRICT  inComplex);
FDK_FORGE_API   F16    ComplexhNorm         (const Complexh& FDK_RESTRICT  inComplex);
FDK_FORGE_API   F16    ComplexhArg          (const Complexh& FDK_RESTRICT  inComplex);
FDK_FORGE_API   F16    ComplexhImag         (const Complexh& FDK_RESTRICT  inComplex);
FDK_FORGE_API   F16    ComplexhReal         (const Complexh& FDK_RESTRICT  inComplex);
FDK_FORGE_API   void   ComplexhSum          (const Complexh& FDK_RESTRICT  l, const Complexh& FDK_RESTRICT r, Complexh* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexhSub          (const Complexh& FDK_RESTRICT  l, const Complexh& FDK_RESTRICT r, Complexh* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexhMult         (const Complexh& FDK_RESTRICT  l, const Complexh& FDK_RESTRICT r, Complexh* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexhMultScalar   (const Complexh& FDK_RESTRICT  inComplex, const F16 scalar, Complexh* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexhDiv          (const Complexh& FDK_RESTRICT  num, const Complexh& FDK_RESTRICT den, Complexh* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexhFromPolar    (const F16 radius, const F16 angle, Complexh*  outComplex);

FDK_FORGE_API   void   ComplexhToComplexf   (const Complexh& FDK_RESTRICT  inComplexh, Complexf* FDK_RESTRICT outComplexf);
FDK_FORGE_API   void   ComplexfToComplexh   (const Complexf& FDK_RESTRICT  inComplexf, Complexh* FDK_RESTRICT outComplexh);

//Inplace

FDK_NS_END

#endif
