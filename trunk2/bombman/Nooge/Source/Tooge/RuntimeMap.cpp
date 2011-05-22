#include "RuntimeMap.h"
#include "Dwall.h"
#include "Uwall.h"
#include "Bonus.h"
#include "Character.h"
#include "PlayerController.h"
#include "Grid.h"

void RuntimeMap::SetMap()
{
	mMap->Load("c:\\test.xml");
	for(int i = 0;i<mMap->mGrids.size();++i)
	{
		GridInfo tmp = mMap->mGrids[i];
		int row = tmp.row;
		int col = tmp.col;

		int side = Grid::SideLen;

		Ref<Grid> currentGrid(new Grid((col-7)*side,(row-5)*side,(col-6)*side,(row-6)*side));

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
				break;
			}
		}
	}
	this->AddChild(mDwall);
	this->AddChild(mUwall);
	this->AddChild(mBonus);
	this->AddChild(mNPC);
	this->AddChild(mPlayer);
}

RuntimeMap::RuntimeMap()
{
	mMap = Ref<Map>(new Map);
	mDwall = Ref<GameObject>(new Sprite);
	mUwall = Ref<GameObject>(new Sprite);
	mBonus = Ref<GameObject>(new Sprite);
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
