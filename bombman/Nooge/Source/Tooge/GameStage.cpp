#include "GameStage.h"

#include <iostream>
#include <cstdlib>
#include "PlayerController.h"

#include "BBombPlus.h"
#include "BDrop.h"
#include "BFaster.h"
#include "BFlamePlus.h"
#include "BPush.h"
#include "BSlower.h"
#include "BTrigger.h"
#include "Grid.h"

Ref<GameObject> GameStage::CurrentMap()
{
	return mCurrentMap;
}

GameStage::GameStage( Ref<GameObject> map ) 
{
	mCurrentMap = map;
	mBonusProb = cast<Map>(mCurrentMap)->GetBonusProb();

	std::map< std::string,Ref<GameObject> > info = cast<Map>(mCurrentMap)->Parse();
	mDwall = info["dwall"];
	mUwall = info["uwall"];
	mNpc = info["npc"];
	mPlayer = info["player"];
	mBomb  = Ref<GameObject>(new Sprite);
	mBonus = Ref<GameObject>(new Sprite);
	//mFlame = Ref<GameObject>(new Sprite);

	//mDwall->SetScale(0.7);

	this->AddChild(mDwall);
	this->AddChild(mUwall);
	this->AddChild(mNpc);
	this->AddChild(mPlayer);
	this->AddChild(mBomb);
	this->AddChild(mBonus);
	//this->AddChild(mFlame);
}

GameStage::~GameStage()
{
	std::cout<<"gamestage released"<<std::endl;
}

Ref<GameObject> GameStage::Player()
{
	return mPlayer;
}

bool GameStage::CanPass( GameObject* obj )
{
	//Sprite* dwallContainer = cast<Sprite>(mDwall);
	//Sprite* uwallContainer = cast<Sprite>(mUwall);
	Grid box = obj->GetBoundingBox();
	int cnt = cast<Sprite>(mUwall)->NumOfChild();
	for(int j = 0;j<cnt;++j)
	{
		Ref<GameObject> child = cast<Sprite>(mUwall)->GetChild(j);
		Grid bBox = child->GetBoundingBox();
		if(bBox.Intersect(box))
		{
			return false;
		}
	}
	cnt = cast<Sprite>(mDwall)->NumOfChild();
	for(int i = 0;i<cnt;++i)
	{
		Ref<GameObject> child = cast<Sprite>(mDwall)->GetChild(i);
		Grid bBox = child->GetBoundingBox();
		if(bBox.Intersect(box))
		{
			return false;
		}
	}
	return true;
}

void GameStage::AddBomb( Ref<GameObject> bomb )
{
	cast<Sprite>(mBomb)->AddChild(bomb);
}

Ref<GameObject> GameStage::CreateBonus()
{
	int r = rand()%100+1;
	//int t = mBonusProb["AddBombP"];
	if(r < mBonusProb["AddBombP"])
	{
		return Ref<GameObject> (new BBombPlus);
	}
	//t += mBonusProb["AddFlameP"];
	else if (r< mBonusProb["AddBombP"]+mBonusProb["AddFlameP"])
	{
		return Ref<GameObject> (new BFlamePlus);
	}
	//t += mBonusProb["FasterP"];
	else if (r<mBonusProb["AddBombP"]+mBonusProb["AddFlameP"]+mBonusProb["FasterP"])
	{
		return Ref<GameObject> (new BFaster);
	}
	//t += mBonusProb["PushP"];
	else if (r<mBonusProb["AddBombP"]+mBonusProb["AddFlameP"]+mBonusProb["FasterP"]+mBonusProb["PushP"])
	{
		return Ref<GameObject> (new BPush);
	}
	//t += mBonusProb["TriggerP"];
	else if (r<mBonusProb["AddBombP"]+mBonusProb["AddFlameP"]+mBonusProb["FasterP"]+mBonusProb["PushP"]+mBonusProb["TriggerP"])
	{
		return Ref<GameObject> (new BTrigger);
	}
	//t += mBonusProb["SlowerP"];
	else if (r<mBonusProb["AddBombP"]+mBonusProb["AddFlameP"]+mBonusProb["FasterP"]+mBonusProb["PushP"]+mBonusProb["TriggerP"]+mBonusProb["SlowerP"])
	{
		return Ref<GameObject> (new BSlower);
	}
	//t += mBonusProb["DropP"];
	else if (r<mBonusProb["AddBombP"]+mBonusProb["AddFlameP"]+mBonusProb["FasterP"]+mBonusProb["PushP"]+mBonusProb["TriggerP"]+mBonusProb["SlowerP"]+mBonusProb["DropP"])
	{
		return Ref<GameObject> (new BDrop);
	}
	else
		return Ref<GameObject> (NULL);
}

void GameStage::AddBonus( Ref<GameObject> bonus )
{
	cast<Sprite>(mBonus)->AddChild(bonus);
}

void GameStage::EatBonus( Character* obj )
{
	Grid box = obj->GetBoundingBox();
	int cnt = cast<Sprite>(mBonus)->NumOfChild();
	for(int i = 0;i<cnt;++i)
	{
		Ref<GameObject> child = cast<Sprite>(mBonus)->GetChild(i);
		Grid bBox = child->GetBoundingBox();
		if(bBox.Intersect(box))
		{
			if(typeid(*child) == typeid(BBombPlus))
			{

			}
			else if(typeid(*child) == typeid(BFlamePlus))
			{
				obj->SetPower(1);
			}
			else if(typeid(*child) == typeid(BFaster))
			{
				obj->SetSpeed(1.5);
			}
			else if(typeid(*child) == typeid(BTrigger))
			{

			}
			else if(typeid(*child) == typeid(BPush))
			{

			}
			else if(typeid(*child) == typeid(BSlower))
			{

			}
			else if(typeid(*child) == typeid(BDrop))
			{

			}
			child->RemoveFromParent();
		}
	}
}

bool GameStage::HasUwall( int row,int col )
{
	int cnt = cast<Sprite>(mUwall)->NumOfChild();
	for(int i = 0;i<cnt;++i)
	{
		Ref<GameObject> child = cast<Sprite>(mUwall)->GetChild(i);
		int tRow = child->GetBoundingBox().Row();
		int tCol = child->GetBoundingBox().Col();

		if(row == tRow && col == tCol)
			return true;
	}
	return false;
}

void GameStage::DwallExplode( int row,int col )
{
	//Ref<GameObject> dWall = mDwall;
	Sprite::ChildrenContainer dWall = cast<Sprite>(mDwall)->GetAllChildren();

	int cnt = dWall.size();
	for(int i = 0;i<cnt;++i)
	{
		//Ref<GameObject> child = cast<Sprite>(dWall)->GetChild(i);
		Ref<GameObject> child = dWall[i];
		int tRow = child->GetBoundingBox().Row();
		int tCol = child->GetBoundingBox().Col();

		if(row == tRow && col == tCol)
			child->RemoveFromParent();
	}
}
