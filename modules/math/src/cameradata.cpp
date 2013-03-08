// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#include "fdk/cameradata.h"

FDK_NS_BEGIN


CameraData::CameraData() : mPosition(0.f,0.f,0.f)	
                          ,mWorldOffset(0.f,0.f,0.f)
						  ,mYaw(0.f)
					      ,mPitch(0.f)
		                  ,mRoll(0.f)
                          ,mNear(1.f)
                          ,mFar(1000.f)
						  ,mFov(Deg2Radf(60.f))
                          ,mAspectRatio(1.f)
                          ,mUpdateViewMatrix(true)
						  ,mIsCameraRelative(true){ 	
	TransformInit3f(&mViewMatrix);	
	TransformInit3f(&mViewProjMatrix);
	QuatfIdentity(&mOrientation);
	Transform3fPerspectiveFovLH(mFov,mAspectRatio,mNear,mFar, &mProjMatrix);	
	TransformMultiply3f(mProjMatrix,mViewMatrix,&mViewProjMatrix);
}

CameraData::~CameraData() {
	
}

void CameraData::update(){
	if(mUpdateViewMatrix){
		Quatf       mRotXY;
		Quatf       mRotX;
		Quatf       mRotY;
		Quatf       mRotZ;
		Quatf       mOffsetQuat;
			
		//reset matrix and quaternions
		TransformInit3f(&mViewMatrix);
		QuatfIdentity(&mRotXY);
		QuatfIdentity(&mRotX);
		QuatfIdentity(&mRotY);
		QuatfIdentity(&mRotZ);

		//create orientation
		QuatfFromAxisAngle(Vec3f(1.f,0.f,0.f),mPitch,&mRotX);
		QuatfFromAxisAngle(Vec3f(0.f,1.f,0.f),mYaw,&mRotY);
		QuatfFromAxisAngle(Vec3f(0.f,0.f,1.f),mRoll,&mRotZ);
	    QuatfMult(mRotX,mRotY,&mRotXY);
		QuatfMult(mRotZ,mRotXY,&mOrientation);	

		//normalize quaternion
		QuatfNormalize(mOrientation,&mOrientation);
						
		//now extract the orientation part of the view matrix
		Mat44fInitFromQuaternion(mOrientation,&mViewMatrix.mat44f);

		//extract the orientation frame of reference vectors (forward,up,right)		
		mRight     = Vec3f(mViewMatrix.mat44f.v00,mViewMatrix.mat44f.v01,mViewMatrix.mat44f.v02);   
		mUp        = Vec3f(mViewMatrix.mat44f.v10,mViewMatrix.mat44f.v11,mViewMatrix.mat44f.v12);   
		mForward   = Vec3f(mViewMatrix.mat44f.v20,mViewMatrix.mat44f.v21,mViewMatrix.mat44f.v22);   

		mViewMatrix.mat44f.v03 = -Vec3fDot(mPosition,mRight);
		mViewMatrix.mat44f.v13 = -Vec3fDot(mPosition,mUp);
		mViewMatrix.mat44f.v23 = -Vec3fDot(mPosition,mForward);		
		
		//now recompose the viewprojection matrix
		TransformMultiply3f(mProjMatrix,mViewMatrix,&mViewProjMatrix);
		mUpdateViewMatrix = false;
	}
}

FDK_NS_END