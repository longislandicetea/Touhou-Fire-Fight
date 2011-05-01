#include "Camera.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

//Default constructor.
CCamera::CCamera()
{

}

//Construct with ObjectID.
CCamera::CCamera(CAMERAID ObjectID): mObjectID(ObjectID)
{
	ZeroMemory(&mEye, sizeof(VECTORFS));
	ZeroMemory(&mCenter, sizeof(VECTORFS));
	ZeroMemory(&mUp, sizeof(VECTORFS));
}

//Default destructor.
CCamera::~CCamera()
{

}

//Place camera to it's position.
void CCamera::Post()
{
	glLoadIdentity();
	//Place viewing position.
	gluLookAt(mEye.x, mEye.y, mEye.z, mCenter.x, mCenter.y, mCenter.z, mUp.x, mUp.y, mUp.z);
}

//Get ID of this object.
CAMERAID CCamera::GetObjectID()
{
	return mObjectID;
}

//Shift the camera position.
void CCamera::Shift(const VECTORFS& ShiftVecIn)
{
	//Add the input vector to camera vector elements.
	mEye.AddSelf(ShiftVecIn);
	mCenter.AddSelf(ShiftVecIn);
}

//Set position ofo this camera.
void CCamera::SetPosition(const VECTORFS& EyeVecIn, const VECTORFS& CenterVecIn, const VECTORFS& UpVecIn)
{
	//Just remember all vector.
	memcpy(&mEye, &EyeVecIn, sizeof(VECTORFS));
	memcpy(&mCenter, &CenterVecIn, sizeof(VECTORFS));
	memcpy(&mUp, &UpVecIn, sizeof(VECTORFS));
}

void CCamera::Forward(const float& Range)
{
	//Calaulate the forward vector.
	VECTORFS ForwardVec(mCenter.Sub(mEye));
	ForwardVec.y = 0.0;
	//Shift camera by the result vector.
	Shift(ForwardVec.Normalize().Multi(Range));
}

void CCamera::Backward(const float& Range)
{
	//Calaulate the backward vector.
	VECTORFS BackwardVec(mCenter.Sub(mEye));
	BackwardVec.y = 0.0;
	//Shift camera by the result vector.
	Shift(BackwardVec.Normalize().Multi(-Range));
}

void CCamera::Leftward(const float& Range)
{
	//Find the normal vector of mCenter and mUp
	VECTORFS LeftwardVec(mCenter.Sub(mEye));
	//Shift camera by the result vector.
	Shift(LeftwardVec.Cross(mUp).Normalize().Multi(-Range));
}

void CCamera::Rightward(const float& Range)
{
	//Find the normal vector of mCenter and mUp
	VECTORFS RightwardVec(mCenter.Sub(mEye));
	//Shift camera by the result vector.
	Shift(RightwardVec.Cross(mUp).Normalize().Multi(Range));
}

//Rotate camera. (radial angle)
void CCamera::PitchRad(const float& Radius)
{
	//Vertical rotation: Right vector as axis.
	//Oops, we dont have a right vector so we need to calculate it first.
	VECTORFS RightVec(mCenter.Sub(mEye).Cross(mUp).Normalize());

	//Precalculate sin(Angle).
	float sinCoeff = sin(static_cast<float>(Radius));

	QUATERNION RotAxisQuat
		(
		//Build the rotated axis quaternion.
		cos(static_cast<float>(Radius)),
		sinCoeff*RightVec.x,
		sinCoeff*RightVec.y,
		sinCoeff*RightVec.z
		);

	QUATERNION CenterQuat
		(
		//Build rotating vector in quaternion form.
		0.0,
		mCenter.x - mEye.x,
		mCenter.y - mEye.y,
		mCenter.z - mEye.z
		);

	QUATERNION RotAxisConjQuat
		(
		//calculate conjugate of the quaternion
		RotAxisQuat.w,
		-RotAxisQuat.x,
		-RotAxisQuat.y,
		-RotAxisQuat.z
		);

	//I'm sorry if this hurt your eye.
	//It's just QUATERNION rotation formula.
	//see: http://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
	mCenter.Assign(mEye.Add(RotAxisQuat.Multi(CenterQuat).MultiVector(RotAxisConjQuat)));
}

void CCamera::YawRad(const float Radius)
{
	//Horizontal rotation: mUp as axis(actually we invert mUp so it will be a "mDown" vector).

	//Precalculate sin(Angle).
	float sinCoeff = sin(static_cast<float>(Radius));

	QUATERNION RotAxisQuat
	(
		//Build the rotated axis quaternion.
		cos(static_cast<float>(Radius)),
		sinCoeff*(-mUp.x),
		sinCoeff*(-mUp.y),
		sinCoeff*(-mUp.z)
	);

	QUATERNION CenterQuat
	(
		//Build rotating vector in quaternion form.
		0.0,
		mCenter.x - mEye.x,
		mCenter.y - mEye.y,
		mCenter.z - mEye.z
	);

	QUATERNION RotAxisConjQuat
	(
		//calculate conjugate of the quaternion
		RotAxisQuat.w,
		-RotAxisQuat.x,
		-RotAxisQuat.y,
		-RotAxisQuat.z
	);

	//I'm sorry if this hurt your eye.
	//It's just QUATERNION rotation formula.
	//see: http://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
	mCenter.Assign(mEye.Add(RotAxisQuat.Multi(CenterQuat).MultiVector(RotAxisConjQuat)));
}

void CCamera::PitchDeg(const float& Angle)
{
	PitchRad(static_cast<float>(Angle*0.5*M_PI/180.0));
}

void CCamera::YawDeg(const float Angle)
{
	YawRad(static_cast<float>(Angle*0.5*M_PI/180.0));
}

//VECTORFS RightwardVec(mCenter.Sub(mEye));
//RightwardVec.Cross(mUp);
//RightwardVec.Normalize();
//RightwardVec.MultiSelf(-Range);
////Shift by this vector.
//Shift(RightwardVec);