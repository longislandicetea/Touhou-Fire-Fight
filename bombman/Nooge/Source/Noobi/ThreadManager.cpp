#include "ThreadManager.h"
#include "Thread.h"

//Forward declare mInstance, also set it to NULL.
CThreadManager* CThreadManager::mInstance = NULL;
//Forward declare the static map container.
map<unsigned, CThread*> CThreadManager::mTreadMap;

//cant be new.
CThreadManager::CThreadManager()
{

}

//Cant be destroy.
//Only self destroy is allow. See DeleteInstance();
CThreadManager::~CThreadManager()
{

}

//Get the singlton instance.
CThreadManager* CThreadManager::GetInstance()
{
	if(mInstance == NULL)
	{
		mInstance = new CThreadManager();
		return mInstance;
	}else
	{
		return mInstance;
	}
}

//Self destroy the singlton instance.
bool CThreadManager::DeleteInstance()
{
	if(mInstance != NULL)
	{
		delete mInstance;
		mInstance = NULL;
		return true;
	}else
	{
		//Oops! somethings wrong, but we shouldnt delete instance here.
		//Swallow the error I guess.
		return false;
	}
}

//Add a CThread ptr to mTreadMap.
bool CThreadManager::AddThread(unsigned ThreadID, CThread* Thread)
{
	//Try to find to ThreadID in map first.
	map<unsigned, CThread*>::iterator MapIter = mTreadMap.find(ThreadID);

	//Oops! ID exist. Something wrong!
	if(MapIter != mTreadMap.end())
	{
		return false;
	}else
	{
		//Remember the thread in map.
		mTreadMap[ThreadID] = Thread;
		return true;
	}
}

//Remove a CThread ptr from mTreadMap.
bool CThreadManager::RemoveThread(unsigned ThreadID)
{
	//Try to find to ThreadID in map first.
	map<unsigned, CThread*>::iterator MapIter = mTreadMap.find(ThreadID);

	//Found it. Erase it.
	if(MapIter != mTreadMap.end())
	{
		mTreadMap.erase(ThreadID);
		return true;
	}else
	{
		//Oops! Something wrong!
		return false;
	}
}

//Check if the thread map is empty.
bool CThreadManager::IsThreadMapEmpty()
{
	return mTreadMap.empty();
}

//Search the mTreadMap for hWnd key value, if exist, return the associated CThread ptr.
CThread* CThreadManager::GetThread(unsigned ThreadID)
{
	//Search mTreadMap for ThreadID first.
	if(mTreadMap.count(ThreadID))
	{
		//return the ptr directly.
		return mTreadMap[ThreadID];
	}else
	{
		//no ThreadID found in map, return NULL.
		//User has to check if the return value is NULL before using it.
		return NULL;
	}
}

//------------------------------------------------------------------------------------------------