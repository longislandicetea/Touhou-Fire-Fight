#include "HelpStage.h"
#include "Image.h"
#include "DataManager.h"

#include "App.h"

Ref<Stage> HelpStage::LoadStage()
{
	return Ref<Stage> (new HelpStage);
}

void HelpStage::HandleClickEvent( int x,int y )
{
	if (x>569 && x<780 && y>516 && y<580)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		App::Inst().ChangeStage(0);
	}
}

HelpStage::HelpStage()
{
	mGuiObject = Ref<GameObject>(new Sprite);
	Ref<GameObject> bgImage (new Image(DataManager::GetDataPath("Image","helpStage","resource\\data.ini"),800,600));
	Ref<GameObject> back (new Image(DataManager::GetDataPath("Image","back","resource\\data.ini"),211,64));
	back->SetPos(569,516,0);

	cast<Sprite>(mGuiObject)->AddChild(bgImage);
	cast<Sprite>(mGuiObject)->AddChild(back);
	this->AddChild(mGuiObject);
}

void HelpStage::Update( float dt )
{
	Stage::Update(dt);
	App::Inst().AudioSys()->Update();
}