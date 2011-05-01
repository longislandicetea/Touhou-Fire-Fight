#include <map>
#include <algorithm>
#include <process.h>
#include "WinFrame.h"
#include "WinManager.h"
#include "resource.h"
#include "Text.h"
#include "Button.h"
#include "Edit.h"

//Default attribute of a winframe.
static const int WINFRAME_DEFAULT_POSX = 50;
static const int WINFRAME_DEFAULT_POSY = 50;
static const int WINFRAME_DEFAULT_WIDTH = 640;
static const int WINFRAME_DEFAULT_HEIGHT = 480;

//constructor: initial all class member variables here.
CWinFrame::CWinFrame()
	:mhWnd(NULL), mPosX(WINFRAME_DEFAULT_POSX), mPosY(WINFRAME_DEFAULT_POSY), mWidth(WINFRAME_DEFAULT_WIDTH), mHeight(WINFRAME_DEFAULT_HEIGHT)
{

}

//Simple constructor.
CWinFrame::CWinFrame(string Name, string title)
	:mhWnd(NULL), mPosX(WINFRAME_DEFAULT_POSX), mPosY(WINFRAME_DEFAULT_POSY), mWidth(WINFRAME_DEFAULT_WIDTH), mHeight(WINFRAME_DEFAULT_HEIGHT)
{
	//Simple way.
	Load(Name, title);
}

//Advance constructor.
CWinFrame::CWinFrame(string Name, string title, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height)
	:mhWnd(NULL), mPosX(Left), mPosY(Top), mWidth(Width), mHeight(Height)
{
	//Simple way.
	Load(Name, title);
}

CWinFrame::~CWinFrame()
{
	//Simple way.
	Unload();
}

//Load the WinFrame object use default value.
bool CWinFrame::Load(string Name, string title)
{
	//check if this object has been loaded.
	if(mhWnd)
	{
		//oops, object has been loaded b4.
		return false;
	}else
	{
		//use WINAPI to get current intstance.
		HINSTANCE tmpInstance = GetModuleHandle(NULL);

		//Create our [default] WNDCLASS here.
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		//[OpenGL require]: CS_OWNDC
		wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		//beware, StaticWndProc() is a static function.
		wcex.lpfnWndProc	= StaticWndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= tmpInstance;
		wcex.hIcon			= static_cast<HICON>(LoadImage(tmpInstance, MAKEINTRESOURCE(IDI_FRAMEICON), IMAGE_ICON, 64, 64, LR_DEFAULTSIZE));
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)COLOR_WINDOW;
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= Name.c_str();
		wcex.hIconSm		= static_cast<HICON>(LoadImage(tmpInstance, MAKEINTRESOURCE(IDI_SFRAMEICON), IMAGE_ICON, 32, 32, LR_DEFAULTSIZE));

		//Register our WNDCLASS.
		RegisterClassEx(&wcex);

		//Try associate this object with its hwnd, store in a static container within CWinFrameMgr.
		CWinManager::GetInstance()->AddWinFrame(this);

		//Here we gonna use mPosX/mPosY/mWidth/mHeight as client area rect to calculate our TRUE window rect.
		RECT tmpClientRect;
		tmpClientRect.left = mPosX;
		tmpClientRect.top = mPosY;
		tmpClientRect.right = mPosX + mWidth;
		tmpClientRect.bottom = mPosY + mHeight;

		//calculate our TRUE window rect here.
		AdjustWindowRect(&tmpClientRect, WS_DLGFRAME | WS_CAPTION | WS_SYSMENU, false );

		//Create Window use [default] values.
		//[OpenGL require]: WS_CLIPCHILDREN, WS_CLIPSIBLINGS
		//Interesting fact: we gonna get our mhWnd when first time wndproc() enter. Not here.
		/*mhWnd = */CreateWindowEx(NULL, wcex.lpszClassName, title.c_str(),
			WS_DLGFRAME | WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
			//Note: This rect is calculate from client rect.
			tmpClientRect.left, tmpClientRect.top, tmpClientRect.right - tmpClientRect.left, tmpClientRect.bottom - tmpClientRect.top
			, 0, 0, tmpInstance, 0);

		//Load object success!
		return true;
	}
}

//Load the WinFrame object use custom values.
bool CWinFrame::Load(string Name, string title, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height)
{
	//check if this object has been loaded.
	if(mhWnd)
	{
		//oops, object has been loaded b4.
		return false;
	}else
	{
		//Just remember the input param.
		mPosX = Left;
		mPosY = Top;
		mWidth = Width;
		mHeight = Height;

		//Simple way.
		return Load(Name, title);
	}
}

//Unload a WinFrame.
bool CWinFrame::Unload()
{
	//check if this object has been loaded.
	if(mhWnd)
	{
		//Suicide.
		DestroyWindow(mhWnd);
		//Forget everything.
		mhWnd = NULL;
		mMessageMap.clear();
		mButtonMap.clear();
		mTextMap.clear();
		return true;
	}else
	{
		return false;
	}
}

//Get the handle of this WinFrame object.
HWND CWinFrame::gethWnd()
{
	return mhWnd;
}

//Add an Event callback to specific WM msg.
bool CWinFrame::AddCallBackEvent(UINT uintIn, const function<void (const WinMsgPackage&)>& CallbackMsgEventIn)
{
	//Thanks to the all-mighty STL container and tr1::function.

	//See if we can find any specific msg callback function in map...
	map<UINT, function<void (const WinMsgPackage&)> >::iterator MapIter = mMessageMap.find(uintIn);

	//If we found one:
	if(MapIter != mMessageMap.end())
	{
		//Oops! Event exist! Cant add again.
		return false;
	}else
	{
		//If we didnt:
		mMessageMap[uintIn] = CallbackMsgEventIn;
		return true;
	}
}

//Remove an Event callback to specific WM msg.
bool CWinFrame::RemoveCallBackEvent(UINT uintIn)
{
	//See if we can find any specific msg callback function in map...
	map<UINT, function<void (const WinMsgPackage&)> >::iterator MapIter = mMessageMap.find(uintIn);

	//If we found one:
	if(MapIter != mMessageMap.end())
	{
		//Erase it.
		mMessageMap.erase(uintIn);
		return true;
	}else
	{
		//If we didnt:
		return false;
	}
}

//Add a CustomProc callback that callbacks [Every] wndproc msg.
bool CWinFrame::AssignCustomProc(const function<void (const WinMsgPackage&)>& CallbackMsgEventIn)
{
	//If member customproc is NULL than accept the input.
	if(mCustomProc == NULL)
	{
		mCustomProc = CallbackMsgEventIn;
		return true;
	}else
	{
		return false;
	}	
}

//Clear Current set CustomProc callback
bool CWinFrame::ClearCustomProc()
{
	if(mCustomProc == NULL)
	{
		//No need to clear.
		return false;
	}else
	{
		//Clear the custom proc member function.
		mCustomProc = NULL;
		return true;
	}
}

//Tell the WinFrame to remember this Text object.
bool CWinFrame::AddTextObject(HWND hWnd, CText* TextObjPtr)
{
	//See if we found any same object here.
	map<HWND, CText*>::iterator MapIter = mTextMap.find(hWnd);

	if(MapIter != mTextMap.end())
	{
		//Oops! Object exist! User is a monkey.
		return false;
	}else
	{
		//Add the text object.
		mTextMap[hWnd] = TextObjPtr;
		return true;
	}
}

//Remove a text object from the textmap.
bool CWinFrame::RemoveTextObject(HWND hWnd)
{
	//See if we found any same object here.
	map<HWND, CText*>::iterator MapIter = mTextMap.find(hWnd);

	if(MapIter != mTextMap.end())
	{
		//Found it. Erase it.
		mTextMap.erase(hWnd);
		return true;
	}else
	{
		//Nope.
		return false;
	}
}

bool CWinFrame::AddButtonObject(unsigned int BtnID, CButton* BtnObjPtr)
{
	//See if we found any same object here.
	map<unsigned int, CButton*>::iterator MapIter = mButtonMap.find(BtnID);

	if(MapIter != mButtonMap.end())
	{
		//Oops! Button object exist! User is a monkey
		return false;
	}else
	{
		//Add this Button object into map.
		mButtonMap[BtnID] = BtnObjPtr;
		return true;
	}
}

//Remove a button object from the map.
bool CWinFrame::RemoveButtonObject(unsigned int BtnID)
{
	//See if we found any same object here.
	map<unsigned int, CButton*>::iterator MapIter = mButtonMap.find(BtnID);

	if(MapIter != mButtonMap.end())
	{
		//Button exist. Erase it.
		mButtonMap.erase(BtnID);
		return true;
	}else
	{
		//Button not found!
		return false;
	}
}

//Get the button object owned by this winframe by ID.
CButton* CWinFrame::GetButtonObject(unsigned int BtnID)
{
	//See if we found the object here.
	map<unsigned int, CButton*>::iterator MapIter = mButtonMap.find(BtnID);

	if(MapIter != mButtonMap.end())
	{
		//Ok, we've found it. Let's return it.
		return MapIter->second;
	}else
	{
		//Not found, return NULL.
		return NULL;
	}
}

//Tell the WinFrame to remember this edit object.
bool CWinFrame::AddEditObject(HWND hWnd, CEdit* EditObjPtr)
{
	//See if we found the object here.
	map<HWND, CEdit*>::iterator MapIter = mEditMap.find(hWnd);

	if(MapIter != mEditMap.end())
	{
		//Oops! Object exist! User is a monkey
		return false;
	}else
	{
		//Add this Edit object into map.
		mEditMap[hWnd] = EditObjPtr;
		return true;
	}
}

//Remove a edit object from the editmap.
bool CWinFrame::RemoveEditObject(HWND hWnd)
{
	//See if we found the object here.
	map<HWND, CEdit*>::iterator MapIter = mEditMap.find(hWnd);

	if(MapIter != mEditMap.end())
	{
		//Edit exist. Erase it.
		mEditMap.erase(hWnd);
		return true;
	}else
	{
		//Object not found.
		return false;
	}
}

//This static window procdure is a fake one, only a hack for wc.lpfnWndProc use. 
LRESULT CALLBACK CWinFrame::StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//now pass the parameters to our true wndproc in object.

	//Get the CWinFrame ptr stored in CWinFrameMgr.
	CWinFrame* tmpWinFrame = CWinManager::GetInstance()->GetWinFrame(hWnd);

	//Check if it's NULL.
	if(tmpWinFrame)
	{
		//Found it, pass parameters to our true WndProc.
		return tmpWinFrame->WndProc(hWnd, msg, wParam, lParam);
	}else//Oops! No hwnd found in the map.
	{
		//Let's try add hwnd first
		if(CWinManager::GetInstance()->AddWinFrameHWND(hWnd))
		{
			//Succsee! The hwnd and a waiting WinFrame should be match in the map now.
			//Let's try get our TRUE wndproc again.
			CWinFrame* tmpWinFrameReload = CWinManager::GetInstance()->GetWinFrame(hWnd);
			if(tmpWinFrameReload)
			{
				//Oh..Ya! 
				return tmpWinFrameReload->WndProc(hWnd, msg, wParam, lParam);
			}else
			{
				//Oops! Something must be wrong.
				//Maybe write an Error log here.
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}
		}else
		{
			//Oops! Something must be wrong.
			//Maybe write an Error log here.
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
    }
}

//This is our true wndproc.
LRESULT CALLBACK CWinFrame::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//we'll do our objective window procdure dirty work here..
	
	//I dont want to do this but..we need our handle as soon as possible.
	if(!mhWnd)
	{
	//	//Identify ourself.
		mhWnd = hWnd;
	}

	//The following block process user assign customproc callback.
	//================================================================================
	if(mCustomProc)
	{
		//Customprov callBack function found. Let's do it.
		WinMsgPackage MsgPkg(hWnd, msg, wParam, lParam);
		mCustomProc(MsgPkg);
	}
	//================================================================================

	//The following block process our callback message map.
	//================================================================================
	//See if we can find any specific msg callback function here...
	map<UINT, function<void (const WinMsgPackage&)> >::iterator MapIter = mMessageMap.find(msg);
	//If we found the callback event.
	if(MapIter != mMessageMap.end())
	{
		//CallBack function found. Let's do it.
		WinMsgPackage MsgPkg(hWnd, msg, wParam, lParam);
		//Call every callback functions in the vector!
		MapIter->second(MsgPkg);
	}
	//================================================================================

	//Here we do all buttons' onclick callback. (button on this frame)
	if(msg == WM_COMMAND)
	{
		//Let's try find the button in our map.
		map<unsigned int, CButton*>::iterator BtnMapIter = mButtonMap.find(static_cast<unsigned int>(wParam));
		
		//Found it. Call the onclick callback.
		if(BtnMapIter != mButtonMap.end())
		{
			BtnMapIter->second->EvokeOnClick();
		}
	}

	//Special case: We'll close this app once all CWinFrame is destroyed.
	if(msg == WM_DESTROY)
	{
		//Clear the callback Event map.
		mMessageMap.clear();
		//Remove this WinFrame from Mgr.
		CWinManager::GetInstance()->RemoveWinFrame(hWnd);
		//Check if Mgr is empty. If true, post the quit message.
		if(CWinManager::GetInstance()->IsWinframeMapEmpty())
		{
			//Once the last window is close, terminate this program.
			PostQuitMessage(0);
		}
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//an example function.
void CWinFrame::CenterWindow( HWND hwnd )
{
    RECT rc ;
    
    GetWindowRect ( hwnd, &rc ) ;
    
    SetWindowPos( hwnd, 0, 
        (GetSystemMetrics(SM_CXSCREEN) - rc.right)/2,
        (GetSystemMetrics(SM_CYSCREEN) - rc.bottom)/2,
         0, 0, SWP_NOZORDER|SWP_NOSIZE );
}
