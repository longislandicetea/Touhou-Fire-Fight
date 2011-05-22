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
	case CharacterController::UP:
		up(dt*100);
		break;
	case CharacterController::DOWN:
		down(dt*100);
		break;
	case CharacterController::LEFT:
		left(dt*100);
		break;
	case CharacterController::RIGHT:
		right(dt*100);
		break;
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
	mModel = Md2Object::Load("c:\\mh_0.md2","c:\\t2.bmp");
	this->AddChild(mModel);
	mStage = (GameStage*)App::Inst().currentStage();
}

Ref<GameObject> Character::AddController(CharacterController* ctrl)
{
	return Ref<GameObject>(new Character(ctrl));
}
