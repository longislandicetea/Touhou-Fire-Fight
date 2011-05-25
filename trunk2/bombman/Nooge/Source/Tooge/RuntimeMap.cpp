#include "RuntimeMap.h"
#include "Dwall.h"
#include "Uwall.h"
#include "Bonus.h"
#include "Character.h"
#include "PlayerController.h"
#include "NPCController.h"
#include "Grid.h"
#include "AIMap.h"

void RuntimeMap::LoadMap()
{
	mMap->Load("c:\\test.xml");
	for(int i = 0;i<mMap->mGrids.size();++i)
	{
		GridInfo tmp = mMap->mGrids[i];
		int row = tmp.row;
		int col = tmp.col;

		Ref<Grid> currentGrid(new Grid(row,col));

		switch (tmp.gridState)
		{
		case DWALL:
			{
				Ref<GameObject> dwall(new Dwall);
				dwall->SetPos(currentGrid->CenterX(),0.0,currentGrid->CenterY());
				cast<Sprite>(mDwall)->AddChild(dwall);
				break;
			}
		case UWALL:
			{
				Ref<GameObject> uwall(new Uwall);
				uwall->SetPos(currentGrid->CenterX(),0.0,currentGrid->CenterY());
				cast<Sprite>(mUwall)->AddChild(uwall);
				break;
			}
		case PLAYER:
			{
				PlayerController* playerCtrl = new PlayerController();
				Ref<GameObject> player = Character::AddController(playerCtrl);
				player->SetPos(currentGrid->CenterX(),0.0,currentGrid->CenterY());
				player->SetRotateY(90);
				cast<Sprite>(mPlayer)->AddChild(player);
				break;
			}
		case NPC :
			{
				NPCController* npcCtrl = new NPCController();
				Ref<GameObject> npc = Character::AddController(npcCtrl);
				npc->SetPos(currentGrid->CenterX(),0.0,currentGrid->CenterY());
				npc->SetRotateY(90);
				cast<Sprite>(mNPC)->AddChild(npc);
				break;
			}
		}
	}
	this->AddChild(mDwall);
	this->AddChild(mUwall);
	//this->AddChild(mBonus);
	this->AddChild(mNPC);
	this->AddChild(mPlayer);
	this->AddChild(mBomb);
}

RuntimeMap::RuntimeMap()
{
	mMap = Ref<Map>(new Map);
	mDwall = Ref<GameObject>(new Sprite);
	mUwall = Ref<GameObject>(new Sprite);
	mBomb = Ref<GameObject>(new Sprite);
	//mBonus = Ref<GameObject>(new Sprite);
	mNPC = Ref<GameObject>(new Sprite);
	mPlayer = Ref<GameObject>(new Sprite);
}

bool RuntimeMap::CanPass( GameObject* obj )
{
	GameObjectContainer* dwallContainer = cast<GameObjectContainer>(mDwall);
	GameObjectContainer* uwallContainer = cast<GameObjectContainer>(mUwall);
	/*for(int i = 0;i<dwallContainer->NumOfChild();++i)
	{
		if(dwallContainer->GetChild(i)->GetBoundingBox().Intersect(obj->GetBoundingBox()))
		{
			return false;
			break;
		}
	}*/
	for(int j = 0;j<uwallContainer->NumOfChild();++j)
	{
		if(uwallContainer->GetChild(j)->GetBoundingBox().Intersect(obj->GetBoundingBox()))
		{
			return false;
			break;
		}
	}
	return true;
}

void RuntimeMap::AddBomb(Ref<GameObject> bomb)
{
	cast<GameObjectContainer>(mBomb)->AddChild(bomb);

}

/*AIMap* RuntimeMap::CreateAIMap()
{
	AIMap* aiMap = new AIMap(100);

	GameObjectContainer* dwallContainer = cast<GameObjectContainer>(mDwall);
	GameObjectContainer* uwallContainer = cast<GameObjectContainer>(mUwall);
	for(int i = 0;i<dwallContainer->NumOfChild();++i)
	{
		int row = dwallContainer->GetChild(i)->GetBoundingBox().Row();
		int col = dwallContainer->GetChild(i)->GetBoundingBox().Col();
		aiMap->SetValue(row,col,-1);
	}
	for(int j = 0;j<uwallContainer->NumOfChild();++j)
	{
		int row = uwallContainer->GetChild(j)->GetBoundingBox().Row();
		int col = uwallContainer->GetChild(j)->GetBoundingBox().Col();
		aiMap->SetValue(row,col,-1);
	}
	return aiMap;
}*/
