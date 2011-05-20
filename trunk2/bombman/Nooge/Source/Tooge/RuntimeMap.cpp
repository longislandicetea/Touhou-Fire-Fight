#include "RuntimeMap.h"
#include "Dwall.h"
#include "Uwall.h"
#include "Bonus.h"
#include "Character.h"

void RuntimeMap::SetMap()
{
	for(int i = 0;i<mGrids.size();++i)
	{
		GridInfo tmp = mGrids[i];
		int row = tmp.row;
		int col = tmp.col;

		switch (tmp.gridState)
		{
		case DWALL:
		{
			Ref<Dwall> dwall(new Dwall());
			//dwall->SetPos();
		}
		}
	}
}

void RuntimeMap::Update()
{

}

void RuntimeMap::Draw()
{

}
