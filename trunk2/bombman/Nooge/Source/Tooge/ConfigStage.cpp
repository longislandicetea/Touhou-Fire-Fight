#include "ConfigStage.h"
#include "Image.h"
#include "DataManager.h"

#include "App.h"

Ref<Stage> ConfigStage::LoadStage()
{
	return Ref<Stage> (new ConfigStage);
}

void ConfigStage::HandleClickEvent( int x,int y )
{
	mouseX = x;
	mouseY = y;

	if (x>569 && x<780 && y>516 && y<580)
	{
		App::Inst().AudioSys()->PlayEffectSound(1,"menubutton");
		App::Inst().ChangeStage(0);
	}
}

ConfigStage::ConfigStage()
{
	mGuiObject = Ref<GameObject>(new Sprite);
	Ref<GameObject> bgImage (new Image(DataManager::GetDataPath("Image","configStage","resource\\data.ini"),800,600));
	Ref<GameObject> bgm,snd;
	
	if(!App::Inst().AudioSys()->IsBgmMute()){
		bgm = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","on0","resource\\data.ini"),82,58));
		bgm->SetPos(580,258,0);}
	else {
		bgm = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","off0","resource\\data.ini"),126,68));
		bgm->SetPos(550,258,0);}
	
	if(!App::Inst().AudioSys()->IsSndMute()){
		snd = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","on0","resource\\data.ini"),82,58));
		snd->SetPos(580,346,0);}
	else{
		snd = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","off0","resource\\data.ini"),126,68));
		snd->SetPos(550,346,0);}
	
	Ref<GameObject> back(new Image(DataManager::GetDataPath("Image","back","resource\\data.ini"),211,64));
	back->SetPos(569,516,0);

	cast<Sprite>(mGuiObject)->AddChild(bgImage);
	cast<Sprite>(mGuiObject)->AddChild(bgm);
	cast<Sprite>(mGuiObject)->AddChild(snd);
	cast<Sprite>(mGuiObject)->AddChild(back);
	this->AddChild(mGuiObject);
}

void ConfigStage::Update( float dt )
{
	Stage::Update(dt);
	App::Inst().AudioSys()->Update();

	bool isBgmOn = !(App::Inst().AudioSys()->IsBgmMute());
	bool isSndOn = !(App::Inst().AudioSys()->IsSndMute());

	if(mouseX>550 && mouseX<676 && mouseY>258 && mouseY<326)
	{
		if(isBgmOn)
		{
			cast<Sprite>(mGuiObject)->GetChild(1)->RemoveFromParent();
			Ref<GameObject> bgmOff(new Image(DataManager::GetDataPath("Image","off0","resource\\data.ini"),126,68));
			bgmOff->SetPos(550,258,0.0);
			cast<Sprite>(mGuiObject)->AddChildAt(bgmOff,1);
			App::Inst().AudioSys()->Mute(0,true);
		}
		else
		{
			cast<Sprite>(mGuiObject)->GetChild(1)->RemoveFromParent();
			Ref<GameObject> bgmOn(new Image(DataManager::GetDataPath("Image","on0","resource\\data.ini"),82,58));
			bgmOn->SetPos(580,258,0.0);
			cast<Sprite>(mGuiObject)->AddChildAt(bgmOn,1);
			App::Inst().AudioSys()->Mute(0,false);
		}
		isBgmOn = !isBgmOn;
	}

	else if (mouseX>550 && mouseX<672 && mouseY>346 && mouseY<414)
	{
		if(isSndOn)
		{
			cast<Sprite>(mGuiObject)->GetChild(2)->RemoveFromParent();
			Ref<GameObject> sndOff(new Image(DataManager::GetDataPath("Image","off0","resource\\data.ini"),126,68));
			sndOff->SetPos(550,346,0.0);
			cast<Sprite>(mGuiObject)->AddChildAt(sndOff,2);
			App::Inst().AudioSys()->Mute(1,true);
			//App::Inst().SetSndState(false);
		}

		else
		{
			cast<Sprite>(mGuiObject)->GetChild(2)->RemoveFromParent();
			Ref<GameObject> sndOn(new Image(DataManager::GetDataPath("Image","on0","resource\\data.ini"),82,58));
			sndOn->SetPos(580,346,0.0);
			cast<Sprite>(mGuiObject)->AddChildAt(sndOn,2);
			App::Inst().AudioSys()->Mute(1,false);
			//App::Inst().SetSndState(true);
		}
		isSndOn = !isSndOn;
	}
	mouseX = mouseY = -1;
}