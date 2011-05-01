
#include "Edit.h"
#include "WinFrame.h"

//Initialize button sequence.
unsigned int CEdit::EDIT_ID_SEQUENCE = 2000;

static const int DEFAULT_EDIT_POSX = 10;
static const int DEFAULT_EDIT_POSY = 10;
static const int DEFAULT_EDIT_WIDTH = 100;
static const int DEFAULT_EDIT_HEIGHT = 19;

//Default constructor.
CEdit::CEdit():mPosX(DEFAULT_EDIT_POSX), mPosY(DEFAULT_EDIT_POSY), mWidth(DEFAULT_EDIT_WIDTH), mHeight(DEFAULT_EDIT_HEIGHT), mhWnd(NULL), mParentFrame(NULL), mEditID(0)
{

}

//Simple constructor.
CEdit::CEdit(CWinFrame* ParientFrame):mPosX(DEFAULT_EDIT_POSX), mPosY(DEFAULT_EDIT_POSY), mWidth(DEFAULT_EDIT_WIDTH), mHeight(DEFAULT_EDIT_HEIGHT), mhWnd(NULL), mParentFrame(NULL), mEditID(0)
{
	//Load the object.
	Load(ParientFrame);
}

//Advance constructor.
CEdit::CEdit(CWinFrame* ParientFrame, unsigned int posX, unsigned int posY, unsigned int Width)
	:mPosX(posX), mPosY(posY), mWidth(Width), mHeight(DEFAULT_EDIT_HEIGHT), mhWnd(NULL), mParentFrame(NULL), mEditID(0)
{
	//Load the object.
	Load(ParientFrame);
}

//Destructor.
CEdit::~CEdit()
{
	//Simple way.
	UnLoad();
}

//Simple load.
bool CEdit::Load(CWinFrame* ParientFrame)
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
				mhWnd = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL
					, mPosX, mPosY, mWidth, mHeight, ParientFrame->gethWnd(), (HMENU)EDIT_ID_SEQUENCE, GetModuleHandle(NULL), 0);
				
				//Remember the EditID.
				mEditID = EDIT_ID_SEQUENCE;

				//Add one to ID generator.
				EDIT_ID_SEQUENCE++;

				//Set font to the edit control.
				HFONT hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Tohoma"));
				SendMessage(mhWnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(true, 0));

				//Add this object to its parent.
				ParientFrame->AddEditObject(mhWnd, this);

				//Remember parent.
				mParentFrame = ParientFrame;

				return true;
			}else
			{
				//ParentFrame hasnt been loaded yet!
				return false;
			}
		}else
		{
			//Oops! ParentFrame us NULL.
			return false;
		}
	}else
	{
		//Object has been loaded! User is a monkey.
		return false;
	}
}

//advance load.
bool CEdit::Load(CWinFrame* ParientFrame, unsigned int posX, unsigned int posY, unsigned int Width)
{
	//Check if the object has been created.
	if(mhWnd == NULL)
	{
		//Assign input param to members and call load.
		mPosX = posX;
		mPosY = posY;
		mWidth = Width;
		return Load(ParientFrame);
	}else
	{
		return false;
	}
}

//Unload this edit object.
bool CEdit::UnLoad()
{
	//Destroy the window if it's been loaded.
	if(mhWnd)
	{
		//Tell the parent to forget us.
		mParentFrame->RemoveEditObject(mhWnd);
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

//Set text.
void CEdit::SetText(const string& strIn)
{

}

//Get text string of this edit.
string CEdit::GetText()
{
	//Get text from Edit.
	char Text[255];
	GetDlgItemText(mParentFrame->gethWnd(), mEditID, Text, 255);

	//We need a string type to return.
	string EditStr(Text);
	return EditStr;
}

//Set the edit position.
void CEdit::SetPosition(int PosX, int PosY)
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
