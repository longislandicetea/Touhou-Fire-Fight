#include "Text.h"
#include "WinFrame.h"
#include <sstream>

static const int DEFAULT_TEXT_POSX = 10;
static const int DEFAULT_TEXT_POSY = 10;

//Default constructor: doesnt create anything. Only initialize members.
CText::CText():mCurrentStr("Default Text"), mFontSize(15), mPosX(DEFAULT_TEXT_POSX), mPosY(DEFAULT_TEXT_POSY), mhWnd(NULL), mParentFrame(NULL)
{
	//Default font.
	mFont = CreateFont(mFontSize, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Tohoma"));
}

//Simple constructor: create a text to specified WinFrame using [default] values.
CText::CText(CWinFrame* ParientFrame):mCurrentStr("Default Text"), mFontSize(15), mPosX(DEFAULT_TEXT_POSX), mPosY(DEFAULT_TEXT_POSY), mhWnd(NULL), mParentFrame(NULL)
{
	//Default font.
	mFont = CreateFont(mFontSize, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Tohoma"));
	//Load the object.
	Load(ParientFrame);
}

//Advance constructor: create a text to specified WinFrame using [custom] values.
CText::CText(CWinFrame* ParientFrame, string strIn, unsigned int posX, unsigned int posY)
	:mCurrentStr(strIn), mFontSize(15), mPosX(posX), mPosY(posY), mhWnd(NULL), mParentFrame(NULL)
{
	//Default font.
	mFont = CreateFont(mFontSize, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Tohoma"));
	//Load the object.
	Load(ParientFrame);
}

//Destructor
CText::~CText()
{
	//Simple.
	UnLoad();
}

//Load the text to specify WinFrame
bool CText::Load(CWinFrame* ParientFrame)
{
	//Check if the object has been created.
	if(mhWnd == NULL)
	{
		//Do remember to anti-fool.
		if(ParientFrame != NULL)
		{
			if(ParientFrame->gethWnd() != NULL)
			{
				//Create the text object.
				mhWnd = CreateWindow("Static", mCurrentStr.c_str(), WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 0, 0, 0, ParientFrame->gethWnd(), NULL, GetModuleHandle(NULL), 0);

				//Set font.
				SendMessage(mhWnd, WM_SETFONT, (WPARAM)mFont, MAKELPARAM(true, 0));

				//Let try find out the object width/height in pixels.
				SIZE TextSize;
				if(GetTextExtentPoint32(GetDC(mhWnd), mCurrentStr.c_str(), mCurrentStr.length(), &TextSize))
				{
					//Set position and width/height.
					MoveWindow(mhWnd, mPosX, mPosY, TextSize.cx, TextSize.cy, true);
				}

				//Add this object to its parent.
				ParientFrame->AddTextObject(mhWnd, this);

				//Remember parent.
				mParentFrame = ParientFrame;

				//Now we should have a text in ParientFrame.
				return true;
			}else
			{
				return false;
			}
		}else
		{
			return false;
		}
	}else
	{
		return false;
	}
}

//Advance load: Load the text to specified WinFrame using [custom] values.
bool CText::Load(CWinFrame* ParientFrame, const string& strIn, unsigned int posX, unsigned int posY)
{
	//Check if the object has been created.
	if(mhWnd == NULL)
	{
		//Assign input param to members and call load.
		mCurrentStr = strIn;
		mPosX = posX;
		mPosY = posY;
		//Load the window.
		return Load(ParientFrame);
	}else
	{
		return false;
	}
}

//Unload this text object.
bool CText::UnLoad()
{
	//Destroy the window if it's been loaded.
	if(mhWnd)
	{
		//Tell the parent to forget us.
		mParentFrame->RemoveTextObject(mhWnd);
		//Suicide.
		DestroyWindow(mhWnd);
		//Forget everything.
		mhWnd = NULL;
		mParentFrame = NULL;
		return true;
	}else
	{
		return false;
	}
}

//Set a text to display.
void CText::SetText(const string& strIn)
{
	//Just remember this str.
	mCurrentStr = strIn;

	//only if the object been created.
	if(mhWnd != NULL)
	{
		//Refresh the width of this object.
		SIZE TextSize;
		if(GetTextExtentPoint32(GetDC(mhWnd), mCurrentStr.c_str(), mCurrentStr.length(), &TextSize))
		{
			//Set position and width/height.
			MoveWindow(mhWnd, mPosX, mPosY, TextSize.cx, TextSize.cy, true);
		}

		//Set text to the object.
		SendMessage(mhWnd, WM_SETTEXT, 0, (LPARAM)mCurrentStr.c_str());
	}
}

//Set text(int version).
void CText::SetText(const int& IntIn)
{
	//Just remember this str.
	stringstream converter;
	converter << IntIn;
	mCurrentStr = converter.str();

	//only if the object been created.
	if(mhWnd != NULL)
	{
		//Refresh the width of this object.
		SIZE TextSize;
		if(GetTextExtentPoint32(GetDC(mhWnd), mCurrentStr.c_str(), mCurrentStr.length(), &TextSize))
		{
			//Set position and width/height.
			MoveWindow(mhWnd, mPosX, mPosY, TextSize.cx, TextSize.cy, true);
		}

		//Set text to the object.
		SendMessage(mhWnd, WM_SETTEXT, 0, (LPARAM)mCurrentStr.c_str());
	}
}

//Set the text position.
void CText::SetPosition(int PosX, int PosY)
{
	//Just remember the input position.
	mPosX = PosX;
	mPosY = PosY;

	//only if the object been created.
	if(mhWnd != NULL)
	{
		//Refresh the width of this object.
		SIZE TextSize;
		if(GetTextExtentPoint32(GetDC(mhWnd), mCurrentStr.c_str(), mCurrentStr.length(), &TextSize))
		{
			//Set position and width/height.
			MoveWindow(mhWnd, mPosX, mPosY, TextSize.cx, TextSize.cy, true);
		}
	}
}