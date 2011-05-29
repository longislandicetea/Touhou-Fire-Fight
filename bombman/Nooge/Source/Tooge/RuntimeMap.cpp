#include "RuntimeMap.h"
#include "Dwall.h"
#include "Uwall.h"
#include "Bonus.h"
#include "Character.h"
#include "PlayerController.h"
#include "NPCController.h"
#include "Grid.h"
#include "AIMap.h"

RuntimeMap::RuntimeMap(float playerX,float playerY)
{
	mDwall = Ref<GameObject>(new Sprite);
	mUwall = Ref<GameObject>(new Sprite);
	mBomb = Ref<GameObject>(new Sprite);
	//mBonus = Ref<GameObject>(new Sprite);
	mNPC = Ref<GameObject>(new Sprite);

	this->AddChild(mDwall);
	this->AddChild(mUwall);
	//this->AddChild(mBonus);
	this->AddChild(mNPC);
	this->AddChild(mBomb);
}

bool RuntimeMap::CanPass( GameObject* obj )
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
