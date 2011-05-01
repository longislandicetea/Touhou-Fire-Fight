#ifndef EditH
#define EditH

#include <windows.h>
#include <string>

using namespace std;

//Forward declare of WinFrame.
class CWinFrame;

//Edit control class. A simple input interface.
class CEdit
{
	public:
		//Default constructor.
		CEdit();

		//Simple constructor.
		CEdit(CWinFrame* ParientFrame);

		//Advance constructor.
		CEdit(CWinFrame* ParientFrame, unsigned int posX, unsigned int posY, unsigned int Width);

		//Destructor.
		~CEdit();

		//Simple load.
		bool Load(CWinFrame* ParientFrame);

		//advance load.
		bool Load(CWinFrame* ParientFrame, unsigned int posX, unsigned int posY, unsigned int Width);

		//Unload this edit object.
		bool UnLoad();

		//Set text.
		void SetText(const string& strIn);

		//Get text string of this edit.
		string GetText();

		//Set the edit position.
		void SetPosition(int PosX, int PosY);

	private:
        //Current position.
		unsigned int mPosX;
		unsigned int mPosY;

	    //Component size.
		unsigned int mWidth;
		unsigned int mHeight;

		//handle of this Edit object.
		HWND mhWnd;

		//A point to remember parent object.
		CWinFrame* mParentFrame;

		//ID of this object.
		unsigned int mEditID;

		//Edit ID generator.
		static unsigned int EDIT_ID_SEQUENCE;

};

#endif
