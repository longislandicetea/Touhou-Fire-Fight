//---------------------------------------------------------------------------
#ifndef WinFrameH
#define WinFrameH

#include <windows.h>
#include <functional>
#include <map>

using namespace std;
using namespace std::tr1;
using namespace std::tr1::placeholders;

//WndProc message Package.
struct WinMsgPackage
{
	//Constructor of the structure.
	WinMsgPackage(HWND hwndIn, UINT msgIn, WPARAM wParamIn, LPARAM lParamIn)
		:hwnd(hwndIn), msg(msgIn), wParam(wParamIn), lParam(lParamIn)
	{
		//Inisitalize all data member above.
	}

	//These are params of WndProc
	HWND hwnd;
	UINT msg;
	WPARAM wParam;
	LPARAM lParam;
};
//A function pointer type which stores client input callback function.
typedef function<void (const WinMsgPackage&)> CallbackMsgEvent;

//Forward declare CText class.
class CText;

//Forward declare CButtin class.
class CButton;

//Forward declare CEdit class.
class CEdit;

//Our grand window class.
class CWinFrame
{
	public:
		//Default constructor.
		CWinFrame();

		//Simple constructor.
		CWinFrame(string Name, string title);

		//Advance constructor.
		CWinFrame(string Name, string title, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height);

		//Destructor
		virtual ~CWinFrame();

		//Load a default WindFrame.
		bool Load(string Name, string title);

		//Load a WinFrame by parameters.
		bool Load(string Name, string title, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height);

		//Unload a WinFrame.
		bool Unload();

		//Get the handle of this WinFrame object.
		HWND gethWnd();

		//Add an Event callback to specific WM msg.
		bool AddCallBackEvent(UINT uintIn, const function<void (const WinMsgPackage&)>& CallbackMsgEventIn);

		//Remove an Event callback to specific WM msg.
		bool RemoveCallBackEvent(UINT uintIn);

		//Add a CustomProc callback that callbacks [Every] wndproc msg.
		bool AssignCustomProc(const function<void (const WinMsgPackage&)>& CallbackMsgEventIn);

		//Clear Current set CustomProc callback
		bool ClearCustomProc();

		//========================= [Text Object] =============================
		//Tell the WinFrame to remember this Text object.
		bool AddTextObject(HWND hWnd, CText* TextObjPtr);

		//Remove a text object from the textmap.
		bool RemoveTextObject(HWND hWnd);
		//=====================================================================

		//======================== [Button object] ============================
		//Tell the WinFrame to remember this Button object.
		bool AddButtonObject(unsigned int, CButton* BtnObjPtr);

		//Remove a button object from the map.
		bool RemoveButtonObject(unsigned int BtnID);

		//Get the button object owned by this winframe by ID.
		CButton* GetButtonObject(unsigned int);
		//=====================================================================

		//========================= [Edit object] =============================
		//Tell the WinFrame to remember this edit object.
		bool AddEditObject(HWND hWnd, CEdit* EditObjPtr);

		//Remove a edit object from the editmap.
		bool RemoveEditObject(HWND hWnd);
		//=====================================================================

	private:
		//This is a hack for WNDCLASS use.
		static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		//This is our true wndproc for this object.
		LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		//A test function: place the window to screen center.
		void CenterWindow(HWND hwnd);

	private:
		//window hwnd of this object.
		HWND mhWnd;

		//Position.
		unsigned int mPosX;
		unsigned int mPosY;

		//Size.
		unsigned int mWidth;
		unsigned int mHeight;

		//Declare our message map.
		//When client input a callback function. We actually store it inside this.
		map<UINT, function<void (const WinMsgPackage&)> > mMessageMap;

		//CustomProc callback event. This things call back every msg.
		function<void (const WinMsgPackage&)> mCustomProc;

		//CButton object map.
		map<unsigned int, CButton*> mButtonMap;

		//CText object map.
		map<HWND, CText*> mTextMap;

		//CEdit object map.
		map<HWND, CEdit*> mEditMap;
};

#endif
