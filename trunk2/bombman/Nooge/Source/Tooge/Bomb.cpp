#include "Bomb.h"
#include "Md2Object.h"

#include "App.h"
#include "GameStage.h"
#include "Bonus.h"
#include "Character.h"

Bomb::Bomb()
{
	mModel = Md2Object::Load("c:\\bomb.md2","c:\\bombt.bmp");
	this->AddChild(mModel);
	mTimer = Ref<Timer>(new Timer);
	mTimer->Begin();	
}

void Bomb::CreateBomb(int x,int y, Character* owner)
{
	Ref<GameObject> bomb(new Bomb);
	bomb->SetPos(x,0,y);
	GameStage* gs = (GameStage*)App::Inst().currentStage();
	gs->AddBomb(bomb);
	cast<Bomb>(bomb)->mPower = owner->GetPower();
	cast<Bomb>(bomb)->mOwner = owner;
}


void Bomb::Update(float dt)
{
	if(mTimer->End()>3.0)
	{
		if(mTimer->End()>3.5)
		{
			explode();
			mOwner->SetBombCnt(1);
			Bonus::CreateBonus(GetX(),GetZ());
			this->RemoveFromParent();
		}
		this->SetAlpha(0.0);
	}
}

void Bomb::explode()
{
	int dx[4] = {-1,0,1,0};
	int dy[4] = {0,1,0,-1};

	int dValid[4] = {1,1,1,1};

	int row = this->GetBoundingBox().Row();
	int col = this->GetBoundingBox().Col();
	mFlame.push_back(Ref<Grid>(new Grid(row,col)));

	GameStage* gs = (GameStage*)App::Inst().currentStage();

	for(int i = 1;i<=mPower;++i)
	{
		for(int j = 0;j<4;++j)
		{
			if(dValid[j])
			{
				int nRow = row + i*dx[j];
				int nCol = col + i*dy[j];

				if(!gs->HasUwall(nRow,nCol))
					mFlame.push_back(Ref<Grid> (new Grid(nRow,nCol)));
				else
					dValid[j] = 0;
			}
		}
	}

	for(int k = 0;k<mFlame.size();++k)
	{
		int r = mFlame[k]->Row();
		int c = mFlame[k]->Col();
		//Bonus::CreateBonus(mFlame[k]->CenterX(),mFlame[k]->CenterY());
		gs->DwallExplode(r,c);
	}
}
