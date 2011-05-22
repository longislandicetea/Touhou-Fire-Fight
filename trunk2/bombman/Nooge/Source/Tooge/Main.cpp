#include <windows.h>
#include <tchar.h>

#include "WinManager.h"
#include "ThreadManager.h"

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
	App *app = &App::Inst();
		
	CWinManager::GetInstance()->LetsRock();

	//****************** [User Implementation] ******************
	// Delete your form class here or you'll get some memory leak.
	//***********************************************************
	delete app;
		
	CWinManager::GetInstance()->DeleteInstance();
	CThreadManager::GetInstance()->DeleteInstance();
		
	return (0);    
}

