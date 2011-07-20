#include "MenuStage.h"
#include "GUIObject.h"
#include "DataManager.h"
#include <gl/glut.h>

#include "App.h"
#include "Map.h"
#include "GameStage.h"

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
	//cast<Image>(bStart)->SetPos2D(475,316);
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

	App::Inst().AudioSys()->PlayStream(0,"menubackground");
}

void MenuStage::HandleClickEvent(int x, int y)
{
	if(x<700 && x>475 && y>316 && y<390)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		Ref<GameObject> map = Map::Load(DataManager::GetDataPath("Map","map","resource\\data.ini"));
		Ref<Stage> gameStage(new GameStage(map));
		App::Inst().ChangeStage(gameStage);
		App::Inst().AudioSys()->Stop(0);
	}
}

void MenuStage::Draw(bool is3D)
{
	Stage::Draw(is3D);
}
