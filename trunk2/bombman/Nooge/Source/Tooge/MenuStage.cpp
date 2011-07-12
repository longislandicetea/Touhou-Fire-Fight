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
	
	Ref<Image> image1 (new Image(DataManager::GetDataPath("Image","button1","resource\\data.ini")));
	Ref<GameObject> tmp1 (new GUIObject(image1,50,50,562,562));
	cast<Sprite>(mGuiObject)->AddChild(tmp1);

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
