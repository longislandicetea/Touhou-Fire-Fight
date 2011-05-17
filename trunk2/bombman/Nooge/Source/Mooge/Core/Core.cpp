#include "Core.h"
#include <gl/GL.h>
#include <gl/GLU.h>

//Default constructor.
CCore::CCore(): mInitialed(false), mhRC(0), mhDC(0), mFontList(0)
{

}

//Default destructor.
CCore::~CCore()
{

}

//Initialize engine.
bool CCore::Initial(void* hWnd)
{
	//Anti-fool.
	if(mInitialed || hWnd == NULL)
	{
		return false;
	}else
	{
		//Remember the window handle.
		// Store the device context
		mhDC = GetDC(static_cast<HWND>(hWnd));
		// Select the pixel format
		SetDCPixelFormat(mhDC);
		// Create the rendering context and make it current
		mhRC = wglCreateContext(mhDC);
		wglMakeCurrent(mhDC, mhRC);

		//Calculate window width and height.
		RECT ClientRect;
		GetClientRect(static_cast<HWND>(hWnd), &ClientRect);
		int ClientWidth = ClientRect.right - ClientRect.left;
		int ClientHeight = ClientRect.bottom - ClientRect.top;

		// Set Viewport to window dimensions
		glViewport(0, 0, ClientWidth, ClientHeight);
		// Reset coordinate system
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//aspectRatio
		float aspectRatio = static_cast<float>(ClientWidth) / static_cast<float>(ClientHeight);

		//glOrtho(-ClientWidth/2, ClientWidth/2, -ClientHeight/2, ClientHeight/2, 1000.0, -1000.0);
		gluPerspective(50.0, aspectRatio, 1.0, 1000.0);
		//gluOrtho2D(0, ClientWidth, ClientHeight, 0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Setup font.
		SetupFont(mhDC);

		//Test Line smooth
		//glEnable(GL_LINE_SMOOTH);
		//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		//glEnable(GL_BLEND);
		glEnable (GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);

		//Set initial flag.
		mInitialed = true;

		return true;
	}
}

//Destroy engine.
bool CCore::Destroy()
{
	if(mInitialed)
	{
		// Deselect the current rendering context and delete it
		wglDeleteContext(mhRC);
		wglMakeCurrent(mhDC, NULL);
		//Foeget everything.
		mhWnd = NULL;
		mPixelFormat = 0;
		mInitialed = false;
		return true;
	}else
	{
		return false;
	}
}

//Check if the core been initialed.
bool CCore::IsInitial()
{
	return mInitialed;
}

// Select the pixel format for a given device context 
//(Reference from OpenGL Super Bible 4th)
void CCore::SetDCPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), // Size of this structure
		1,                             // Version of this structure
		PFD_DRAW_TO_WINDOW |           // Draw to window (not to bitmap)
		PFD_SUPPORT_OPENGL |           // Support OpenGL calls in window
		PFD_DOUBLEBUFFER,              // Double-buffered mode
		PFD_TYPE_RGBA,                 // RGBA color mode
		32,                            // Want 32-bit color
		0,0,0,0,0,0,                   // Not used to select mode
		0,0,                           // Not used to select mode
		0,0,0,0,0,                     // Not used to select mode
		16,                            // Size of depth buffer
		0,                             // Not used here
		0,                             // Not used here
		PFD_MAIN_PLANE,                             // Not used here
		0,                             // Not used here
		0,0,0 };                       // Not used here
		// Choose a pixel format that best matches that described in pfd
		mPixelFormat = ChoosePixelFormat(hDC, &pfd);
		// Set the pixel format for the device context
		SetPixelFormat(hDC, mPixelFormat, &pfd);
}

void CCore::SetupFont(HDC hDC)
{
	// Set up the font characteristics
	HFONT hFont;
	//GLYPHMETRICSFLOAT agmf[128]; // Throw away
	LOGFONTA logfont;
	logfont.lfHeight = -12;
	logfont.lfWidth = 0;
	logfont.lfEscapement = 0;
	logfont.lfOrientation = 0;
	logfont.lfWeight = FW_NORMAL;
	logfont.lfItalic = FALSE;
	logfont.lfUnderline = FALSE;
	logfont.lfStrikeOut = FALSE;
	logfont.lfCharSet = ANSI_CHARSET;
	logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logfont.lfQuality = DEFAULT_QUALITY;
	logfont.lfPitchAndFamily = DEFAULT_PITCH;
	strcpy(logfont.lfFaceName, "DotumChe");
	// Create the font and display list
	hFont = CreateFontIndirectA(&logfont);
	SelectObject(hDC, hFont);
	// Create display lists for glyphs 0 through 128 with 0.1 extrusion
	// and default deviation. The display list numbering starts at 1000
	// (it could be any number).
	mFontList = glGenLists(128);
	//wglUseFontOutlines(hDC, 0, 128, mFontList, 0.0f, 0.5f,
	//	WGL_FONT_POLYGONS, agmf);
	wglUseFontBitmaps(hDC, 0, 128, mFontList);
	DeleteObject(hFont);
}

//Get font list. (used by 2DText currently)
unsigned int CCore::GetFontList()
{
	return mFontList;
}