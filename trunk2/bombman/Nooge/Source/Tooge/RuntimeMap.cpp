#include "RuntimeMap.h"
#include "Dwall.h"
#include "Uwall.h"
#include "Bonus.h"
#include "Character.h"
#include "Grid.h"

void RuntimeMap::SetMap()
{
	mMap->Load("c:\\test.xml");
	for(int i = 0;i<mMap->mGrids.size();++i)
	{
		GridInfo tmp = mMap->mGrids[i];
		int row = tmp.row;
		int col = tmp.col;

		Ref<Grid> currentGrid(new Grid((col-7)*mSide,(row-5)*mSide,(col-6)*mSide,(row-6)*mSide));

		switch (tmp.gridState)
		{
		case DWALL:
			{
				Ref<GameObject> dwall(new Dwall);
				dwall->SetPos(currentGrid->CenterX(),0.0,currentGrid->CenterY());
				cast<GameObject,Sprite>(mDwall)->AddChild(dwall);
				break;
			}
		case UWALL:
			{
				Ref<GameObject> uwall(new Uwall);
				uwall->SetPos(currentGrid->CenterX(),0.0,currentGrid->CenterY());
				cast<GameObject,Sprite>(mDwall)->AddChild(uwall);
				break;
			}
		case NPC :
			{
			}
		case PLAYER:
			{
				mPlayer->SetPos(currentGrid->CenterX(),0.0,currentGrid->CenterY());
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
	mSide = 10.0;
}
