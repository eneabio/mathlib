// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/quatd.h"
#include "fdk/mathd.h"
#include "fdk/vec3d.h"

FDK_NS_BEGIN

void QuatdInit(Quatd* outQuat) {
	outQuat->qX = 0.0;
	outQuat->qY = 0.0;
	outQuat->qZ = 0.0;
	outQuat->qW = 0.0;
}

void QuatdInitWithValues(F64 x, F64 y, F64 z, F64 w, Quatd* outQuat) {
	outQuat->qX = x;
	outQuat->qY = y;
	outQuat->qZ = z;
	outQuat->qW = w;
	
	F64 length = QuatdModulus(*outQuat);
	
	//to do with toll
	bool res = FdkEqd64(length, 1.0, FDK_F64_TOLL);
	FDK_ASSERT(res);
	
}

void   QuatdIdentity(Quatd* outQuat){
	outQuat->qX = 0.0;
	outQuat->qY = 0.0;
	outQuat->qZ = 0.0;
	outQuat->qW = 1.0;
}

void   QuatdInitWithEulerAngles(F64 yaw, F64 roll, F64 pitch, Quatd* outQuat) {
	//Set the quaternion using euler angles (YZX)
	/*F64 halfYaw   = yaw*0.5;
	 F64 halfPitch = pitch*0.5;
	 F64 halfRoll  = roll*0.5;
	 
	 F64 c1 = Cosd(halfYaw);
	 F64 c2 = Cosd(halfRoll);
	 F64 c3 = Cosd(halfPitch);
	 F64 s1 = Sind(halfYaw);
	 F64 s2 = Sind(halfRoll);
	 F64 s3 = Sind(halfPitch);
	 
	 //set quaternion
	 outQuat->qW = c1 * c2 * c3 - s1 * s2 * s3;
	 outQuat->qX = s1 * s2 * c3 + c1 * c2 * s3;
	 outQuat->qY = s1 * c2 * c3 + c1 * s2 * s3;
	 outQuat->qZ = c1 * s2 * c3 - s1 * c2 * s3;*/
	
	F64 p = pitch * 0.5;
	F64 y = yaw   * 0.5;
	F64 r = roll  * 0.5;
	
	F64 sinp = Sind(p);
	F64 siny = Sind(y);
	F64 sinr = Sind(r);
	F64 cosp = Cosd(p);
	F64 cosy = Cosd(y);
	F64 cosr = Cosd(r);
	
	outQuat->qX = sinr * cosp * cosy - cosr * sinp * siny;
	outQuat->qY = cosr * sinp * cosy + sinr * cosp * siny;
	outQuat->qZ = cosr * cosp * siny - sinr * sinp * cosy;
	outQuat->qW = cosr * cosp * cosy + sinr * sinp * siny;
	
	QuatdNormalize(*outQuat, outQuat);
}

F64 QuatdModulus (const Quatd& inQuatd) {
	F64 inQuatdxQ = inQuatd.qX * inQuatd.qX;
	F64 inQuatdyQ = inQuatd.qY * inQuatd.qY;
	F64 inQuatdzQ = inQuatd.qZ * inQuatd.qZ;
	F64 inQuatdwQ = inQuatd.qW * inQuatd.qW;
	return Sqrtd(inQuatdxQ + inQuatdyQ + inQuatdzQ + inQuatdwQ);
}


F64    QuatdSquaredModulus      (const Quatd& FDK_RESTRICT inQuatd) {
	F64 inQuatdxQ = inQuatd.qX * inQuatd.qX;
	F64 inQuatdyQ = inQuatd.qY * inQuatd.qY;
	F64 inQuatdzQ = inQuatd.qZ * inQuatd.qZ;
	F64 inQuatdwQ = inQuatd.qW * inQuatd.qW;
	return (inQuatdxQ + inQuatdyQ + inQuatdzQ + inQuatdwQ);
}

void   QuatdNormalize(const Quatd&  inQuatd, Quatd* outQuatd) {
	F64 length2 = QuatdSquaredModulus(inQuatd);
	
	//lenght different from zero...
	if (Fabsd(length2) > FDK_F64_TOLL && Fabsd(length2 - 1.0) > FDK_F64_TOLL) {
		//if (FdkEqF64(length2, 0.0, FDK_F64_TOLL)) {
		F64 length = Sqrtd(length2);
		outQuatd->qX = inQuatd.qX / length;
		outQuatd->qY = inQuatd.qY / length;
		outQuatd->qZ = inQuatd.qZ / length;
		outQuatd->qW = inQuatd.qW / length;
		
		return;
	}
	
	outQuatd->qX = inQuatd.qX;
	outQuatd->qY = inQuatd.qY;
	outQuatd->qZ = inQuatd.qZ;
	outQuatd->qW = inQuatd.qW;
}

void  QuatdConjugate(const Quatd&  inQuatd, Quatd* outQuatd) {
	outQuatd->qX = - inQuatd.qX;
	outQuatd->qY = - inQuatd.qY;
	outQuatd->qZ = - inQuatd.qZ;
	outQuatd->qW =  inQuatd.qW;
}

void   QuatdInverse(const Quatd&  inQuatd, Quatd* outQuatd) {
	F64   mod  = QuatdModulus(inQuatd);
	Quatd temp;
	QuatdConjugate(inQuatd, &temp);
	//mod different from zero...
	if( mod != 0) {
		outQuatd->qX =  temp.qX / (mod * mod);
		outQuatd->qY =  temp.qY / (mod * mod);
		outQuatd->qZ =  temp.qZ / (mod * mod);
		outQuatd->qW =  temp.qW / (mod * mod);
	}
}

F64     QuatdDot(const Quatd& l, const Quatd& r) {
	
	F64 qXMul = l.qX * r.qX;
	F64 qYMul = l.qY * r.qY;
	F64 qZMul = l.qZ * r.qZ;
	F64 qWMul = l.qW * r.qW;
	F64 res = qXMul + qYMul + qZMul + qWMul;
	return res;
	
}

void    QuatdMultScalar(const Quatd& inQuat, const F64 scalar, Quatd* outQuat) {
	
	outQuat->qX = scalar * inQuat.qX;
	outQuat->qY = scalar * inQuat.qY;
	outQuat->qZ = scalar * inQuat.qZ;
	outQuat->qW = scalar * inQuat.qW;
}


void    QuatdMult(const Quatd& l, const Quatd& r, Quatd* outQuad) {
	
	outQuad->qX = l.qW * r.qX + l.qX * r.qW + l.qY * r.qZ - l.qZ * r.qY;
	outQuad->qY = l.qW * r.qY - l.qX * r.qZ + l.qY * r.qW + l.qZ * r.qX;
	outQuad->qZ = l.qW * r.qZ + l.qX * r.qY - l.qY * r.qX + l.qZ * r.qW;
	outQuad->qW = l.qW * r.qW - l.qX * r.qX - l.qY * r.qY - l.qZ * r.qZ;
}

void    QuatdSum(const Quatd& l, const Quatd& r, Quatd* outQuad) {
	outQuad->qX = r.qX + l.qX;
	outQuad->qY = r.qY + l.qY;
	outQuad->qZ = r.qZ + l.qZ;
	outQuad->qW = r.qW + l.qW;
	
}

void    QuatdSub(const Quatd& l, const Quatd& r, Quatd* outQuad) {
	outQuad->qX = l.qX - r.qX;
	outQuad->qY = l.qY - r.qY;
	outQuad->qZ = l.qZ - r.qZ;
	outQuad->qW = l.qW - r.qW;
	
}

void    QuatdAbs(const Quatd&  inQuatd, Quatd* outQuad) {
	outQuad->qX = Absd(inQuatd.qX);
	outQuad->qY = Absd(inQuatd.qY);
	outQuad->qZ = Absd(inQuatd.qZ);
	outQuad->qW = Absd(inQuatd.qW);
	
}

void    QuatdLerp(const Quatd&  l, const Quatd& r, F64 t,  Quatd* outQuat) {
	//Linear interpolation
	//q(t)=(1−t) * q1 + t * q2
	Quatd first;
	Quatd second;
	QuatdMultScalar(l, (1.0-t), outQuat);
	first = *outQuat;
	QuatdMultScalar(r, t, outQuat);
	second = *outQuat;
	QuatdSum(first, second , outQuat);
	
}

void   QuatdFromAxisAngle(const Vec3d& FDK_RESTRICT  inAxis,F64 angle,Quatd* FDK_RESTRICT outQuatd){
	Vec3d inAxisNorm;
	F64   halfAngle     = angle * 0.5;
	F64   sinHalfAngle  = Sind(halfAngle);
	Vec3dNormalize(inAxis,&inAxisNorm); //normalize the axis (since we don't know if it's normalized)
	outQuatd->qX      = inAxisNorm.x*sinHalfAngle;
	outQuatd->qY      = inAxisNorm.y*sinHalfAngle;
	outQuatd->qZ      = inAxisNorm.z*sinHalfAngle;
	outQuatd->qW      = Cosd(halfAngle);
}

void   QuatdGetAxis             (const Quatd& FDK_RESTRICT inQuatd, Vec3d* FDK_RESTRICT outAxis) {
	F64 scale = Sind(ArcCosd(inQuatd.qW));
	
	if ( scale < FDK_F64_TOLL && scale > -FDK_F64_TOLL ) {
		outAxis->x = 0.0;
		outAxis->y = 0.0;
		outAxis->z = 0.0;
	} else {
		outAxis->x = inQuatd.qX / scale;
		outAxis->y = inQuatd.qY / scale;
		outAxis->z = inQuatd.qZ / scale;
	}
}

void   QuatdGetAngle            (const Quatd& FDK_RESTRICT inQuatd, F64* outAngle) {
	*outAngle = 2.0 * ArcCosd(inQuatd.qW);
}


void   QuatdToAxisAngle         (const Quatd& FDK_RESTRICT inQuatd, F64* outAngle, Vec3d* outAxis) {
	QuatdGetAngle(inQuatd, outAngle);
	QuatdGetAxis(inQuatd, outAxis);
}

void   QuatdSlerp(const Quatd&  l, const Quatd& r, F64 t,  Quatd* outQuat) {
	Quatd start = Quatd(0.0, 0.0, 0.0, 0.0);
        F64 recipSinAngle, scale0, scale1, cosAngle, angle;
        cosAngle = QuatdDot(l, r);	//is it to normalize?
        if ( cosAngle < 0.0 ) {
		cosAngle = -cosAngle;
		QuatdSubInplace(l, &start);
        } else {
		start = l;
        }
        if ( cosAngle < 0.999 ) {
		angle = ArcCosd(cosAngle);
		recipSinAngle = ( 1.0 / Sind(angle));
		scale0 = ( Sind( ( ( 1.0 - t ) * angle ) ) * recipSinAngle );
		scale1 = ( Sind( ( t * angle ) ) * recipSinAngle );
        } else {
		scale0 = ( 1.0 - t );
		scale1 = t;
        }
	QuatdMultScalar(start, scale0, outQuat);
        Quatd first = *outQuat;
	QuatdMultScalar(r, scale1, outQuat);
	Quatd second = *outQuat;
	QuatdSum(first, second, outQuat);
	
}

void QuatdSumInplace(const Quatd& r, Quatd* outQuad) {
	outQuad->qX = outQuad->qX + r.qX;
	outQuad->qY = outQuad->qY + r.qY;
	outQuad->qZ = outQuad->qZ + r.qZ;
	outQuad->qW = outQuad->qW + r.qW;
}

void    QuatdSubInplace(const Quatd& r, Quatd* outQuad) {
	outQuad->qX = outQuad->qX - r.qX;
	outQuad->qY = outQuad->qY - r.qY;
	outQuad->qZ = outQuad->qZ - r.qZ;
	outQuad->qW = outQuad->qW - r.qW;
}

FDK_NS_END
