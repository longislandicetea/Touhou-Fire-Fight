#include <windows.h>
#include <tchar.h>

#include "WinManager.h"
#include "ThreadManager.h"

#include "TestForm.h"
#include "AppOne.h"
#include "AppTwo.h"
#include "App.h"

//#include <vld.h>

//use common controls available on different windows OS'
//These macro let us create GUI that match current system theme.
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	    //CTestForm* mTest = new CTestForm("TestForm", "TestForm", 30, 60, 150, 220);
		//CAppOne* AppOne = new CAppOne();
		//CAppTwo* AppTwo = new CAppTwo();

		App *app = &App::Inst();
		//***********************************************************

		//[Dont Modify This]: This start our grand windows msg loop.
		CWinManager::GetInstance()->LetsRock();

		//****************** [User Implementation] ******************
		// Delete your form class here or you'll get some memory leak.
		//***********************************************************
			
		//delete mTest;	
		//delete AppOne;
		delete app;
		//***********************************************************

		//[Dont Modify This]: This delete CWinManager EVIL singleton Instance.
		CWinManager::GetInstance()->DeleteInstance();
		//[Dont Modify This]: This delete CThreadManager EVIL singleton Instance.
		CThreadManager::GetInstance()->DeleteInstance();

	return (0);
}

