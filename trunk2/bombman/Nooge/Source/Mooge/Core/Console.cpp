#include "Console.h"
#include "2DText.h"

//Default constructor.
CConsole::CConsole(unsigned int ScreenWidth, unsigned int ScreenHeight, unsigned int FontHeight, unsigned FontWidth): mCurrentCommand(""), mCommander("[Mooge]:"),
	mLineCount(ScreenHeight/FontHeight), mLineCharCount(125), mActivate(false)
{
	unsigned int TextID = 0;
	for(unsigned int i = 1 ; i <= mLineCount ; i++)
	{
		mTextLineVec.push_back(new C2DText("", 0, i*FontHeight, ++TextID));
	}

	mTextLineVec[0]->SetText(mCommander + mCurrentCommand);
}

//Default destructor.
CConsole::~CConsole()
{
	//Delete all elements in C2DText vector.
	for (vector<C2DText*>::iterator TextVecIter = mTextLineVec.begin() ; TextVecIter != mTextLineVec.end() ; TextVecIter++)
	{
		delete *TextVecIter;
	}
	mTextLineVec.clear();

	//Delete all elements in command history.
	for (vector<string*>::iterator StrVecIter = mCommandHistory.begin() ; StrVecIter != mCommandHistory.end() ; StrVecIter++)
	{
		delete *StrVecIter;
	}
	mCommandHistory.clear();
}

//Draw console texts.
void CConsole::Draw(unsigned int FontList)
{
	for (vector<C2DText*>::iterator TextVecIter = mTextLineVec.begin() ; TextVecIter != mTextLineVec.end() ; TextVecIter++)
	{
		(*TextVecIter)->Draw(FontList);
	}
}

//Active the console.
void CConsole::Activate()
{
	mActivate = true;	
}

//Hide console.
void CConsole::Deactivate()
{
	mActivate = false;
}

//Is console activate?
bool CConsole::IsActivate()
{
	return mActivate;
}

//User Input.
void CConsole::Input(char c)
{
	//Return key
	if(c == 13)
	{
		mCurrentCommand.clear();
		mTextLineVec[0]->SetText(mCommander + mCurrentCommand);
		mTextLineVec[1]->SetText("Are you human?");
	}else if(c == 8)//Backspace key
	{
		if(mCurrentCommand.size() > 0)
		{
			mCurrentCommand.erase(--mCurrentCommand.end());
			mTextLineVec[0]->SetText(mCommander + mCurrentCommand);
		}		
	}else if(c == 9)//Tab key
	{

	}else if(c == 27)//Esc key
	{

	}else//Other key
	{
		mCurrentCommand.push_back(c);
		mTextLineVec[0]->SetText(mCommander + mCurrentCommand);
	}
}