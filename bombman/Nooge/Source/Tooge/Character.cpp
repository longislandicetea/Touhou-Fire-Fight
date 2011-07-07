#include"Character.h"
#include "Md2Object.h"
#include "App.h"
#include "Bomb.h"

void Character::Update(float dt)
{
	int oldX = this->GetX();
	int oldZ = this->GetZ();
	mCurrentAction = mCtrl.Update(this,dt);
	doAction(mCurrentAction,dt);
	
	GameStage* gs =(GameStage*)(App::Inst().currentStage());
	if(!gs->CanPass(this))
		SetPos(oldX,GetY(),oldZ);
	gs->EatBonus(this);
	gs->StepOnBomb(this);

	if(mHasDropMalus)
	{
		if(mTimer->End()>10.0)
		{
			SetBombCnt(1);
			mHasDropMalus = false;
		}
	}
}

void Character::doAction( int currentAction, float dt )
{
	switch (currentAction)
	{
	case CharacterController::MOVE_UP:
		//cast<Md2Object>(mModel)->setAnimation("RUN");
		up(dt*mSpeed);
		break;
	case CharacterController::MOVE_DOWN:
		//cast<Md2Object>(mModel)->setAnimation("RUN");
		down(dt*mSpeed);
		break;
	case CharacterController::MOVE_LEFT:
		//cast<Md2Object>(mModel)->setAnimation("RUN");
		left(dt*mSpeed);
		break;
	case CharacterController::MOVE_RIGHT:
		//cast<Md2Object>(mModel)->setAnimation("RUN");
		right(dt*mSpeed);
		break;
	case CharacterController::DROP_BOMB:
		if(mBombCnt>0) 
		{
			Bomb::CreateBomb(GetX(),GetZ(),this);
			SetBombCnt(-1);
		}
		break;
	case CharacterController::TRIGGER_BOMB:
		mTrigTimer->Begin();
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
	//mModel = Md2Object::Load("c:\\mh_name.md2","c:\\t2.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","player","resource\\data.ini"),DataManager::GetDataPath("Texture","playerT","resource\\data.ini"));
	cast<Md2Object>(mModel)->setAnimation("IDLE");
	this->AddChild(mModel);
	mSpeed = 100.0;
	mBombPower = 1;
	//mLifeCnt = 
	mBombCnt = 1;
	mHasDropMalus = false;
	mHasPushBonus = false;
	mHasTrigBonus = false;
	mTimer = Ref<Timer>(new Timer);
	mTrigTimer = Ref<Timer>(new Timer);
}

Ref<GameObject> Character::AddController(CharacterController* ctrl)
{
	return Ref<GameObject>(new Character(ctrl));
}

void Character::SetSpeed( int factor )
{
	mSpeed *= factor;
}

void Character::SetPower( int factor )
{
	mBombPower += factor;
}

int Character::GetPower()
{
	return mBombPower;
}

void Character::SetBombCnt( int factor )
{
	mBombCnt += factor;
}

int Character::GetBombCnt()
{
	return mBombCnt;
}

void Character::SetTimer()
{
	mHasDropMalus = true;
	mTimer->Begin();
}

void Character::SetPushBonus(bool hasBonus)
{
	mHasPushBonus = hasBonus;
}

bool Character::HasPushBonus()
{
	return mHasPushBonus;
}

int Character::GetCurState()
{
	return mCurrentAction;
}

void Character::SetTrigBonus( bool hasBonus )
{
	mHasTrigBonus = hasBonus;
}

bool Character::HasTrigBonus()
{
	return mHasTrigBonus;
}

Ref<Timer> Character::TrigBonusTimer()
{
	return mTrigTimer;
}

