#ifndef CameraManagerH
#define CameraManagerH
#include <map>
#include "MoogeType.h"

using namespace std;
using namespace MoogeType;

class CCamera;
class CMooge;

class CCameraManager
{
	//Only CMooge class(main interface of engine) has the power to use me.
	friend CMooge;

	public:
		//========== [Camera Object Method] ==========
		//Add a camera.
		bool AddCamera(CCamera*& ReturnPtr);
		//Remove a camera.
		bool RemoveCamera(CCamera*& ObjectPtr);
		//Clear all camera.
		void RemoveAllCamera();
		//Set using a camera by ID.
		bool SetCurrentCamera(CCamera*& ObjectPtr);
		//============================================

	private:
		//Default constructor.
		CCameraManager();

		//Defaule destructor.
		~CCameraManager();

		//Post current camera to it's position.
		void Post();

	private:
		//Manage CCamera objects in this map.
		map<CAMERAID, CCamera*> mCameraMap;

		//Store current using(looking) camera.
		CCamera* mCurrentCamera;

		//Object ID generator.
		unsigned int CAMERAIDSEQ;

};


#endif