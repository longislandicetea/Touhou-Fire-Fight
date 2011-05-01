#ifndef ButtonH
#define ButtonH

#include <windows.h>
#include <functional>
#include "Text.h"

using namespace std;
using namespace std::tr1;

//Farward declare.
class CWinFrame;

//Button class.
class CButton
{
	public:
		//Default onstructor.
		CButton();

		//Simple constructor.
		CButton(CWinFrame* ParientFrame);

		//Advance constructor.
		CButton(CWinFrame* ParientFrame, unsigned int PosX, unsigned int PosY, unsigned int Width, unsigned int Height, string Text = "l337 87n");

		//Advance constructor.
		CButton(CWinFrame* ParientFrame, string Text);

		//Destructor.
		~CButton();

		//Simple load: Load the button with default value.
		bool Load(CWinFrame* ParientFrame);

		//Advance load: Load the button with custom value.
		bool Load(CWinFrame* ParientFrame, unsigned int PosX, unsigned int PosY, unsigned int Width, unsigned int Height, string Text = "l337 87n");

		//Advance load: Load the button with custom value.
		bool Load(CWinFrame* ParientFrame, string Text);

		//Unload this button.
		bool UnLoad();

		//Set button position.
		void SetPosition(unsigned int PosX, unsigned int PosY);

		//Set button size.
		void SetSize(unsigned int Width, unsigned int Height);

		//Set button size.
		void SetText(string Text);

		//Set click callback.
		bool SetOnClick(function<void (void)> CallBack);

		//Clear the onclick callback.
		void ClearOnClick();

		//Call the method.
		void EvokeOnClick();

	private:
		//Here's our fake Button Wnd Proc
		static LRESULT WINAPI StaticButtonWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

		//This is our true ButtonProc function.
		LRESULT WINAPI ButtonWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

	private:
		//Window handle of this object.
		HWND mhWnd;

		//Current position.
		unsigned int mPosX;
		unsigned int mPosY;

		//Button size.
		unsigned int mWidth;
		unsigned int mHeight;

		//Current button text.
		string mButtonText;

		//Parent WinFrame handle.
		CWinFrame* mParentFrame;

		//ID of this object.
		unsigned int mButtonID;

		//Remember user define on click callback function here.
		function<void (void)> mOnClickCallBack;

		//Here we save the sub class returned origin wndproc.
		WNDPROC OriginWndProc;

		//Button ID generator.
		static unsigned int BUTTON_ID_SEQUENCE;
};

#endif