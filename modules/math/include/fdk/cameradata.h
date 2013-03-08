// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef __FDK_FORGE_CAMERADATA_H__
#define __FDK_FORGE_CAMERADATA_H__

#include "fdk/transform3f.h"
#include "fdk/vec3f.h"
#include "fdk/quatf.h"

FDK_NS_BEGIN

class CameraData{

private:

	Transform3f mViewMatrix;     //camera view matrix

	Transform3f mProjMatrix;     //camera projection matrix (define the camera frustum)

	Transform3f mViewProjMatrix;                //ViewProjection

	Quatf       mOrientation;    //final object orientation

	Vec3f       mPosition;       //camera position

	Vec3f       mWorldOffset;    //world offset

	//camera relative frame
	Vec3f       mForward;        //forward vector

	Vec3f       mUp;             //up vector

	Vec3f       mRight;          //right vector

	//Euler angles
	F32 mYaw;                    //yaw angle 

	F32 mPitch;                  //pitch angle 

	F32 mRoll;                   //roll angle

	//perspective matrix data
	F32 mNear;                   //near plane 

	F32 mFar;                    //far plane

	F32 mFov;                    //field of view

	F32 mAspectRatio;	         //perspective matrix aspect ratio

	bool  mUpdateViewMatrix;     //do we need to update the view matrix ? If we moved/rotated it yes, otherwise no!	

	bool  mIsCameraRelative;     //are applying our motions relative to the camera?
	
	#if defined (FDK_OS_OSX) || (FDK_OS_IOS)
		uint8_t __unused a [2];
	#else
		uint8_t __unused[2];
	#endif

public:

	CameraData();

	~CameraData();

	void update();

	const Transform3f& getViewMatrix() const;

	const Transform3f& getViewProjectionMatrix() const;

	const Vec3f& getPosition() const;

	void setPosition(const Vec3f& pos);

	void setPerspectiveMatrix(F32 fov,F32 aspectRatio,F32 zNear,F32 zFar);

	void moveXCameraRelative(F32 dx);

	void moveYCameraRelative(F32 dy);

	void moveZCameraRelative(F32 dz);	

	void rotateXCameraRelative(F32 dPitch);

	void rotateYCameraRelative(F32 dYaw);

	void rotateZCameraRelative(F32 dRoll);	

};

FDK_INLINE const Transform3f& CameraData::getViewMatrix() const{
	return mViewMatrix;
}

FDK_INLINE const Vec3f& CameraData::getPosition() const{
	return mPosition;
}

FDK_INLINE void CameraData::setPosition(const Vec3f& pos){
	mUpdateViewMatrix = true;
	mPosition = pos;
}

FDK_INLINE void CameraData::setPerspectiveMatrix(F32 fov,F32 aspectRatio,F32 zNear,F32 zFar){
	mFov         = fov;
	mNear        = zNear;
	mFar         = zFar;
	mAspectRatio = aspectRatio;
	Transform3fPerspectiveFovLH(fov,aspectRatio,zNear,zFar, &mProjMatrix);	
	TransformMultiply3f(mProjMatrix,mViewMatrix,&mViewProjMatrix);
}

FDK_INLINE const Transform3f& CameraData::getViewProjectionMatrix() const{
	return mViewProjMatrix;
}

FDK_INLINE void CameraData::moveXCameraRelative(F32 dx){
	Vec3fAddScale(mPosition,mRight,dx,&mPosition);
	mUpdateViewMatrix = true;
	mIsCameraRelative = true;
}

FDK_INLINE void CameraData::moveYCameraRelative(F32 dy){
	Vec3fAddScale(mPosition,mUp,dy,&mPosition);
	mUpdateViewMatrix = true;
	mIsCameraRelative = true;
}

FDK_INLINE void CameraData::moveZCameraRelative(F32 dz){
	Vec3fAddScale(mPosition,mForward,dz,&mPosition);
	mUpdateViewMatrix = true;
	mIsCameraRelative = true;
}

FDK_INLINE void CameraData::rotateXCameraRelative(F32 dPitch){
	mPitch = dPitch;
	mUpdateViewMatrix = true;
	mIsCameraRelative = true;
}

FDK_INLINE void CameraData::rotateYCameraRelative(F32 dYaw){
	mYaw   = dYaw;
	mUpdateViewMatrix = true;
	mIsCameraRelative = true;
}

FDK_INLINE void CameraData::rotateZCameraRelative(F32 dRoll){
	mRoll  = dRoll;
	mUpdateViewMatrix = true;
	mIsCameraRelative = true;
}


FDK_NS_END

#endif