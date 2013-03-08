// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_COMPLEXF_H__
#define __FDK_COMPLEXF_H__

#include "fdk/base_defs.h"
#include "fdk/forge_defs.h"

FDK_NS_BEGIN

struct Complexf {
	
	Complexf(F32 _real,F32 _img) : real(_real),img(_img) {}
	Complexf() {}
	
	operator const F32*() const { return (const F32*)(void*)this; }
	operator F32* () const { return (F32*)(void*)this; }
	
	F32& operator()(int index) {
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 2);
		return ((F32*)this)[index];
	}
	const F32& operator()(int index) const {
		FDK_ASSERT(index >= 0);
		FDK_ASSERT(index < 2);
		return ((F32*)this)[index];
	}

	F32 real;
	F32 img;

};

FDK_FORGE_API   void   ComplexfInit         (Complexf* outComplex);
FDK_FORGE_API   void   ComplexfConj         (const Complexf& FDK_RESTRICT  inComplex, Complexf* FDK_RESTRICT outComplex);
FDK_FORGE_API   F32    ComplexfAbs          (const Complexf& FDK_RESTRICT  inComplex);
FDK_FORGE_API   F32    ComplexfNorm         (const Complexf& FDK_RESTRICT  inComplex);
FDK_FORGE_API   F32    ComplexfArg          (const Complexf& FDK_RESTRICT  inComplex);
FDK_FORGE_API   F32    ComplexfImag         (const Complexf& FDK_RESTRICT  inComplex);
FDK_FORGE_API   F32    ComplexfReal         (const Complexf& FDK_RESTRICT  inComplex);
FDK_FORGE_API   void   ComplexfSum          (const Complexf& FDK_RESTRICT  l, const Complexf& FDK_RESTRICT r, Complexf* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexfSub          (const Complexf& FDK_RESTRICT  l, const Complexf& FDK_RESTRICT r, Complexf* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexfMult         (const Complexf& FDK_RESTRICT  l, const Complexf& FDK_RESTRICT r, Complexf* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexfMultScalar   (const Complexf& FDK_RESTRICT  inComplex, const F32 scalar, Complexf* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexfDiv          (const Complexf& FDK_RESTRICT  num, const Complexf& FDK_RESTRICT den, Complexf* FDK_RESTRICT outComplex);
FDK_FORGE_API   void   ComplexfFromPolar    (const F32 radius, const F32 angle, Complexf*  outComplex);

//Inplace

FDK_NS_END

#endif
