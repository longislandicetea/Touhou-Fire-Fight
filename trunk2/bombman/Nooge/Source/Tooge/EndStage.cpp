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
	Ref<GameObject> bgImage ;
	if(type == "win")
	{
		bgImage = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","endWin","resource\\data.ini"),800,600));
		App::Inst().AudioSys()->PlayStream(1,"win");
	}
	else
	{
		bgImage = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","endLose","resource\\data.ini"),800,600));
		App::Inst().AudioSys()->PlayStream(1,"lose");
	}
	
	cast<Sprite>(mGuiObject)->AddChild(bgImage);
	this->AddChild(mGuiObject);
}

void EndStage::Update( float dt )
{
	Stage::Update(dt);
	App::Inst().AudioSys()->Update();
}
