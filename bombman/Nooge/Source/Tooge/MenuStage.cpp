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
	
	Ref<Image> start (new Image(DataManager::GetDataPath("Image","start","resource\\data.ini")));
	Ref<GameObject> bStart (new GUIObject(start,475,386,692,316));
	cast<Sprite>(mGuiObject)->AddChild(bStart);

	Ref<Image> config (new Image(DataManager::GetDataPath("Image","config","resource\\data.ini")));
	Ref<GameObject> bConfig (new GUIObject(config,407,453,624,383));
	cast<Sprite>(mGuiObject)->AddChild(bConfig);

	Ref<Image> help (new Image(DataManager::GetDataPath("Image","help","resource\\data.ini")));
	Ref<GameObject> bHelp (new GUIObject(help,557,519,774,449));
	cast<Sprite>(mGuiObject)->AddChild(bHelp);

	Ref<Image> quit (new Image(DataManager::GetDataPath("Image","quit","resource\\data.ini")));
	Ref<GameObject> bQuit (new GUIObject(quit,505,589,722,519));
	cast<Sprite>(mGuiObject)->AddChild(bQuit);

	Ref<Image> image (new Image(DataManager::GetDataPath("Image","initStage","resource\\data.ini")));
	Ref<GameObject> tmp(new GUIObject(image,0,600,800,0));
	cast<Sprite>(mGuiObject)->AddChild(tmp);

	this->AddChild(mGuiObject);
}

void MenuStage::HandleClickEvent(int x, int y)
{
	if(x<=400 && x>=0)
	{
		Ref<GameObject> map = Map::Load(DataManager::GetDataPath("Map","map","resource\\data.ini"));
		Ref<Stage> gameStage(new GameStage(map));
		App::Inst().ChangeStage(gameStage);
	}
}
