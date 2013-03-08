// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/complexh.h"
#include "fdk/mathf.h"

FDK_NS_BEGIN

void   ComplexhInit   (Complexh* outComplex) {
	outComplex->real = 0;
	outComplex->img  = 0;
}

void   ComplexhConj   (const Complexh&   inComplex, Complexh*  outComplex) {
	Complexf inComplexF;
	ComplexhToComplexf(inComplex, &inComplexF);
	Complexf outComplexF;
	ComplexfConj(inComplexF, &outComplexF);
	ComplexfToComplexh(outComplexF, outComplex);
}

F16    ComplexhAbs    (const Complexh&   inComplex) {
	Complexf inComplexF;
	ComplexhToComplexf(inComplex, &inComplexF);
	F32 absF = ComplexfAbs(inComplexF);
	F16 absH = toFloat16(absF);
	return absH;
}

F16    ComplexhNorm   (const Complexh&   inComplex) {
	Complexf inComplexF;
	ComplexhToComplexf(inComplex, &inComplexF);
	F32 zF = ComplexfNorm(inComplexF);
	F16 zH = toFloat16(zF);
	return zH;
}

F16    ComplexhArg    (const Complexh&   inComplex) {
	return ArcTan2h(inComplex.img, inComplex.real);
}

F16   ComplexhImag   (const Complexh&   inComplex) {
	return inComplex.img;
}

F16   ComplexhReal   (const Complexh&   inComplex) {
	return inComplex.real;
}

void   ComplexhSum    (const Complexh&   l, const Complexh&  r, Complexh*  outComplex) {
	Complexf lF;
	ComplexhToComplexf(l, &lF);
	Complexf rF;
	ComplexhToComplexf(r, &rF);
	Complexf outComplexF;
	ComplexfSum(lF, rF, &outComplexF);
	ComplexfToComplexh(outComplexF, outComplex);
}

void   ComplexhSub    (const Complexh&   l, const Complexh&  r, Complexh*  outComplex) {
	Complexf lF;
	ComplexhToComplexf(l, &lF);
	Complexf rF;
	ComplexhToComplexf(r, &rF);
	Complexf outComplexF;
	ComplexfSub(lF, rF, &outComplexF);
	ComplexfToComplexh(outComplexF, outComplex);
}

void   ComplexhMult    (const Complexh&   l, const Complexh&  r, Complexh*  outComplex) {
	Complexf lF;
	ComplexhToComplexf(l, &lF);
	Complexf rF;
	ComplexhToComplexf(r, &rF);
	Complexf outComplexF;
	ComplexfMult(lF, rF, &outComplexF);
	ComplexfToComplexh(outComplexF, outComplex);
}

void   ComplexhMultScalar   (const Complexh&   inComplex, const F16 scalar, Complexh*  outComplex) {
	Complexf incomplexF;
	ComplexhToComplexf(inComplex, &incomplexF);
	F32 scalarF = toFloat32(scalar);
	Complexf outComplexF;
	ComplexfMultScalar(incomplexF, scalarF, &outComplexF);
	ComplexfToComplexh(outComplexF, outComplex);
	
}

void   ComplexhDiv    (const Complexh&   num, const Complexh&  den, Complexh*  outComplex) {
	Complexf numF;
	ComplexhToComplexf(num, &numF);
	Complexf denF;
	ComplexhToComplexf(den, &denF);
	Complexf outComplexF;
	ComplexfDiv(numF, denF, &outComplexF);
	ComplexfToComplexh(outComplexF, outComplex);
}

void   ComplexhFromPolar    (const F16 radius, const F16 angle, Complexh*  outComplex) {
	F32 radiusF = toFloat32(radius);
	F32 angleF  = toFloat32(angle);
	Complexf outComplexF;
	ComplexfFromPolar(radiusF, angleF, &outComplexF);
	ComplexfToComplexh(outComplexF, outComplex);
}

void   ComplexhToComplexf        (const Complexh&  inComplexh, Complexf* outComplexf) {
	outComplexf->real = toFloat32(inComplexh.real);
	outComplexf->img  = toFloat32(inComplexh.img);
}

void   ComplexfToComplexh        (const Complexf&  inComplexf, Complexh* outComplexh) {
	outComplexh->real = toFloat16(inComplexf.real);
	outComplexh->img  = toFloat16(inComplexf.img);
}

FDK_NS_END

