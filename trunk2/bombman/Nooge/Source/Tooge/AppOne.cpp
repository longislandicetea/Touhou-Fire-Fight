#include "AppOne.h"

#include <gl/GL.h>
#include <gl/GLU.h>

CAppOne::CAppOne():mhRC(NULL), mhDC(NULL)
{
	//Listening all event here.
	mRenderForm.AddCallBackEvent(WM_CREATE, bind(&CAppOne::OnRenderFormCreate, this, _1));
	mRenderForm.AddCallBackEvent(WM_DESTROY, bind(&CAppOne::OnRenderFormDestroy, this, _1));
	mRenderForm.AddCallBackEvent(WM_TIMER, bind(&CAppOne::OnRenderFormTimer, this, _1));

	//Proceed load windows.
	mRenderForm.Load("AppOne rendering form", 40, 50, 800, 600);
	mDebugForm.Load("Debug");

	//Square position and size
	mRectPosX = 0.0f;
	mRectPosY = 0.0f;
	mRectSize = 25;

	// Step size in x and y directions
	// (number of pixels to move each time)
	mXstep = 1.0f;
	mYstep = 1.0f;

	// Keep track of windows changing width and height
	mRenderWindowWidth = 800;
	mRenderWindowHeight = 600;
}

CAppOne::~CAppOne()
{
	mDebugForm.Unload();
	mRenderForm.Unload();
}

void CAppOne::OnRenderFormCreate(const WinMsgPackage& MsgPack)
{
	//When renderform create..

	// Store the device context
	mhDC = GetDC(MsgPack.hwnd);
	// Select the pixel format
	SetDCPixelFormat(mhDC);
	// Create the rendering context and make it current
	mhRC = wglCreateContext(mhDC);
	wglMakeCurrent(mhDC, mhRC);

	// Set Viewport to window dimensions
	glViewport(0, 0, (GLsizei)mRenderWindowWidth, (GLsizei)mRenderWindowHeight);
	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, 800.0, 0.0, 600.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Create a timer that fires 30 times a second
	SetTimer(MsgPack.hwnd, 33, 1, NULL);
}

void CAppOne::OnRenderFormDestroy(const WinMsgPackage& MsgPack)
{
	// Kill the timer that we created
	KillTimer(MsgPack.hwnd, 101);
	// Deselect the current rendering context and delete it
	wglMakeCurrent(mhDC,NULL);
	wglDeleteContext(mhRC);
	// Tell the application to terminate after the window
	// is gone.
	PostQuitMessage(0);
}

void CAppOne::OnRenderFormTimer(const WinMsgPackage& MsgPack)
{
	IdleFunction();
	RenderScene();
	SwapBuffers(mhDC);

	//Print rect position.
	mDebugForm.SetPosXValue(static_cast<int>(mRectPosX));
	mDebugForm.SetPosYValue(static_cast<int>(mRectPosY));
}

void CAppOne::RenderScene()
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);
	// Set current drawing color to red
	//         R     G     B
	glColor3f(0.0f, 1.0f, 1.0f);
	// Draw a filled rectangle with current color
	glRectf(mRectPosX, mRectPosY, mRectPosX + mRectSize, mRectPosY + mRectSize);

	glBegin(GL_LINE_STRIP);
		glVertex2f(100.0, 100.0);
		glVertex2f(100.0, -100.0);
		glVertex2f(-100.0, -100.0);
		glVertex2f(-100.0, 100.0);
	glEnd();
}

void CAppOne::IdleFunction()
{
	// Reverse direction when you reach left or right edge
	if(mRectPosX > mRenderWindowWidth - mRectSize || mRectPosX < 0)
		mXstep = -mXstep;
	// Reverse direction when you reach top or bottom edge
	if(mRectPosY > mRenderWindowHeight -mRectSize || mRectPosY < 0)
		mYstep = -mYstep;
	// Actually move the square
	mRectPosX += mXstep;
	mRectPosY += mYstep;
	// Check bounds. This is in case the window is made
	// smaller while the rectangle is bouncing and the
	// rectangle suddenly finds itself outside the new
	// clipping volume
	if(mRectPosX > (mRenderWindowWidth - mRectSize + mXstep))
		mRectPosX = mRenderWindowWidth - mRectSize - 1;
	else if(mRectPosX < -(mRenderWindowWidth + mXstep))
		mRectPosX = - mRenderWindowWidth - 1;
	if(mRectPosY > (mRenderWindowHeight + mYstep))
		mRectPosY = mRenderWindowHeight - 1;
	else if(mRectPosY < -(mRenderWindowHeight - mRectSize + mYstep))
		mRectPosY = -mRenderWindowHeight + mRectSize - 1;
}

// Select the pixel format for a given device context
void CAppOne::SetDCPixelFormat(HDC hDC)
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
		nPixelFormat = ChoosePixelFormat(hDC, &pfd);
		// Set the pixel format for the device context
		SetPixelFormat(hDC, nPixelFormat, &pfd);
}