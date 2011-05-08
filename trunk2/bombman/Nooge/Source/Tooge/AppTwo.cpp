#include "AppTwo.h"
#include <windows.h>
#include "RenderForm.h"
#include "Mooge.h"
#include "Core.h"
#include "PrimitiveManager.h"
#include "Line.h"
#include "CameraManager.h"
#include "Camera.h"
#include "2DText.h"
#include "TextManager.h"
#include "Console.h"

#include "jpeglib.h"

CAppTwo::CAppTwo(): CThread(true), mMouseCaptured(false),
	mRotBase(static_cast<float>(0.05)), mRotAcc(static_cast<float>(0.001)), mRenderForm(NULL), mMooge(NULL), mMainCamera(NULL)
{
	for(int i = 0 ; i < MOVEKEYTYPE ; i ++)
	{
		mKeyTrigger[i] = false;
	}
	for(int i = 0 ; i < MOVEKEYTYPE ; i ++)
	{
		mMoveSpeed[i] = 0.0;
	}

 	mRenderForm = new CRenderForm();
	mMooge = new CMooge();

	//Listening all event here.
	mRenderForm->AddCallBackEvent(WM_CREATE, bind(&CAppTwo::OnRenderFormCreate, this, _1));
	mRenderForm->AddCallBackEvent(WM_DESTROY, bind(&CAppTwo::OnRenderFormDestroy, this, _1));
	mRenderForm->AddCallBackEvent(WM_TIMER, bind(&CAppTwo::OnRenderFormTimer, this, _1));
	mRenderForm->AddCallBackEvent(WM_KEYDOWN, bind(&CAppTwo::OnRenderFormKeyDown, this, _1));
	mRenderForm->AddCallBackEvent(WM_KEYUP, bind(&CAppTwo::OnRenderFormKeyUp, this, _1));
	mRenderForm->AddCallBackEvent(WM_LBUTTONDOWN, bind(&CAppTwo::OnRenderFormLBtnDown, this, _1));
	mRenderForm->AddCallBackEvent(WM_CHAR, bind(&CAppTwo::OnRenderFormChar, this, _1));

	//Proceed load windows.
	mRenderForm->Load("Rendering form", 40, 50, 800, 600);

}

CAppTwo::~CAppTwo()
{
	mRenderForm->Unload();
	
	delete mMooge;
	delete mRenderForm;
}

void CAppTwo::OnRenderFormCreate(const WinMsgPackage& MsgPack)
{
	//Start rendering thread.
	Resume();
}

void CAppTwo::OnRenderFormDestroy(const WinMsgPackage& MsgPack)
{
	//Terminate to thread first.
	this->mTerminated = true;
	Sleep(100);

	mMooge->Primitives->RemoveAllLine();
	mMooge->Primitives->RemoveAllBoldLine();
	mMooge->Cameras->RemoveAllCamera();
	mMooge->Core->Destroy();
}

void CAppTwo::OnRenderFormTimer(const WinMsgPackage& MsgPack)
{
	//process camera shift behavior.
	if(!mMooge->Console->IsActivate())
	{
		ProcessCameraShift();
		MouseProcess();
	}	
}

void CAppTwo::OnRenderFormKeyDown(const WinMsgPackage& MsgPack)
{
	//Activate/Deavtivate console.
	if(!mMooge->Console->IsActivate())
	{
		switch(MsgPack.wParam)
		{
		case 'A':
			mKeyTrigger[MoveKey_A] = true;
			break;
		case 'D':
			mKeyTrigger[MoveKey_D] = true;
			break;
		case 'S':
			mKeyTrigger[MoveKey_S] = true;
			break;
		case 'W':
			mKeyTrigger[MoveKey_W] = true;
			break;
		}
	}

	//Special handle esc key for release cursor.
	if(MsgPack.wParam == VK_ESCAPE)
	{
		ShowCursor(true);
		mMouseCaptured = false;
	}
}

void CAppTwo::OnRenderFormKeyUp(const WinMsgPackage& MsgPack)
{
	//Activate/Deavtivate console.
	if(!mMooge->Console->IsActivate())
	{
		switch(MsgPack.wParam)
		{
		case 'A':
			mKeyTrigger[MoveKey_A] = false;
			break;
		case 'D':
			mKeyTrigger[MoveKey_D] = false;
			break;
		case 'S':
			mKeyTrigger[MoveKey_S] = false;
			break;
		case 'W':
			mKeyTrigger[MoveKey_W] = false;
			break;
		}
	}
}

void CAppTwo::OnRenderFormLBtnDown(const WinMsgPackage& MsgPack)
{
	ShowCursor(false);
	//Get window client rect
	RECT rc;
	GetWindowRect(mRenderForm->gethWnd(), &rc);
	//Calculate window center position.
	int windowCenterX = rc.left + ((rc.right - rc.left)/2);
	int windowCenterY = rc.top + ((rc.bottom - rc.top)/2);

	//Get current mouse position on screen.
	POINT thisPoint;
	GetCursorPos(&thisPoint);

	LONG YawPixel = thisPoint.x - windowCenterX;
	LONG PitchPixel = windowCenterY - thisPoint.y;
	
	//Put mouse in window center.
	SetCursorPos(windowCenterX, windowCenterY);

	//Start mouse movement capture.
	mMouseCaptured = true;
}

void CAppTwo::OnRenderFormChar(const WinMsgPackage& MsgPack)
{
	if(MsgPack.wParam == '`')
	{
		//Activate/Deavtivate console.
		if(mMooge->Console->IsActivate())
		{
			mMooge->Console->Deactivate();
		}else
		{
			mMooge->Console->Activate();
		}
	}else
	{
		if(mMooge->Console->IsActivate())
		{
			mMooge->Console->Input(MsgPack.wParam);
		}
	}
}

//[NOTE]: This function MUST be called in Execute().
//Here we setup engine rendering in a seperated thread.
void CAppTwo::SetupEngine()
{
	//Initial engine at thread start.
	mMooge->Core->Initial(mRenderForm->gethWnd());

	//Setup camera.
	mMooge->Cameras->AddCamera(mMainCamera);

	VECTORFS CamEyeVec(40.0, 60.0, 100.0);
	VECTORFS CamCenterVec(0.0, 0.0, 0.0);
	VECTORFS CamUpVec(0.0, 1.0, 0.0);
	mMainCamera->SetPosition(CamEyeVec, CamCenterVec, CamUpVec);

	//Add Engine object here.
	//...

	//Create a timer that fires 30 times a second
	SetTimer(mRenderForm->gethWnd(), 33, 1, NULL);

	mLeastTime = clock();
}

//Render thread execution.
void CAppTwo::Execute()
{
	//Initial and setup engine evvironment.
	SetupEngine();

	//Thread start.
	while(!this->mTerminated)
	{
		mMooge->Render();
		Sleep(1);
	}
}

//Camera shift process.
void CAppTwo::ProcessCameraShift()
{
	for (int i = 0 ; i < MOVEKEYTYPE ; i++)
	{
		if(mKeyTrigger[i])//Key down
		{
			if(mMoveSpeed[i] < 3.0)
			{
				mMoveSpeed[i] += static_cast<float>(0.1);
			}
			if(mMoveSpeed[i] > 3.0)
			{
				mMoveSpeed[i] = 3.0;
			}
		}else//Key release
		{
			if(mMoveSpeed[i] > 0.0)
			{
				if(mMoveSpeed[i] >= 0.2)
				{
					mMoveSpeed[i] -= static_cast<float>(0.2);
				}else
				{
                   	mMoveSpeed[i] = 0.0;
                }

				if(mMoveSpeed[i] < 0.0)
				{
					mMoveSpeed[i] = 0.0;
				}
			}
		}
	}

	mMainCamera->Forward(mMoveSpeed[MoveKey_W]);
	mMainCamera->Backward(mMoveSpeed[MoveKey_S]);
	mMainCamera->Leftward(mMoveSpeed[MoveKey_A]);
	mMainCamera->Rightward(mMoveSpeed[MoveKey_D]);
}

void CAppTwo::MouseProcess()
{
	if(mMouseCaptured)
	{
		//Get window client rect
		RECT rc;
		GetWindowRect(mRenderForm->gethWnd(), &rc);
		//Calculate window center position.
		int windowCenterX = rc.left + ((rc.right - rc.left)/2);
		int windowCenterY = rc.top + ((rc.bottom - rc.top)/2);

		//Get current mouse position on screen.
		POINT thisPoint;
		GetCursorPos(&thisPoint);

		LONG YawPixel = thisPoint.x - windowCenterX;
		LONG PitchPixel = windowCenterY - thisPoint.y;

		//Calculate mouse shift.
		//Rotate camera here.
		if(YawPixel > 0)
		{
			mMainCamera->YawDeg(static_cast<float>(YawPixel)*mRotBase + static_cast<float>(0.5)*mRotAcc*static_cast<float>(YawPixel)*static_cast<float>(YawPixel));
		}else if(YawPixel < 0)
		{
			mMainCamera->YawDeg(static_cast<float>(YawPixel)*mRotBase - static_cast<float>(0.5)*mRotAcc*static_cast<float>(YawPixel)*static_cast<float>(YawPixel));
		}

		if(PitchPixel > 0)
		{
			mMainCamera->PitchDeg(static_cast<float>(PitchPixel)*mRotBase + static_cast<float>(0.5)*mRotAcc*static_cast<float>(PitchPixel)*static_cast<float>(PitchPixel));
		}else if(PitchPixel < 0)
		{
			mMainCamera->PitchDeg(static_cast<float>(PitchPixel)*mRotBase - static_cast<float>(0.5)*mRotAcc*static_cast<float>(PitchPixel)*static_cast<float>(PitchPixel));
		}

		//Put mouse in window center.
		SetCursorPos(windowCenterX, windowCenterY);
	}
}
