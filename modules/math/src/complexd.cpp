// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/complexd.h"
#include "fdk/mathd.h"

FDK_NS_BEGIN

void   ComplexdInit   (Complexd* outComplex) {
	outComplex->real = 0.f;
	outComplex->img  = 0.f;
}

void   ComplexdConj   (const Complexd&   inComplex, Complexd*  outComplex) {
	outComplex->real =   inComplex.real;
	outComplex->img  = - inComplex.img;
}

F64    ComplexdAbs    (const Complexd&   inComplex) {
	F64 z;
	z = (inComplex.real * inComplex.real) + (inComplex.img * inComplex.img);
	return Sqrtd(z);
}

F64    ComplexdNorm   (const Complexd&   inComplex) {
	F64 z;
	z = (inComplex.real * inComplex.real) + (inComplex.img * inComplex.img);
	return z;
}

F64    ComplexdArg    (const Complexd&   inComplex) {
	return ArcTan2d(inComplex.img, inComplex.real);
}

F64   ComplexdImag   (const Complexd&   inComplex) {
	return inComplex.img;
}

F64   ComplexdReal   (const Complexd&   inComplex) {
	return inComplex.real;
}

void   ComplexdSum    (const Complexd&   l, const Complexd&  r, Complexd*  outComplex) {
	outComplex->real = l.real + r.real;
	outComplex->img  = l.img  + r.img;
}

void   ComplexdSub    (const Complexd&   l, const Complexd&  r, Complexd*  outComplex) {
	outComplex->real = l.real - r.real;
	outComplex->img  = l.img  - r.img;
}

void   ComplexdMult    (const Complexd&   l, const Complexd&  r, Complexd*  outComplex) {
	outComplex->real = l.real * r.real  - l.img  * r.img;
	outComplex->img  = l.img  * r.real  + l.real * r.img;
}

void   ComplexdMultScalar   (const Complexd&   inComplex, const F64 scalar, Complexd*  outComplex) {
	outComplex->real = scalar * inComplex.real;
	outComplex->img  = scalar * inComplex.img;
}

void   ComplexdDiv    (const Complexd&   num, const Complexd&  den, Complexd*  outComplex) {
	F64  denF = ComplexdNorm(den);
	FDK_ASSERT(denF > 0);
	outComplex->real = (num.real * den.real + num.img  * den.img)/denF;
	outComplex->img  = (num.img  * den.real - num.real * den.img)/denF;
}

void   ComplexdFromPolar    (const F64 radius, const F64 angle, Complexd*  outComplex) {
	outComplex->real = radius  * Cosd(angle);
	outComplex->img  = radius  * Sind(angle);
}

FDK_NS_END

