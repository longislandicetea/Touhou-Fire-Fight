#include "Bomb.h"
#include "Md2Object.h"

#include "App.h"
#include "GameStage.h"

Bomb::Bomb()
{
	mModel = Md2Object::Load("c:\\bomb.md2","c:\\bombt.bmp");
	this->AddChild(mModel);
	mTimer = Ref<Timer>(new Timer);
	mTimer->Begin();
	mFlamePower = 1;
	
}

void Bomb::CreateBomb(int x,int y)
{
	Ref<GameObject> bomb(new Bomb);
	bomb->SetPos(x,0,y);
	GameStage* gs = (GameStage*)App::Inst().currentStage();
	gs->AddBomb(bomb);
}


void Bomb::Update(float dt)
{
	if(mTimer->End()>3.0)
		this->RemoveFromParent();
}
