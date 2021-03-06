#include "Bomb.h"
#include "Md2Object.h"

#include "App.h"
#include "GameStage.h"
#include "Bonus.h"
#include "Character.h"
#include "Explosion.h"

Bomb::Bomb()
{
	//mModel = Md2Object::Load("c:\\bomb.md2","c:\\bombt.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","bomb","resource\\data.ini"),DataManager::GetDataPath("Texture","bombT","resource\\data.ini"));
	this->AddChild(mModel);
	mTimer = Ref<Timer>(new Timer);
	mTimer->Begin();	
	mPushed = false;
	mInTrigState = false;
}

void Bomb::CreateBomb(int x,int y, Character* owner)
{
	Ref<GameObject> bomb(new Bomb);
	bomb->SetPos(x,0,y);
	bomb->SetCol();
	bomb->SetRow();
	GameStage* gs = (GameStage*)App::Inst().CurrentStage();
	gs->AddBomb(bomb);
	//owner->SetBombCnt(-1);
	cast<Bomb>(bomb)->mOwner = owner;
	cast<Bomb>(bomb)->mPower = owner->GetPower();
}


void Bomb::Update(float dt)
{
	int oldX = GetX();
	int oldZ = GetZ();
	if(mPushed)
		MoveWhenPushed(dt*mSpeed);
	GameStage* gs = (GameStage*)App::Inst().CurrentStage();
	if(!gs->CanPass(this))
		SetPos(oldX,GetY(),oldZ);
	if(!mOwner->HasTrigBonus())
	{
		if(mTimer->End()>3.0)
		{
			if(mTimer->End()>3.3)
			{
				actWhenSteped();
			}
			this->SetAlpha(0.0);
		}
	}
	else
	{
		//mInTrigState = true;
		if(mOwner->GetCurState() == CharacterController::TRIGGER_BOMB ||mInTrigState)
		{
			mInTrigState = true;
			this->SetAlpha(0.0);
			//if(mOwner->TrigBonusTimer()->End()>0.3)
				actWhenSteped();
			
			mOwner->SetTrigBonus(true);
			if(mOwner == &*gs->Player()) gs->SetBonusCnt(3);
		}
	}
}

void Bomb::explode()
{
	int dx[4] = {-1,0,1,0};
	int dy[4] = {0,1,0,-1};

	int dValid[4] = {1,1,1,1};
	
	mFlame.reserve(30);
	mSurroundDwall.reserve(30);
	int row = this->GetBoundingBox().Row();
	int col = this->GetBoundingBox().Col();
	mFlame.push_back(Ref<Grid>(new Grid(row,col)));

	GameStage* gs = (GameStage*)App::Inst().CurrentStage();

	for(int i = 1;i<=mPower;++i)
	{
		for(int j = 0;j<4;++j)
		{
			if(dValid[j])
			{
				int nRow = row + i*dx[j];
				int nCol = col + i*dy[j];

				if(!gs->HasUwall(nRow,nCol))
				{
					Ref<Grid> curGrid (new Grid(nRow,nCol));
					mFlame.push_back(curGrid);
					if(gs->HasDwall(nRow,nCol))
					{
						mSurroundDwall.push_back(curGrid);
					}
				}
				else
					dValid[j] = 0;
			}
		}
	}
	if(! App::Inst().AudioSys()->IsSndMute()) App::Inst().AudioSys()->PlayEffectSound(1,"explode");
	for(int k = 0;k<mFlame.size();++k)
	{
		int r = mFlame[k]->Row();
		int c = mFlame[k]->Col();
		int x = mFlame[k]->CenterX();
		int y = mFlame[k]->CenterY();
		Ref<GameObject> explosion(new Explosion(x,rand()%5,y));
		gs->AddExplosion(explosion);
		gs->CheckCharacterLife(r,c);
		gs->DwallExplode(r,c);
	}
}

void Bomb::MoveWhenPushed(float ds)
{
	//0-left 1-down 2-right 3-up
	switch(mDirection)
	{
	case 0:
		SetZ(GetZ()-ds);
		break;
	case 1:
		SetZ(GetZ()+ds);
		break;
	case 2:
		SetX(GetX()+ds);
		break;
	case 3:
		SetX(GetX()-ds);
		break;
	}
}

void Bomb::TriggerPush( int direction,float speed )
{
	mDirection = direction;
	mSpeed = speed;
	mPushed = true;
}

void Bomb::actWhenSteped()
{
	explode();
	mOwner->SetBombCnt(1);
	//Bonus::CreateBonus(GetX(),GetZ());
	if(!mSurroundDwall.empty())
	{
		int randId = rand()%(mSurroundDwall.size());
		Bonus::CreateBonus(mSurroundDwall[randId]->CenterX(),mSurroundDwall[randId]->CenterY());
	}
	this->RemoveFromParent();
	//this->GetParent()->AddChildAt()
}

int Bomb::GetPower()
{
	return mPower;
}

Ref<Timer> Bomb::GetTimer()
{
	return mTimer;
}

bool Bomb::IsInTriggerState()
{
	return mInTrigState;
}

Character* Bomb::GetOwner()
{
	return mOwner;
}
