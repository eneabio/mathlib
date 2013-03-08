// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/complexf.h"
#include "fdk/mathf.h"

FDK_NS_BEGIN

void   ComplexfInit   (Complexf* outComplex) {
	outComplex->real = 0.f;
	outComplex->img  = 0.f;
}

void   ComplexfConj   (const Complexf&   inComplex, Complexf*  outComplex) {
	outComplex->real =   inComplex.real;
	outComplex->img  = - inComplex.img;
}

F32    ComplexfAbs    (const Complexf&   inComplex) {
	F32 z;
	z = (inComplex.real * inComplex.real) + (inComplex.img * inComplex.img);
	return Sqrtf(z);
}

F32    ComplexfNorm   (const Complexf&   inComplex) {
	F32 z;
	z = (inComplex.real * inComplex.real) + (inComplex.img * inComplex.img);
	return z;
}

F32    ComplexfArg    (const Complexf&   inComplex) {
	return ArcTan2f(inComplex.img, inComplex.real);
}

F32   ComplexfImag   (const Complexf&   inComplex) {
	return inComplex.img;
}

F32   ComplexfReal   (const Complexf&   inComplex) {
	return inComplex.real;
}

void   ComplexfSum    (const Complexf&   l, const Complexf&  r, Complexf*  outComplex) {
	outComplex->real = l.real + r.real;
	outComplex->img  = l.img  + r.img;
}

void   ComplexfSub    (const Complexf&   l, const Complexf&  r, Complexf*  outComplex) {
	outComplex->real = l.real - r.real;
	outComplex->img  = l.img  - r.img;
}

void   ComplexfMult    (const Complexf&   l, const Complexf&  r, Complexf*  outComplex) {
	outComplex->real = l.real * r.real  - l.img  * r.img;
	outComplex->img  = l.img  * r.real  + l.real * r.img;
}

void   ComplexfMultScalar   (const Complexf&   inComplex, const F32 scalar, Complexf*  outComplex) {
	outComplex->real = scalar * inComplex.real;
	outComplex->img  = scalar * inComplex.img;
}

void   ComplexfDiv    (const Complexf&   num, const Complexf&  den, Complexf*  outComplex) {
	F32  denF = ComplexfNorm(den);
	FDK_ASSERT(denF > 0);
	outComplex->real = (num.real * den.real + num.img  * den.img)/denF;
	outComplex->img  = (num.img  * den.real - num.real * den.img)/denF;
}

void   ComplexfFromPolar    (const F32 radius, const F32 angle, Complexf*  outComplex) {
	outComplex->real = radius  * Cosf(angle);
	outComplex->img  = radius  * Sinf(angle);
}

FDK_NS_END

