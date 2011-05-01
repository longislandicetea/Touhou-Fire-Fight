#ifndef CameraH
#define CameraH

#include "MoogeType.h"

using namespace MoogeType;

//Forward declaure of friend class.
class CCameraManager;

class CCamera
{
	friend CCameraManager;
	public:
		//Get ID of this object.
		CAMERAID GetObjectID();

		//Shift the camera position. (Effect both on 3-element)
		void Shift(const VECTORFS& ShiftVecIn);

		//Set position ofo this camera.
		void SetPosition(const VECTORFS& EyeVecIn, const VECTORFS& CenterVecIn, const VECTORFS& UpVecIn);

		//Move on the x-z plain.
		void Forward(const float& Range);
		void Backward(const float& Range);
		void Leftward(const float& Range);
		void Rightward(const float& Range);

		//Rotate camera. (Degree)
		void PitchRad(const float& Radius);
		void YawRad(const float Radius);
		//Rotate camera. (Radius)
		void PitchDeg(const float& Angle);
		void YawDeg(const float Angle);

	private:
		//Default constructor.
		CCamera();

		//Construct with ObjectID.
		CCamera(CAMERAID ObjectID);

		//Default destructor.
		~CCamera();
		
		//Place camera to it's position.
		void Post();

	private:
		//ObjectID.
		CAMERAID mObjectID;

		//Eye location.
		VECTORFS mEye;
		//Center vector.
		VECTORFS mCenter;
		//Up vector.
		VECTORFS mUp;
};

#endif