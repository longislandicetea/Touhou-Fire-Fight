#include "SelectStage.h"
#include "GUIObject.h"
#include "DataManager.h"

#include "App.h"
#include "Map.h"
#include "GameStage.h"

Ref<Stage> SelectStage::LoadStage()
{
	return Ref<Stage> (new SelectStage());
}

SelectStage::SelectStage()
{
	mGuiObject = Ref<GameObject>(new Sprite);

	Ref<GameObject> bgImage (new Image(DataManager::GetDataPath("Image","selectStage","resource\\data.ini"),800,600));
	cast<Sprite>(mGuiObject)->AddChild(bgImage);

	/*Ref<GameObject> bStart (new Image(DataManager::GetDataPath("Image","start","resource\\data.ini"),230,74));
	//cast<Image>(bStart)->SetPos2D(475,316);
	bStart->SetPos(475,316,0.0);
	cast<Sprite>(mGuiObject)->AddChild(bStart);

	Ref<GameObject> bConfig (new Image(DataManager::GetDataPath("Image","config","resource\\data.ini"),230,74));
	bConfig->SetPos(407,383,0.0);
	cast<Sprite>(mGuiObject)->AddChild(bConfig);

	Ref<GameObject> bHelp (new Image(DataManager::GetDataPath("Image","help","resource\\data.ini"),230,74));
	bHelp->SetPos(557,449,0.0);
	cast<Sprite>(mGuiObject)->AddChild(bHelp);*/

	this->AddChild(mGuiObject);
}

void SelectStage::HandleClickEvent(int x, int y)
{
	if(y>0 && y<200)
	{
		//App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		//App::Inst().AudioSys()->Resume(1);
		//App::Inst().AudioSys()->Stop(0);
		Ref<GameObject> map = Map::Load(DataManager::GetDataPath("Map","map","resource\\data.ini"));
		Ref<Stage> gameStage(new GameStage(map,1));
		App::Inst().ChangeStage(gameStage);
	}
	else if (y>200 && y<400)
	{
		/*App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		App::Inst().AudioSys()->Resume(1);*/
		Ref<GameObject> map = Map::Load(DataManager::GetDataPath("Map","map","resource\\data.ini"));
		Ref<Stage> gameStage(new GameStage(map,2));
		App::Inst().ChangeStage(gameStage);
	}
	else if (y>400 && y<600)
	{
		/*App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		App::Inst().AudioSys()->Resume(1);*/
		Ref<GameObject> map = Map::Load(DataManager::GetDataPath("Map","map","resource\\data.ini"));
		Ref<Stage> gameStage(new GameStage(map,3));
		App::Inst().ChangeStage(gameStage);
	}
}




