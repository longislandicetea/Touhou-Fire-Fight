#ifndef AppOneH
#define AppOneH

#include "RenderForm.h"
#include "DebugForm.h"

//Our grand first step start here.
//AppOne: our testing project.
class CAppOne
{
	public:
		CAppOne();

		~CAppOne();

	private:
		void OnRenderFormCreate(const WinMsgPackage& MsgPack);
		void OnRenderFormDestroy(const WinMsgPackage& MsgPack);
		void OnRenderFormTimer(const WinMsgPackage& MsgPack);

		// Select the pixel format for a given device context 
		//(Reference from OpenGL Super Bible 4th)
		void SetDCPixelFormat(HDC hDC);
		void RenderScene();
		void IdleFunction();

	private:
		CDebugForm mDebugForm;

		CRenderForm mRenderForm;

	private:
		HGLRC mhRC;    // Permanent rendering context
		HDC mhDC;      // Private GDI device context

		//Square position and size
		float mRectPosX;
		float mRectPosY;
		float mRectSize;

		// Step size in x and y directions
		// (number of pixels to move each time)
		float mXstep;
		float mYstep;

		// Keep track of windows changing width and height
		float mRenderWindowWidth;
		float mRenderWindowHeight;

		int nPixelFormat;
};

#endif