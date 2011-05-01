//---------------------------------------------------------------------------
#ifndef WinManagerH
#define WinManagerH
#include <windows.h>
#include <map>

using namespace std;

//Forward declare the class.
class CWinFrame;

//Forward declare of button class.
class CButton;

//Singleton class, manage WinFrameProcMap which used by wndproc hack in WinFrame.cpp.
//Also manage the WINAPI message loop.
//Remember: suicide just before winmain end.
class CWinManager
{
	public:
		//Get the singlton instance.
		static CWinManager* GetInstance();

		//Start the WINAPI message loop.
		void LetsRock();

		//Self destroy the singlton instance.
		bool DeleteInstance();

		//---------------------------------- [WinFrame Manage Method] ------------------------------------
		//Add a WinFrame ptr to CWinManager.
		bool AddWinFrame(CWinFrame* WinFrame);

		//Add a HWND to CWinFrameMgr. CWinManager'll try match a WinFrame for the hwnd.
		bool AddWinFrameHWND(HWND hWnd);

		//Remove a WinFrame ptr from mWinFrameProcMap.
		bool RemoveWinFrame(HWND hWnd);

		//This function let the WM_DESTROY in WinFrame decide whether to PostQuitMessge(0).
		bool IsWinframeMapEmpty();

		//Search the mWinFrameProcMap for hWnd key value, if exist, return the associated WinFrame ptr.
		CWinFrame* GetWinFrame(HWND hWnd);
		//------------------------------------------------------------------------------------------------

		//---------------------------------- [Button Manage Method] --------------------------------------
		//Add a Button ptr to CWinManager.
		bool AddButton(CButton* Button);

		//Add a HWND to CWinManager. CWinManager'll try match a WinFrame for the hwnd.
		bool AddButtonHWND(HWND hWnd);

		//Remove a WinFrame ptr from mWinFrameProcMap.
		bool RemoveButton(HWND hWnd);

		//This function let the WM_DESTROY in WinFrame decide whether to PostQuitMessge(0).
		bool IsButtonMapEmpty();

		//Search the mWinFrameProcMap for hWnd key value, if exist, return the associated WinFrame ptr.
		CButton* GetButton(HWND hWnd);
		//------------------------------------------------------------------------------------------------

	private:
		//cant be new.
		CWinManager();

		//Cant be destroy.
		//Only self destroy is allow. See DeleteInstance();
		~CWinManager();

		//Try match the hwnd and WinFrame that is currently waiting.
		bool MatchWinFrameWaiter();

		//Try match the waiting button and hWnd.
		bool MatchButtonWaiter();

	private:
		//Singoeton instance here.
		static CWinManager* mInstance;

		//---------------------------- [WinFrame Manage variables] -----------------------------
		//This map associate each CWinFrame object with their hwnd.
		//When a WinFrame is Loaded, it store itself to this map.
		//Used by CWinFrame::StaticWndProc() to recognize which wndproc() it should call.
		static map<HWND, CWinFrame*> mWinFrameProcMap;

		//A CWinFrame hWnd temp that waiting for match.
		HWND mWinFramehWndWaiting;

		//A CWinFrame ptr temp that waiting for match.
		CWinFrame* mWinFrameWaiting;
		//--------------------------------------------------------------------------------------

		//----------------------------- [Button Manage variables] ------------------------------
		//A CButton object map. Just like mWinFrameProcMap.
		static map<HWND, CButton*> mButtonProcMap;

		//A CButton hWnd temp that waiting for match.
		HWND mButtonhWndWaiting;

		//A CButton ptr that waiting for match.
		CButton* mButtonWaiting;
		//--------------------------------------------------------------------------------------
};

//---------------------------------------------------------------------------
#endif
