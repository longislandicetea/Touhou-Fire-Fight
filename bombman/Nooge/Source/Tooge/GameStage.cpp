#include "GameStage.h"

#include <iostream>
#include "PlayerController.h"

Ref<GameObject> GameStage::CurrentMap()
{
	return mCurrentMap;
}

GameStage::GameStage( Ref<GameObject> map ) 
{
	mCurrentMap = map;

	std::map< std::string,Ref<GameObject> > info = cast<Map>(mCurrentMap)->Parse();
	mDwall = info["dwall"];
	mUwall = info["uwall"];
	mNpc = info["npc"];
	mPlayer = info["player"];
	mBomb  = Ref<GameObject>(new Sprite);
	
	this->AddChild(mDwall);
	this->AddChild(mUwall);
	this->AddChild(mNpc);
	this->AddChild(mPlayer);
	this->AddChild(mBomb);
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
	Sprite* dwallContainer = cast<Sprite>(mDwall);
	Sprite* uwallContainer = cast<Sprite>(mUwall);
	/*for(int i = 0;i<dwallContainer->NumOfChild();++i)
	{
		if(dwallContainer->GetChild(i)->GetBoundingBox().Intersect(obj->GetBoundingBox()))
		{
			return false;
			break;
		}
	}*/
	Grid box = obj->GetBoundingBox();
	for(int j = 0;j<uwallContainer->NumOfChild();++j)
	{
		Ref<GameObject> child = uwallContainer->GetChild(j);
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
