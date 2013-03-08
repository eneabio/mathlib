// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/quath.h"
#include "fdk/quatf.h"
#include "fdk/mathf.h"
#include "fdk/vec3h.h"

FDK_NS_BEGIN

void QuathInit(Quath* outQuat) {
	outQuat->qX = 0;
	outQuat->qY = 0;
	outQuat->qZ = 0;
	outQuat->qW = 0;
}

void QuathInitWithValues(F16 x, F16 y, F16 z, F16 w, Quath* outQuat) {
	outQuat->qX = x;
	outQuat->qY = y;
	outQuat->qZ = z;
	outQuat->qW = w;
	
	F16 lengthH = QuathModulus(*outQuat);
	
	//to do with toll
	F32 lengthF = toFloat32(lengthH);
	bool res = FdkEqf32(lengthF, 1.f, FDK_F16_TOLL);
	FDK_ASSERT(res);
	
}

void   QuathIdentity(Quath* outQuat){
	F16 one = toFloat16(1.f);
	outQuat->qX = 0;
	outQuat->qY = 0;
	outQuat->qZ = 0;
	outQuat->qW = one;
}

void   QuathInitWithEulerAngles(F16 yaw, F16 roll, F16 pitch, Quath* outQuat) {
	F32 yawF = toFloat32(yaw);
	F32 rollF = toFloat32(roll);
	F32 pitchF = toFloat32(pitch);
	Quatf outQuatf;
	QuatfInitWithEulerAngles(yawF, rollF, pitchF, &outQuatf);
	QuatfToQuath(outQuatf, outQuat);
}

F16 QuathModulus (const Quath& inQuath) {
	Quatf inQuatf;
	QuathToQuatf(inQuath, &inQuatf);
	F32 modulusF = QuatfModulus(inQuatf);
	F16 modulusH = toFloat16(modulusF);
	return modulusH;
}

F16    QuathSquaredModulus      (const Quath& FDK_RESTRICT inQuath) {
	Quatf inQuatf;
	QuathToQuatf(inQuath, &inQuatf);
	F32 squaredMF = QuatfSquaredModulus(inQuatf);
	F16 squaredMH = toFloat16(squaredMF);
	return squaredMH;
}

void   QuathNormalize(const Quath&  inQuath, Quath* outQuath) {
	Quatf inQuatf;
	QuathToQuatf(inQuath, &inQuatf);
	Quatf outQuatf;
	QuatfNormalize(inQuatf, &outQuatf);
	QuatfToQuath(outQuatf, outQuath);
}

void  QuathConjugate(const Quath&  inQuath, Quath* outQuath) {
	Quatf inQuatf;
	QuathToQuatf(inQuath, &inQuatf);
	Quatf outQuatf;
	QuatfConjugate(inQuatf, &outQuatf);
	QuatfToQuath(outQuatf, outQuath);
}

void   QuathInverse(const Quath&  inQuath, Quath* outQuath) {
	Quatf inQuatf;
	QuathToQuatf(inQuath, &inQuatf);
	Quatf outQuatf;
	QuatfInverse(inQuatf, &outQuatf);
	QuatfToQuath(outQuatf, outQuath);
}

F16     QuathDot(const Quath& l, const Quath& r) {
	Quatf lf;
	QuathToQuatf(l, &lf);
	Quatf rf;
	QuathToQuatf(r, &rf);
	F32 resF = QuatfDot(lf, rf);
	F16 resH = toFloat16(resF);
	return resH;
}

void    QuathMultScalar(const Quath& inQuath, const F16 scalar, Quath* outQuath) {
	Quatf inQuatf;
	QuathToQuatf(inQuath, &inQuatf);
	F32 scalarF = toFloat32(scalar);
	Quatf outQuatf;
	QuatfMultScalar(inQuatf, scalarF, &outQuatf);
	QuatfToQuath(outQuatf, outQuath);
}


void    QuathMult(const Quath& l, const Quath& r, Quath* outQuath) {
	Quatf lf;
	QuathToQuatf(l, &lf);
	Quatf rf;
	QuathToQuatf(r, &rf);
	Quatf outQuatf;
	QuatfMult(lf, rf, &outQuatf);
	QuatfToQuath(outQuatf, outQuath);
}

void    QuathSum(const Quath& l, const Quath& r, Quath* outQuath) {
	Quatf lf;
	QuathToQuatf(l, &lf);
	Quatf rf;
	QuathToQuatf(r, &rf);
	Quatf outQuatf;
	QuatfSum(lf, rf, &outQuatf);
	QuatfToQuath(outQuatf, outQuath);
}

void    QuathSub(const Quath& l, const Quath& r, Quath* outQuath) {
	Quatf lf;
	QuathToQuatf(l, &lf);
	Quatf rf;
	QuathToQuatf(r, &rf);
	Quatf outQuatf;
	QuatfSub(lf, rf, &outQuatf);
	QuatfToQuath(outQuatf, outQuath);
}

void    QuathAbs(const Quath&  inQuath, Quath* outQuath) {
	outQuath->qX = Absh(inQuath.qX);
	outQuath->qY = Absh(inQuath.qY);
	outQuath->qZ = Absh(inQuath.qZ);
	outQuath->qW = Absh(inQuath.qW);
	
}

void    QuathLerp(const Quath&  l, const Quath& r, F16 t,  Quath* outQuath) {
	//Linear interpolation
	//q(t)=(1−t) * q1 + t * q2
	Quatf lf;
	QuathToQuatf(l, &lf);
	Quatf rf;
	QuathToQuatf(r, &rf);
	F32 tF = toFloat32(t);
	Quatf outQuatf;
	QuatfLerp(lf, rf, tF, &outQuatf);
	QuatfToQuath(outQuatf, outQuath);
}

void   QuathFromAxisAngle(const Vec3h& FDK_RESTRICT  inAxis, F16 angle,Quath* FDK_RESTRICT outQuath){
	Vec3f inAxisF;
	Vec3hToVec3f(inAxis, &inAxisF);
	F32 angleF = toFloat32(angle);
	Quatf outQuatf;
	QuatfFromAxisAngle(inAxisF, angleF, &outQuatf);
	QuatfToQuath(outQuatf, outQuath);
}

void   QuathGetAxis             (const Quath& FDK_RESTRICT inQuath, Vec3h* FDK_RESTRICT outAxis) {
	Quatf inQuatf;
	QuathToQuatf(inQuath, &inQuatf);
	Vec3f outAxisf;
	QuatfGetAxis(inQuatf, &outAxisf);
	Vec3fToVec3h(outAxisf, outAxis);
}

void   QuathGetAngle            (const Quath& FDK_RESTRICT inQuath, F16* outAngle) {
	Quatf inQuatf;
	QuathToQuatf(inQuath, &inQuatf);
	F32 outAngleF = 2.0f * ArcCosf(inQuath.qW);
	*outAngle = toFloat16(outAngleF);
}


void   QuathToAxisAngle         (const Quath& FDK_RESTRICT inQuath, F16* outAngle, Vec3h* outAxis) {
	Quatf inQuatf;
	QuathToQuatf(inQuath, &inQuatf);
	F32 outAnglef = toFloat32(*outAngle);
	Vec3f outAxisf;
	QuatfGetAngle(inQuatf, &outAnglef);
	QuatfGetAxis(inQuatf, &outAxisf);
	*outAngle = toFloat16(outAnglef);
	Vec3fToVec3h(outAxisf, outAxis);
}

void   QuathSlerp(const Quath&  l, const Quath& r, F16 t,  Quath* outQuath) {
	Quatf lf;
	QuathToQuatf(l, &lf);
	Quatf rf;
	QuathToQuatf(r, &rf);
	F32 tF = toFloat32(t);
	Quatf outQuatf;
	QuatfSlerp(lf, rf, tF, &outQuatf);
	QuatfToQuath(outQuatf, outQuath);
}

void   QuathToQuatf        (const Quath&  inQuath, Quatf* outQuatf) {
	outQuatf->qW = toFloat32(inQuath.qW);
	outQuatf->qX = toFloat32(inQuath.qX);
	outQuatf->qY = toFloat32(inQuath.qY);
	outQuatf->qZ = toFloat32(inQuath.qZ);
}

void   QuatfToQuath        (const Quatf&  inQuatf, Quath* outQuath) {
	outQuath->qW = toFloat16(inQuatf.qW);
	outQuath->qX = toFloat16(inQuatf.qX);
	outQuath->qY = toFloat16(inQuatf.qY);
	outQuath->qZ = toFloat16(inQuatf.qZ);
}

//Inplace

void QuathSumInplace(const Quath& r, Quath* outQuath) {
	Quatf rf;
	QuathToQuatf(r, &rf);
	Quatf outQuatf;
	QuathToQuatf(*outQuath, &outQuatf);
	QuatfSumInplace(rf, &outQuatf);
	QuatfToQuath(outQuatf, outQuath);
}

void    QuathSubInplace(const Quath& r, Quath* outQuath) {
	Quatf rf;
	QuathToQuatf(r, &rf);
	Quatf outQuatf;
	QuathToQuatf(*outQuath, &outQuatf);
	QuatfSubInplace(rf, &outQuatf);
	QuatfToQuath(outQuatf, outQuath);
}

FDK_NS_END
