#include "EndStage.h"
#include "Image.h"
#include "DataManager.h"

#include "App.h"

Ref<Stage> EndStage::LoadStage( const std::string& result )
{
	return Ref<Stage> (new EndStage(result));
}

void EndStage::HandleClickEvent( int x,int y )
{
	if (x>569 && x<780 && y>516 && y<580)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		App::Inst().ChangeStage(0);
		App::Inst().AudioSys()->Stop(0);
	}
}

EndStage::EndStage(const std::string& type)
{
	mGuiObject = Ref<GameObject>(new Sprite);
	
	Ref<GameObject> bgImage ;
	if(type == "win")
	{
		bgImage = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","win","resource\\data.ini"),800,600));
		if(! App::Inst().AudioSys()->IsBgmMute()) App::Inst().AudioSys()->PlayStream(0,"win");
	}
	else
	{
		bgImage = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","lose","resource\\data.ini"),800,600));
		if(! App::Inst().AudioSys()->IsBgmMute()) App::Inst().AudioSys()->PlayStream(0,"lose");
	}
	cast<Sprite>(mGuiObject)->AddChild(bgImage);

	Ref<GameObject> back(new Image(DataManager::GetDataPath("Image","back","resource\\data.ini"),211,64));
	back->SetPos(569,516,0);
	cast<Sprite>(mGuiObject)->AddChild(back);
	
	this->AddChild(mGuiObject);
}

void EndStage::Update( float dt )
{
	Stage::Update(dt);
	App::Inst().AudioSys()->Update();
}
