#include "RuntimeMap.h"
#include "Dwall.h"
#include "Uwall.h"
#include "Bonus.h"
#include "Character.h"

void RuntimeMap::SetMap()
{
	mMap->Load("c:\\test.xml");
	for(int i = 0;i<mMap->mGrids.size();++i)
	{
		GridInfo tmp = mMap->mGrids[i];
		int row = tmp.row;
		int col = tmp.col;

		switch (tmp.gridState)
		{
		case DWALL:
			{
				Ref<GameObject> dwall(new Dwall);
				dwall->SetPos((6-col)*10.0,0.0,(row-7)*10.0);
				cast<GameObject,Sprite>(mDwall)->AddChild(dwall);
				break;
			}
		case UWALL:
			{
				Ref<GameObject> uwall(new Uwall);
				uwall->SetPos((6-col)*10.0,0.0,(row-7)*10.0);
				cast<GameObject,Sprite>(mDwall)->AddChild(uwall);
				break;
			}
		case NPC :
			{
			}
		case PLAYER:
			{
			}
		}
	}
	this->AddChild(mDwall);
	this->AddChild(mUwall);
	this->AddChild(mBonus);
	this->AddChild(mNPC);
}

RuntimeMap::RuntimeMap()
{
	mMap = Ref<Map>(new Map);
	mDwall = Ref<GameObject>(new Sprite);
	mUwall = Ref<GameObject>(new Sprite);
	mBonus = Ref<GameObject>(new Sprite);
	mNPC = Ref<GameObject>(new Sprite);
}
