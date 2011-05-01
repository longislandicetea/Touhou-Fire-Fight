#ifndef CoreH
#define CoreH
#include <windows.h>

class CMooge;

//Engine core functionality.
class CCore
{
	friend CMooge;

	public:
		//Initialize engine.
		bool Initial(void* hWnd);

		//Destroy engine.
		bool Destroy();	

		//Check if the core been initialed.
		bool IsInitial();

	private:
		//Default constructor.
		CCore();

		//Default destructor.
		~CCore();

		// Select the pixel format for a given device context 
		//(Reference from OpenGL Super Bible 4th)
		void SetDCPixelFormat(HDC hDC);

		//Ref from opengl super bible.
		//Setup fontlist.
		void SetupFont(HDC hDC);

		//Get font list. (used by 2DText currently)
		unsigned int GetFontList();

	private:
		//Is the engine been initialized?
		bool mInitialed;
		//Permanent rendering context
		HGLRC mhRC;    
		//Private GDI device context
		HDC mhDC;      
		//Store render handle here.
		HWND mhWnd;
		//PixelFormat of this dc.
		int mPixelFormat;
		//FontList
		unsigned int mFontList;		
};

#endif