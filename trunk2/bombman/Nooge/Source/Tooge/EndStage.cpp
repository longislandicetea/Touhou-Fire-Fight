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

}

EndStage::EndStage(const std::string& type)
{
	mGuiObject = Ref<GameObject>(new Sprite);

	Ref<GameObject> canvas (new Image(DataManager::GetDataPath("Image","end","resource\\data.ini"),800,600));
	cast<Sprite>(mGuiObject)->AddChild(canvas);
	
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
	
	this->AddChild(mGuiObject);
}

void EndStage::Update( float dt )
{
	Stage::Update(dt);
	App::Inst().AudioSys()->Update();
}
