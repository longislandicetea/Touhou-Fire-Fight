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
#include "Cube.h"
#include "Md2Object.h"
#include "RuntimeMap.h"

#include "jpeglib.h"	


App::App(void): CThread(true),mMooge(NULL),mRenderForm(NULL),mMainCamera(NULL)
{
	mRenderForm = new CRenderForm();
	mMooge = new CMooge();

	mRenderForm->AddCallBackEvent(WM_CREATE, bind(&App::OnRenderFormCreate, this, _1));
	mRenderForm->AddCallBackEvent(WM_DESTROY, bind(&App::OnRenderFormDestroy, this, _1));
	mRenderForm->AddCallBackEvent(WM_CHAR, bind(&App::OnRenderFormChar, this, _1));
	mRenderForm->AddCallBackEvent(WM_TIMER, bind(&App::OnRenderFormTimer, this, _1));

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

	VECTORFS CamEyeVec(0.0, 120, 100.0);
	VECTORFS CamCenterVec(0.0, 0.0, 0.0);
	VECTORFS CamUpVec(0.0, 120.0, 0.0);
	mMainCamera->SetPosition(CamEyeVec, CamCenterVec, CamUpVec);

	//Add Engine object here.
	//...
	Ref<Stage> stage(new Stage);
	mMooge->CurrentStage = stage;
	
	Ref<GameObject> model = Md2Object::Load("c:\\mh_normal.md2","c:\\t2.bmp");
	model->SetRotateY(90);
	model->SetY(10);

	Ref<GameObject> runtimeMap(new RuntimeMap);
	cast<GameObject,RuntimeMap>(runtimeMap)->SetMap();

	//stage->AddChild(model);
	stage->AddChild(runtimeMap);
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
	}
}

void App::OnRenderFormTimer( const WinMsgPackage& MsgPack )
{
	clock_t now = clock();
	float dt = (float)(now - mLeastTime) / CLOCKS_PER_SEC;
	mMooge->Update(dt);
	mLeastTime = now;
}
