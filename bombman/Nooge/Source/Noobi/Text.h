#ifndef TextH
#define TextH

#include <windows.h>
#include <string>

using namespace std;

//Forward declare of WinFrame.
class CWinFrame;

//This is a Text class.
//Currently using Tohoma as default font. Size = 15;
class CText
{
	public:
		//Default constructor: doesnt create anything. Only initialize members.
		CText();

		//Simple constructor: create a text to specified WinFrame using [default] values.
		CText(CWinFrame* ParientFrame);

		//Advance constructor: create a text to specified WinFrame using [custom] values.
		CText(CWinFrame* ParientFrame, string strIn, unsigned int posX, unsigned int posY);

		//Destructor
		~CText();

		//Simple load: Load the text to specified WinFrame using [default] values.
		bool Load(CWinFrame* ParientFrame);

		//Advance load: Load the text to specified WinFrame using [custom] values.
		bool Load(CWinFrame* ParientFrame, const string& strIn, unsigned int posX, unsigned int posY);

		//Unload this text object.
		bool UnLoad();

		//Set text.
		void SetText(const string& strIn);

		//Set text(int version).
		void SetText(const int& IntIn);

		//Set the text position.
		void SetPosition(int PosX, int PosY);	

	private:
		//handle of this text object.
		HWND mhWnd;

		//A point to remember parent object.
		CWinFrame* mParentFrame;

		//Current displaying text.
		string mCurrentStr;

		//Font of this text.
		HFONT mFont;

		//Font size.
		unsigned int mFontSize;

		//Current position.
		unsigned int mPosX;
		unsigned int mPosY;
};

#endif
