#include"Character.h"
#include "WinFrame.h"
#include "Md2Object.h"
#include "App.h"
#include "Bomb.h"

#include "Explosion.h"
#include "PlayerController.h"
#include "NPCController.h"

void Character::Update(float dt)
{
	int oldX = this->GetX();
	int oldZ = this->GetZ();
	mCurrentAction = mCtrl.Update(this,dt);
	doAction(mCurrentAction,dt);
	
	GameStage* gs =(GameStage*)(App::Inst().CurrentStage());
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
	Sprite::Update(dt);
}

void Character::doAction( int currentAction, float dt )
{
	switch (currentAction)
	{
	case CharacterController::MOVE_UP:
		SetCol();
		up(dt*mSpeed);
		if(mLastAction == CharacterController::IDLE)
			cast<Md2Object>(mModel)->setAnimation("RUN");
		break;
	case CharacterController::MOVE_DOWN:
		SetCol();
		down(dt*mSpeed);
		if(mLastAction == CharacterController::IDLE)
			cast<Md2Object>(mModel)->setAnimation("RUN");
		break;
	case CharacterController::MOVE_LEFT:
		SetRow();
		left(dt*mSpeed);
		if(mLastAction == CharacterController::IDLE)
			cast<Md2Object>(mModel)->setAnimation("RUN");
		break;
	case CharacterController::MOVE_RIGHT:
		SetRow();
		right(dt*mSpeed);
		if(mLastAction == CharacterController::IDLE)
			cast<Md2Object>(mModel)->setAnimation("RUN");
		break;
	case CharacterController::DROP_BOMB:
		if(mBombCnt>0) 
		{
			Bomb::CreateBomb(GetX(),GetZ(),this);
			if(! App::Inst().AudioSys()->IsSndMute()) App::Inst().AudioSys()->PlayEffectSound(1,"dropbomb");
			SetBombCnt(-1);
		}
		break;
	case CharacterController::TRIGGER_BOMB:
		mTrigTimer->Begin();
		this->SetTrigBonus(false);
		break;
	case CharacterController::IDLE:
		cast<Md2Object>(mModel)->setAnimation("IDLE");
	}

	mLastAction = (CharacterController::Action)currentAction;
}

void Character::up( float dt )
{
	this->SetZ(GetZ()-dt);
	mModel->SetRotateY(180);
}

void Character::down( float dt )
{
	this->SetZ(GetZ()+dt);
	mModel->SetRotateY(0);
}

void Character::left( float dt )
{
	this->SetX(GetX()-dt);
	mModel->SetRotateY(270);
}

void Character::right( float dt )
{
	this->SetX(GetX()+dt);
	mModel->SetRotateY(90);
}

Character::Character(CharacterController* ctrl, const std::string& type)
	: mCtrl(*ctrl)
{
	//mModel = Md2Object::Load("c:\\mh_name.md2","c:\\t2.bmp");
	if(type == "player")
		mModel = Md2Object::Load(DataManager::GetDataPath("Model","player","resource\\data.ini"),DataManager::GetDataPath("Texture","playerT","resource\\data.ini"));
	else if(type == "npc1")
		mModel = Md2Object::Load(DataManager::GetDataPath("Model","npc","resource\\data.ini"),DataManager::GetDataPath("Texture","npc1T","resource\\data.ini"));
	else if(type == "npc2")
		mModel = Md2Object::Load(DataManager::GetDataPath("Model","npc","resource\\data.ini"),DataManager::GetDataPath("Texture","npc2T","resource\\data.ini"));
	else
		mModel = Md2Object::Load(DataManager::GetDataPath("Model","npc","resource\\data.ini"),DataManager::GetDataPath("Texture","npc3T","resource\\data.ini"));
	
	cast<Md2Object>(mModel)->setAnimation("RUN");
	this->AddChild(mModel);
	mSpeed = 60;
	mBombPower = 1;
	mLifeCnt = 1;
	mBombCnt = 1;
	mHasDropMalus = false;
	mHasPushBonus = false;
	mHasTrigBonus = false;
	mTimer = Ref<Timer>(new Timer);
	mTrigTimer = Ref<Timer>(new Timer);

	mLastAction = CharacterController::IDLE;
}

/*Ref<GameObject> Character::AddController(CharacterController* ctrl)
{
	return Ref<GameObject>(new Character(ctrl));
}*/

void Character::SetSpeed( float factor )
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

float Character::GetSpeed()
{
	return mSpeed;
}

void Character::SetBombCnt( int factor )
{
	LogTrace("factor:%d BombCnt:%d, finally:%d \n",factor,mBombCnt,factor + mBombCnt);
	mBombCnt += factor;
	// std::cerr<< mBombCnt<<std::endl;
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
	mTrigTimer->Begin();
}

bool Character::HasTrigBonus()
{
	return mHasTrigBonus;
}

Ref<Timer> Character::TrigBonusTimer()
{
	return mTrigTimer;
}

Grid Character::GetBoundingBox()
{

	float offset = Grid::SideLen/2-2;
	return Grid(GetX()-offset,GetZ()+offset,GetX()+offset,GetZ()-offset);
}

Ref<GameObject> Character::CreateCharacter( const std::string& type )
{
	if(type == "player")
	{
		PlayerController* playerCtrl = new PlayerController();
		return Ref<GameObject> (new Character(playerCtrl,type));
	}
	else 
	{
		NPCController* npcCtrl = new NPCController();
		if(type == "npc1")
			return Ref<GameObject> (new Character(npcCtrl,"npc1"));
		else if (type == "npc2")
			return Ref<GameObject> (new Character(npcCtrl,"npc2"));
		else
			return Ref<GameObject> (new Character(npcCtrl,"npc3"));
	}
}

void Character::SetLifeCnt( int factor )
{
	mLifeCnt += factor;
}

