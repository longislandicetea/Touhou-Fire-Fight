#include "App.h"
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
#include "Stage.h"
#include "Md2Object.h"
#include "Map.h"
#include "Character.h"
#include "PlayerController.h"
#include "GameStage.h"
#include "DataManager.h"
#include "jpeglib.h"	

#include "MenuStage.h"
#include <gl/glut.h>

App::App(void): CThread(true),mMooge(NULL),mRenderForm(NULL),mMainCamera(NULL)
{
	mRenderForm = new CRenderForm();
	mMooge = new CMooge();
	mInputSys = Ref<InputSystem>(new InputSystem);

	mRenderForm->AddCallBackEvent(WM_CREATE, bind(&App::OnRenderFormCreate, this, _1));
	mRenderForm->AddCallBackEvent(WM_DESTROY, bind(&App::OnRenderFormDestroy, this, _1));
	mRenderForm->AddCallBackEvent(WM_CHAR, bind(&App::OnRenderFormChar, this, _1));
	mRenderForm->AddCallBackEvent(WM_TIMER, bind(&App::OnRenderFormTimer, this, _1));
	mRenderForm->AddCallBackEvent(WM_KEYDOWN, bind(&App::OnRenderFormKeyDown, this, _1));
	mRenderForm->AddCallBackEvent(WM_KEYUP, bind(&App::OnRenderFormKeyUp, this, _1));
	mRenderForm->AddCallBackEvent(WM_LBUTTONDOWN,bind(&App::OnRenderFormClickButton,this,_1));
	mRenderForm->Load("Rendering form", 40, 50, 800, 600);
}


App::~App(void)
{
	mRenderForm->Unload();
	delete mMooge;
	delete mRenderForm;
}

void App::OnRenderFormCreate(const WinMsgPackage& MsgPack)
{
	Resume();
}

void App::OnRenderFormDestroy(const WinMsgPackage& MsgPack)
{
	this->mTerminated = true;
	Sleep(100);

	mMooge->Cameras->RemoveAllCamera();
	mMooge->Core->Destroy();
}

void App::OnRenderFormChar(const WinMsgPackage& MsgPack)
{
	if(MsgPack.wParam == '`')
	{
		if(mMooge->Console->IsActivate())
		{
			mMooge->Console->Deactivate();
		}else
		{
			mMooge->Console->Activate();
		}
	}
	else
	{
		if(mMooge->Console->IsActivate())
		{
			mMooge->Console->Input(MsgPack.wParam);
		}
	}
}

void App::SetupEngine()
{
	mMooge->Core->Initial(mRenderForm->gethWnd());

	//Setup camera.
	mMooge->Cameras->AddCamera(mMainCamera);

	VECTORFS CamEyeVec(75.0,120.0,180.0);
	VECTORFS CamCenterVec(75.0, 0.0, 65.0);
	VECTORFS CamUpVec(0.0, 40.0, 0.0);

	mMainCamera->SetPosition(CamEyeVec, CamCenterVec, CamUpVec);

	//Add Engine object here.
	
	Ref<GameObject> map = Map::Load(DataManager::GetDataPath("Map","map","resource\\data.ini"));
	Ref<Stage> gameStage(new GameStage(map));
	mMooge->CurrentStage = gameStage;

	/*Ref<Stage> initStage = MenuStage::LoadStage();
	mMooge->CurrentStage = initStage;*/

	//Create a timer that fires 30 times a second
	SetTimer(mRenderForm->gethWnd(), 33, 1, NULL);

	mLeastTime = clock();
}

void App::Execute()
{
	SetupEngine();

	while(!this->mTerminated)
	{
		mMooge->Render();
		Sleep(1000 / 33);
		clock_t now = clock();
		float dt = (float)(now - mLeastTime) / CLOCKS_PER_SEC;
		mMooge->Update(dt);
		mLeastTime = now;
	}

	if(!mMooge->NextStage.IsNull())
	{
		//mMooge->CurrentStage.Clear();
		mMooge->CurrentStage = mMooge->NextStage;
		mMooge->NextStage.Clear();
	}
}

void App::OnRenderFormTimer( const WinMsgPackage& MsgPack )
{
}

App& App::Inst()
{
	static App _app;
	return _app;
}

Ref<InputSystem> App::InputSys()
{
	return mInputSys;
}

void App::OnRenderFormKeyDown( const WinMsgPackage& MsgPack )
{
	if(!mMooge->Console->IsActivate())
	{
		switch(MsgPack.wParam)
		{
		case VK_UP:
			mInputSys->KeyDown(VK_UP);
			break;
		case VK_DOWN:
			mInputSys->KeyDown(VK_DOWN);
			break;
		case VK_LEFT:
			mInputSys->KeyDown(VK_LEFT);
			break;
		case VK_RIGHT:
			mInputSys->KeyDown(VK_RIGHT);
			break;
		case VK_SPACE:
			mInputSys->KeyDown(VK_SPACE);
			break;
		case VK_SHIFT:
			mInputSys->KeyDown(VK_SHIFT);
			break;
		}
	}
}

void App::OnRenderFormKeyUp( const WinMsgPackage& MsgPack )
{
	if(!mMooge->Console->IsActivate())
	{
		switch(MsgPack.wParam)
		{
		case VK_UP:
			mInputSys->KeyUp(VK_UP);
			break;
		case VK_DOWN:
			mInputSys->KeyUp(VK_DOWN);
			break;
		case VK_LEFT:
			mInputSys->KeyUp(VK_LEFT);
			break;
		case VK_RIGHT:
			mInputSys->KeyUp(VK_RIGHT);
			break;
		case VK_SPACE:
			mInputSys->KeyUp(VK_SPACE);
			break;
		case VK_SHIFT:
			mInputSys->KeyUp(VK_SHIFT);
			break;
		}
	}
}

Stage * App::CurrentStage()
{
	return &*mMooge->CurrentStage;
}

void App::ChangeStage( Ref<Stage> next )
{
	mMooge->CurrentStage = next;
}

void App::OnRenderFormClickButton( const WinMsgPackage& MsgPack )
{
	int x = LOWORD(MsgPack.lParam);
	int y = HIWORD(MsgPack.lParam);
	CurrentStage()->HandleClickEvent(x,y);
	LogTrace("%d %d\n",x,y);
}
