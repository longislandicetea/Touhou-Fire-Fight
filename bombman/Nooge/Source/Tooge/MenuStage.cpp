#include "MenuStage.h"
#include "GUIObject.h"
#include "DataManager.h"
#include <gl/glut.h>

#include "App.h"
#include "Map.h"
#include "SelectStage.h"

#include "WinFrame.h"

Ref<Stage> MenuStage::LoadStage()
{
	return Ref<Stage> (new MenuStage());
}

MenuStage::MenuStage()
{
	mGuiObject = Ref<GameObject>(new Sprite);

	Ref<GameObject> bgImage (new Image(DataManager::GetDataPath("Image","initStage","resource\\data.ini"),800,600));
	cast<Sprite>(mGuiObject)->AddChild(bgImage);

	Ref<GameObject> bStart (new Image(DataManager::GetDataPath("Image","start","resource\\data.ini"),230,74));
	bStart->SetPos(475,316,0.0);
	cast<Sprite>(mGuiObject)->AddChild(bStart);

	Ref<GameObject> bConfig (new Image(DataManager::GetDataPath("Image","config","resource\\data.ini"),230,74));
	bConfig->SetPos(407,383,0.0);
	cast<Sprite>(mGuiObject)->AddChild(bConfig);

	Ref<GameObject> bHelp (new Image(DataManager::GetDataPath("Image","help","resource\\data.ini"),230,74));
	bHelp->SetPos(557,449,0.0);
	cast<Sprite>(mGuiObject)->AddChild(bHelp);

	Ref<GameObject> bQuit (new Image(DataManager::GetDataPath("Image","quit","resource\\data.ini"),230,74));
	bQuit->SetPos(505,519,0.0);
	cast<Sprite>(mGuiObject)->AddChild(bQuit);

	this->AddChild(mGuiObject);

	if(!App::Inst().AudioSys()->IsBgmMute())
		App::Inst().AudioSys()->PlayStream(0,"menubackground");
}

void MenuStage::HandleClickEvent(int x, int y)
{
	mLastX = x;
	mLastY = y;
	if(x<700 && x>475 && y>316 && y<390)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		App::Inst().ChangeStage(1);
	}
	else if (x<637 && x>407 && y<457 && y>383)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		App::Inst().ChangeStage(5);
	}
	else if (x<787 && x>557 && y<523 && y>449)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		App::Inst().ChangeStage(6);
	}
	else if(x<735 && x>505 && y<593 && y>519)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		exit(0);
	}
}

void MenuStage::Draw(bool is3D)
{
	Stage::Draw(is3D);
}

/*void MenuStage::HandleMouseOverEvent( int x,int y )
{
	mLastX = x;
	mLastY = y;
	LogTrace("lastX: %d lastY: %d\n",mLastX,mLastY);
}*/

void MenuStage::Update( float dt )
{
	if(mLastX<700 && mLastX>475 && mLastY>316 && mLastY<390)
	{
		cast<Sprite>(mGuiObject)->GetChild(1)->RemoveFromParent();
		Ref<GameObject> bStart (new Image(DataManager::GetDataPath("Image","start1","resource\\data.ini"),230,74));
		bStart->SetPos(475,316,0.0);
		cast<Sprite>(mGuiObject)->AddChildAt(bStart,1);
	}
	else if (mLastX<637 && mLastX>407 && mLastY<457 && mLastY>383)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		//App::Inst().AudioSys()->Resume(1);
	}
	else if (mLastX<787 && mLastX>557 && mLastY<523 && mLastY>449)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		//App::Inst().AudioSys()->Resume(1);
	}
	else if(mLastX<735 && mLastX>505 && mLastY<593 && mLastY>519)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		//App::Inst().AudioSys()->Resume(1);
	} 
	else 
	{
	}
}
