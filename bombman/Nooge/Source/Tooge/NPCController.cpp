#include "NPCController.h"
#include "App.h"
#include "GameStage.h"
#include "RuntimeMap.h"
#include"AIMap.h"
#include<queue>
using namespace std;

int NPCController::Update(Character *character, float dt)
{
	//return rand() %4;
	mDangerGrid = new AIMap(-1);
	mFloodFillGrid  = new AIMap(100);
	
	//computeFloodFill(character);
	
	//computePerception(character,dt);
	//return  mFsm.Update(dt);

	return 0;
}

void NPCController::computeFloodFill(Character* character)
{
	int x = character->GetBoundingBox().Row();
	int y = character->GetBoundingBox().Col();
	mFloodFillGrid->Reset(100);
	mFloodFillGrid->SetValue(x,y,0);
	computeFloodFill(x,y);
}

void NPCController::computeFloodFill( int x,int y )
{
	static int dirX[4] = { -1, 0, 1,  0};
	static int dirY[4] = {  0, 1, 0, -1};
	queue<pair<int,int>> myQueue;
	myQueue.push(make_pair(x,y));
	//mFloodFillGrid->SetValue(x,y,0);

	while(!myQueue.empty())
	{
		
		pair<int,int> pos = myQueue.front();
		myQueue.pop();
		for(int i = 0;i<4;++i)
		{
			int nextX = pos.first + dirX[i]; int nextY = pos.second + dirY[i];
		if (mFloodFillGrid->IsFree(nextX, nextY) && mFloodFillGrid->IsInside(nextX,nextY) )
		{
			float nextValue = mFloodFillGrid->GetValue(pos.first,pos.second) +1;
			if (nextValue< mFloodFillGrid->GetValue(nextX,nextY))
			{
				mFloodFillGrid->SetValue(nextX, nextY, nextValue);
				myQueue.push(make_pair(nextX,nextY));
			}
		}
		}
	}

	//°¤Ç§µ¶µÄµÝ¹é

	/*int nextValue = mFloodFillGrid->GetValue(x,y) + 1;
	for (int i = 0; i < 4 ; ++i)
	{
		int nextX = x + dirX[i]; int nextY = y + dirY[i];
		if (mFloodFillGrid->IsFree(nextX, nextY) && mFloodFillGrid->IsInside(nextX,nextY) )
		{
			if (nextValue < mFloodFillGrid->GetValue(nextX,nextY))
				mFloodFillGrid->SetValue(nextX, nextY, nextValue);
		}
	}
	for (int i = 0; i < 4 ; ++i)
	{
		int nextX = x + dirX[i]; int nextY = y + dirY[i];
		if ( mFloodFillGrid->IsInside(nextX,nextY) && mFloodFillGrid->GetValue(nextX, nextY) == nextValue)
			computeFloodFill(nextX, nextY);
	}*/
}

void NPCController::computePerception(Character* character, float dt)
{
	//get bomb container
	GameStage* gs = (GameStage*)App::Inst().CurrentStage();
	
	computeDangerGrid(gs,character,dt);
	
}

void NPCController::computeDangerGrid(GameStage* gs, Character* character, float dt)
{
	const int WIDTH = mDangerGrid->GetWidth();
	const int HEIGHT = mDangerGrid->GetHeight();
	//vector<Ref<GameObject>> bombs = (vector<Ref<GameObject>>);
	GameObjectContainer::ChildrenContainer bombs = gs->GetAllBombs();
	int nbomb = bombs.size();
	//compute dangerGrid
	
	for(int t = 0;t<nbomb;++t)
	{
		Bomb* b = cast<Bomb>(gs->GetAllBombs()[t]);
		int power = b->GetPower();
		for(int i = -power;i<=power;++i)
		{
			int row = b->GetBoundingBox().Row();
			int col = b->GetBoundingBox().Col();
			double remain;
			//trigger
			if(b->IsInTriggerState() && character == b->GetOwner())
			{
				continue;
			}
			else
			{
				if(b->IsInTriggerState() && character != b->GetOwner())
					remain = 0;
				else
					remain = 3.0-b->GetTimer()->Last();//3!

				if(row+i>=0 && row+i<=WIDTH)
				{
					mDangerGrid->SetValue(row+i,col,remain);
				}
				if(col+i>=0 && col+i<=HEIGHT)
				{
					mDangerGrid->SetValue(row,col+i,remain);
				}
			}
		}
	}
}

NPCController::~NPCController()
{
	delete mDangerGrid;
	//delete mInterestGrid;
	delete mFloodFillGrid;
}


AIMap* NPCController::GetInterestGrid()
{
	return mInterestGrid;
}

AIMap* NPCController::GetDangerGrid()
{
	return mDangerGrid;
}


