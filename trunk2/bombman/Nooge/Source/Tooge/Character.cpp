#include"Character.h"
#include "Md2Object.h"
#include "App.h"

void Character::Update(float dt)
{
	int oldX = this->GetX();
	int oldZ = this->GetZ();
	int currentAction = mCtrl.Update(this,dt);
	doAction(currentAction,dt);
	if(!(cast<RuntimeMap>(mStage->CurrentMap())->CanPass(this)))
		SetPos(oldX,GetY(),oldZ);
}

void Character::doAction( int currentAction, float dt )
{
	switch (currentAction)
	{
	case CharacterController::MOVE_UP:
		cast<Md2Object>(mModel)->setAnimation("RUN");
		up(dt*mSpeed);
		break;
	case CharacterController::MOVE_DOWN:
		cast<Md2Object>(mModel)->setAnimation("RUN");
		down(dt*mSpeed);
		break;
	case CharacterController::MOVE_LEFT:
		cast<Md2Object>(mModel)->setAnimation("RUN");
		left(dt*mSpeed);
		break;
	case CharacterController::MOVE_RIGHT:
		cast<Md2Object>(mModel)->setAnimation("RUN");
		right(dt*mSpeed);
		break;
	case CharacterController::DROP_BOMB:
		Ref<GameObject> bomb(new Bomb);
		bomb->SetPos(GetX(),0,GetZ());
		cast<RuntimeMap>(mStage->CurrentMap())->AddBomb(bomb);
		break;
	/*case CharacterController::TRIGGER_BOMB:
		break;*/
	}
}

void Character::up( float dt )
{
	this->SetZ(GetZ()-dt);
}

void Character::down( float dt )
{
	this->SetZ(GetZ()+dt);
}

void Character::left( float dt )
{
	this->SetX(GetX()-dt);
}

void Character::right( float dt )
{
	this->SetX(GetX()+dt);
}

Character::Character(CharacterController* ctrl)
	: mCtrl(*ctrl)
{
	mModel = Md2Object::Load("c:\\mh_name.md2","c:\\t2.bmp");
	cast<Md2Object>(mModel)->setAnimation("IDLE");
	this->AddChild(mModel);
	mStage = (GameStage*)App::Inst().currentStage();
	mSpeed = 100.0;
}

Ref<GameObject> Character::AddController(CharacterController* ctrl)
{
	return Ref<GameObject>(new Character(ctrl));
}

GameStage* Character::GetGameStage()
{
	return mStage;
}

Character::~Character()
{
	delete mStage;
}
