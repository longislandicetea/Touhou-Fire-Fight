#include "CameraManager.h"
#include "Camera.h"

//Default constructor.
CCameraManager::CCameraManager(): mCurrentCamera(NULL)
{
	CAMERAIDSEQ = 1000000000;
}

//Defaule destructor.
CCameraManager::~CCameraManager()
{
	mCurrentCamera= NULL;
 	//Remove all camera in map.
	for (map<CAMERAID, CCamera*>::iterator MapIter = mCameraMap.begin() ; MapIter != mCameraMap.end() ; MapIter++)
	{
		delete MapIter->second;
	}
	mCameraMap.clear();
}

//Post current camera to it's position.
void CCameraManager::Post()
{
	if(mCurrentCamera != NULL)
		mCurrentCamera->Post();
}

//Add a camera.
bool CCameraManager::AddCamera(CCamera*& ReturnPtr)
{
	//Current camera seq +1;
	CAMERAIDSEQ++;

	mCameraMap[CAMERAIDSEQ] = new CCamera(CAMERAIDSEQ);

	//If the current camera is NULL. Use this one.
	if(mCurrentCamera == NULL)
		mCurrentCamera = mCameraMap[CAMERAIDSEQ];

	//Return camera ptr to user.
	ReturnPtr = mCameraMap[CAMERAIDSEQ];

	return true;
}

//Remove a camera.
bool CCameraManager::RemoveCamera(CCamera*& ObjectPtr)
{
	//Is user a monkey?
	if(ObjectPtr == NULL)
		return false;

	//Try fine the ID in map first.
	CAMERAID CameraID = ObjectPtr->GetObjectID();
	map<CAMERAID, CCamera*>::iterator MapIter = mCameraMap.find(CameraID);

	if(MapIter != mCameraMap.end())
	{
		//Found it.
		//Delete the object.
		delete mCameraMap[CameraID];
		//Set NULL to the user specific ptr.
		ObjectPtr = NULL;
		//Erase from map.
		mCameraMap.erase(CameraID);
		return true;
	}else
	{
		//Not found. Delete element failed.
		return false;
	}
}

//Clear all camera.
void CCameraManager::RemoveAllCamera()
{
	//Be very careful...remember to remove current using camera first.
	mCurrentCamera = NULL;
	//Remove all camera in map.
	for (map<CAMERAID, CCamera*>::iterator MapIter = mCameraMap.begin() ; MapIter != mCameraMap.end() ; MapIter++)
	{
		delete MapIter->second;
	}
	mCameraMap.clear();
}

//Set using a camera by ID.
bool CCameraManager::SetCurrentCamera(CCamera*& ObjectPtr)
{
	//Is user a monkey?
	if(ObjectPtr == NULL)
		return false;

	//Try fine the ID in map first.
	CAMERAID CameraID = ObjectPtr->GetObjectID();
	map<CAMERAID, CCamera*>::iterator MapIter = mCameraMap.find(CameraID);

	if(MapIter != mCameraMap.end())
	{
		//Found it. Use it
		mCurrentCamera = mCameraMap[CameraID];
		return true;
	}else
	{
		//Not found.
		return false;
	}
}