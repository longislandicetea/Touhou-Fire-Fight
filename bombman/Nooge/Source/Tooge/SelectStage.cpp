#include "SelectStage.h"
#include "DataManager.h"

#include "App.h"
#include "Map.h"
#include "GameStage.h"
#include "MenuStage.h"
#include "Image.h"

Ref<Stage> SelectStage::LoadStage()
{
	return Ref<Stage> (new SelectStage);
}

SelectStage::SelectStage()
{
	mGuiObject = Ref<GameObject>(new Sprite);

	Ref<GameObject> bgImage (new Image(DataManager::GetDataPath("Image","selectStage","resource\\data.ini"),800,600));
	cast<Sprite>(mGuiObject)->AddChild(bgImage);

	Ref<GameObject> back(new Image(DataManager::GetDataPath("Image","back","resource\\data.ini"),211,64));
	back->SetPos(569,516,0);
	cast<Sprite>(mGuiObject)->AddChild(back);

	this->AddChild(mGuiObject);
}

void SelectStage::HandleClickEvent(int x, int y)
{
	if (x>569 && x<780 && y>516 && y<580)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		App::Inst().ChangeStage(0);
	}

	else if(x>336 && x<628 && y>175 && y<254)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		App::Inst().AudioSys()->Stop(0);
		App::Inst().ChangeStage(2);
	}

	else if (x>443 && x<766 && y>276 && y<355)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		App::Inst().AudioSys()->Stop(0);
		App::Inst().ChangeStage(3);
	}
	else if (x>391 && x<689 && y>379 && y<452)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		App::Inst().AudioSys()->Stop(0);
		App::Inst().ChangeStage(4);
	}
}
void SelectStage::Update( float dt )
{
	Stage::Update(dt);
	App::Inst().AudioSys()->Update();
}






