
#include "WinManager.h"

//Forward declare mInstance, also set it to NULL.
CWinManager* CWinManager::mInstance = NULL;
//Forward declare the static map container.
map<HWND, CWinFrame*> CWinManager::mWinFrameProcMap;
map<HWND, CButton*> CWinManager::mButtonProcMap;

//default value for all class member here.
CWinManager::CWinManager(): mWinFramehWndWaiting(NULL), mWinFrameWaiting(NULL), mButtonhWndWaiting(NULL), mButtonWaiting(NULL)
{

}

CWinManager::~CWinManager()
{

}

//Get the singlton instance.
CWinManager* CWinManager::GetInstance()
{
	if(mInstance == NULL)
	{
		mInstance = new CWinManager();
		return mInstance;
	}else
	{
		return mInstance;
	}
}

//Start the WINAPI message loop.
void CWinManager::LetsRock()
{
	//Nothing to do with these now.
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

bool CWinManager::DeleteInstance()
{
	//Critical step! we should check if the mWinFrameProcMap is empty.
	//If we just delete instance and clear mWinFrameProcMap, the wndproc may go kaboom.
	if(mWinFrameProcMap.empty() && mInstance != NULL)
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

//Add a WinFrame to CWinFrameMgr. CWinFrameMgr store this WinFrame in mWinFrameWaiting and waiting for a match.
bool CWinManager::AddWinFrame(CWinFrame* WinFrame)
{
	//Check if there is any WinFrame currently waiting.
	if(mWinFrameWaiting != NULL)
	{
		return false;
	}else
	{
		//Store it.
		mWinFrameWaiting = WinFrame;
		return true;
	}
}

//Add a HWND to CWinFrameMgr. CWinFrameMgr'll try match a WinFrame for this hwnd.
bool CWinManager::AddWinFrameHWND(HWND hWnd)
{
	//Check if there is a hwnd currently waiting.
	if(mWinFramehWndWaiting != NULL)
	{
		return false;
	}else
	{
		//Store it.
		mWinFramehWndWaiting = hWnd;
		//Try match the waiting hwnd and winframe.
		if(MatchWinFrameWaiter())
		{
			//Success.
			return true;
		}else
		{
			//Failed.
			return false;
		}
	}
}

//Remove a WinFrame ptr from mWinFrameProcMap.
bool CWinManager::RemoveWinFrame(HWND hWnd)
{
	//Search mWinFrameProcMap for hWnd key first.
	if(mWinFrameProcMap.count(hWnd))
	{
		//Set the contain to NULL first.
		mWinFrameProcMap[hWnd] = NULL;
		//Erase it from the map.
		mWinFrameProcMap.erase(hWnd);
		return true;
	}else
	{
		return false;
	}
}

//This function let the WM_DESTROY in WinFrame decide whether to PostQuitMessge(0).
bool CWinManager::IsWinframeMapEmpty()
{
	return mWinFrameProcMap.empty();
}

CWinFrame* CWinManager::GetWinFrame(HWND hWnd)
{
  	//Search mWinFrameProcMap for hWnd key first.
	if(mWinFrameProcMap.count(hWnd))
	{
		//return the ptr directly.
		return mWinFrameProcMap[hWnd];
	}else
	{
		//no hWnd key found in map, return NULL.
		//User has to response checking if the return value is NULL.
		return NULL;
	}
}

//Add a Button ptr to CWinManager.
bool CWinManager::AddButton(CButton* Button)
{
	//Check if there is any CButton currently waiting.
	if(mButtonWaiting != NULL)
	{
		return false;
	}else
	{
		//Store it.
		mButtonWaiting = Button;
		return true;
	}
}

//Add a HWND to CWinManager. CWinManager'll try match a WinFrame for the hwnd.
bool CWinManager::AddButtonHWND(HWND hWnd)
{
	//Check if there is a Button hwnd currently waiting.
	if(mButtonhWndWaiting != NULL)
	{
		return false;
	}else
	{
		//Store it.
		mButtonhWndWaiting = hWnd;
		//Try match the waiting hwnd and button.
		if(MatchButtonWaiter())
		{
			//Success.
			return true;
		}else
		{
			//Failed.
			return false;
		}
	}
}

//Remove a WinFrame ptr from mWinFrameProcMap.
bool CWinManager::RemoveButton(HWND hWnd)
{
	//Search mWinFrameProcMap for hWnd key first.
	if(mButtonProcMap.count(hWnd))
	{
		//Set the contain to NULL first.
		mButtonProcMap[hWnd] = NULL;
		//Erase it from the map.
		mButtonProcMap.erase(hWnd);
		return true;
	}else
	{
		return false;
	}
}

bool CWinManager::IsButtonMapEmpty()
{
	return mButtonProcMap.empty();
}

//Search the mButtonProcMap for hWnd key value, if exist, return the associated Button ptr.
CButton* CWinManager::GetButton(HWND hWnd)
{
	//Search mButtonProcMap for hWnd key first.
	if(mButtonProcMap.count(hWnd))
	{
		//return the ptr directly.
		return mButtonProcMap[hWnd];
	}else
	{
		//no hWnd key found in map, return NULL.
		//User has to check if the return value is NULL before using it.
		return NULL;
	}
}

//Try match the hwnd and WinFrame that is currently waiting.
bool CWinManager::MatchWinFrameWaiter()
{
	//If both are not NULL. Well that's just what we need.
	if(mWinFramehWndWaiting != NULL && mWinFrameWaiting != NULL)
	{
		//Store them both to the map.
		mWinFrameProcMap[mWinFramehWndWaiting] = mWinFrameWaiting;
		//clear the waiter.
		mWinFramehWndWaiting = NULL;
		mWinFrameWaiting = NULL;
		return true;
	}else
	{
		//If any of them are NULL the match is a failed.
		return false;
	}
}

//Try match the waiting button and hWnd.
bool CWinManager::MatchButtonWaiter()
{
	//If both are not NULL. Well that's just what we need.
	if(mButtonhWndWaiting != NULL && mButtonWaiting != NULL)
	{
		//Store them both to the map.
		mButtonProcMap[mButtonhWndWaiting] = mButtonWaiting;
		//clear the waiter.
		mButtonhWndWaiting = NULL;
		mButtonWaiting = NULL;
		return true;
	}else
	{
		//If any of them are NULL the match is a failed.
		return false;
	}
}
