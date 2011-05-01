#include "Button.h"
#include "WinFrame.h"
#include "WinManager.h"

//Initialize button sequence.
unsigned int CButton::BUTTON_ID_SEQUENCE = 1000000000;

static const int BUTTON_DEFAULT_POSX = 10;
static const int BUTTON_DEFAULT_POSY = 10;
static const int BUTTON_DEFAULT_WIDTH = 75;
static const int BUTTON_DEFAULT_HEIGHT = 25;

//Constructor.
CButton::CButton()
	:mhWnd(NULL), mButtonID(0), mParentFrame(NULL), OriginWndProc(NULL), 
	mPosX(BUTTON_DEFAULT_POSX), mPosY(BUTTON_DEFAULT_POSY), mWidth(BUTTON_DEFAULT_WIDTH), mHeight(BUTTON_DEFAULT_HEIGHT), mButtonText("l337 87n")
{

}

//Simple constructor.
CButton::CButton(CWinFrame* ParientFrame)
	:mhWnd(NULL), mButtonID(0), mParentFrame(NULL), OriginWndProc(NULL), 
	mPosX(BUTTON_DEFAULT_POSX), mPosY(BUTTON_DEFAULT_POSY), mWidth(BUTTON_DEFAULT_WIDTH), mHeight(BUTTON_DEFAULT_HEIGHT), mButtonText("l337 87n")
{
	//Simple way.
	Load(ParientFrame);
}

//Advance constructor.
CButton::CButton(CWinFrame* ParientFrame, unsigned int PosX, unsigned int PosY, unsigned int Width, unsigned int Height, string Text)
	:mhWnd(NULL), mButtonID(0), mParentFrame(ParientFrame), OriginWndProc(NULL), mPosX(PosX), mPosY(PosY), mWidth(Width), mHeight(Height), mButtonText(Text)
{
	//Simple way.
	Load(ParientFrame);
}

//Advance constructor.
CButton::CButton(CWinFrame* ParientFrame, string Text)
	:mhWnd(NULL), mButtonID(0), mParentFrame(NULL), OriginWndProc(NULL), 
	mPosX(BUTTON_DEFAULT_POSX), mPosY(BUTTON_DEFAULT_POSY), mWidth(BUTTON_DEFAULT_WIDTH), mHeight(BUTTON_DEFAULT_HEIGHT), mButtonText(Text)
{
	//Simple way.
	Load(ParientFrame);
}

//Destructor.
CButton::~CButton()
{
	//Simple.
	UnLoad();
}

//Simple load: Load the button with default value.
bool CButton::Load(CWinFrame* ParientFrame)
{
	if(ParientFrame != NULL)
	{
		if(ParientFrame->gethWnd() != NULL)
		{
			if(CWinManager::GetInstance()->AddButton(this))
			{	
				//Create our grand button window. We'll store the hwnd to class member.
				mhWnd = CreateWindow("Button", mButtonText.c_str(), WS_CHILD | WS_VISIBLE , mPosX, mPosY, mWidth, mHeight, ParientFrame->gethWnd(), (HMENU)BUTTON_ID_SEQUENCE, GetModuleHandle(NULL), 0);	

				//Remember the buttonID.
				mButtonID = BUTTON_ID_SEQUENCE;

				//Tell our parent to remember us.
				ParientFrame->AddButtonObject(BUTTON_ID_SEQUENCE, this);

				//Add current sequence.
				BUTTON_ID_SEQUENCE++;

				//Remember the parent WinFrame.
				mParentFrame = ParientFrame;			

				//Now this is a grand step. Subclass this button object so we got our own wndproc of this object.
				OriginWndProc = (WNDPROC)SetWindowLong(mhWnd, GWL_WNDPROC, (DWORD)StaticButtonWndProc);

				//Set font to the button.
				HFONT hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Tohoma"));
				SendMessage(mhWnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(true, 0));

				//Load success.
				return true;
			}else
			{
				//Oops, add button to manager failed!
				return false;
			}		
		}else
		{
			//Oops, parent is NULL.
			return false;
		}
	}else
	{
		//Oops, parent is NULL.
		return false;
	}	
}

//Load the button.
bool CButton::Load(CWinFrame* ParientFrame, unsigned int PosX, unsigned int PosY, unsigned int Width, unsigned int Height, string Text)
{
	//Check if the object has been created.
	if(mhWnd == NULL)
	{
		//Just remember these setting.
		mPosX = PosX;
		mPosY = PosY;
		mWidth = Width;
		mHeight = Height;
		mButtonText = Text;
		//Call default load.
		return Load(ParientFrame);
	}else
	{
		return false;
	}
}

//Advance load: Load the button with custom value.
bool CButton::Load(CWinFrame* ParientFrame, string Text)
{
	//Check if the object has been created.
	if(mhWnd == NULL)
	{
		//Just remember these setting.
		mPosX = BUTTON_DEFAULT_POSX;
		mPosY = BUTTON_DEFAULT_POSY;
		mWidth = BUTTON_DEFAULT_WIDTH;
		mHeight = BUTTON_DEFAULT_HEIGHT;
		mButtonText = Text;
		//Call default load.
		return Load(ParientFrame);
	}else
	{
		return false;
	}
}

//Unload this button.
bool CButton::UnLoad()
{
	//Destroy the window if it's been loaded.
	if(mhWnd)
	{
		//Tell the parent to forget us.
		mParentFrame->RemoveButtonObject(mButtonID);
		//Tell the WinManager to forget us.
		CWinManager::GetInstance()->RemoveButton(mhWnd);
		//Suicide.
		DestroyWindow(mhWnd);
		//Forget everything.
		mhWnd = NULL;
		mParentFrame = NULL;
		mOnClickCallBack = NULL;
		return true;
	}else
	{
		return false;
	}
}

//Set button position.
void CButton::SetPosition(unsigned int PosX, unsigned int PosY)
{
	//Just remember the input position.
	mPosX = PosX;
	mPosY = PosY;

	//only if the object been created.
	if(mhWnd != NULL)
	{
		//Set position and width/height.
		MoveWindow(mhWnd, mPosX, mPosY, mWidth, mHeight, true);
	}
}

//Set button size.
void CButton::SetSize(unsigned int Width, unsigned int Height)
{
	//Just remember the input position.
	mWidth = Width;
	mHeight = Height;

	//only if the object been created.
	if(mhWnd != NULL)
	{
		//Set position and width/height.
		MoveWindow(mhWnd, mPosX, mPosY, mWidth, mHeight, true);
	}
}

//Set button size.
void CButton::SetText(string Text)
{
	//Remember the text.
	mButtonText = Text;
	//only if the object has been created.
	if(mhWnd != NULL)
	{
		//Set text to the object.
		SendMessage(mhWnd, WM_SETTEXT, 0, (LPARAM)mButtonText.c_str()); 
	}
}

//Set click callback.
bool CButton::SetOnClick(function<void (void)> CallBack)
{
	//Check if it's set b4.
	if(mOnClickCallBack)
	{
		//Oops.
		return false;
	}else
	{
		//Just remember the function
		mOnClickCallBack = CallBack;
		return true;
	}
}

//Clear the onclick callback.
void CButton::ClearOnClick()
{
	//Forget the function.
	mOnClickCallBack = NULL;
}

//Call the method.
void CButton::EvokeOnClick()
{
	//Only if the function exist...
	if(mOnClickCallBack)
	{
		//Call the method.
		mOnClickCallBack();
	}
}

//Here's our fake Button Wnd Proc
LRESULT WINAPI CButton::StaticButtonWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	//Here we seek our parent to identify our true object. Use it to call the true ButtonWndProc.
	CButton* ThisBtn = CWinManager::GetInstance()->GetButton(hWnd);

	//If we found the button, call the true button wndproc!
	if(ThisBtn != NULL)
	{
		//Found it!
		return ThisBtn->ButtonWndProc(hWnd, nMsg, wParam, lParam);
	}else//Oops, button not found.
	{
		//Let's try add this hWnd.
		if(CWinManager::GetInstance()->AddButtonHWND(hWnd))
		{
			//Succsee! The hwnd and a waiting Button should be match in the map now.
			//Let's try get our TRUE wndproc again.
			CButton* tmpButtonReload = CWinManager::GetInstance()->GetButton(hWnd);
			if(tmpButtonReload)
			{
				//Oh..Ya! 
				return tmpButtonReload->ButtonWndProc(hWnd, nMsg, wParam, lParam);
			}else
			{
				//Oops! Something must be wrong.
				//Maybe write an Error log here.
				return DefWindowProc(hWnd, nMsg, wParam, lParam);
			}
		}else
		{
			//Oops! Something must be wrong.
			//Maybe write an Error log here.
			return DefWindowProc(hWnd, nMsg, wParam, lParam);
		}
	}
}

//This is our true ButtonProc function.
LRESULT WINAPI CButton::ButtonWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	//This is our button subclass wndproc.
	
	//We could handle our custom button proc here.

	return CallWindowProc(static_cast<WNDPROC>(OriginWndProc), hWnd, nMsg, wParam, lParam);
}
