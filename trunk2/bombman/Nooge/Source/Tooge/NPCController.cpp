#include "NPCController.h"
#include "App.h"
#include "GameStage.h"
#include "RuntimeMap.h"

int NPCController::Update(Character *character, float dt)
{
	return rand() %4;
	mDangerGrid = new AIMap(-1);
	mFloodFillGrid  = new AIMap(100);
	computeFloodFill(character);
	//computePerception(dt);
	//return  mFsm.Update(dt);
	
	return 0;
}

void NPCController::computeFloodFill(Character* character)
{
	int x = character->GetX();
	int y = character->GetZ();
	mFloodFillGrid->Reset(100);
	mFloodFillGrid->SetValue(x,y,0);
	computeFloodFill(x,y);
}

void NPCController::computeFloodFill( int x,int y )
{
	static int dirX[4] = { -1, 0, 1,  0};
	static int dirY[4] = {  0, 1, 0, -1};
	int nextValue = mFloodFillGrid->GetValue(x,y) + 1;
	for (int i = 0; i < 4 ; ++i)
	{
		int nextX = x + dirX[i]; int nextY = y + dirY[i];
		if (mFloodFillGrid->IsFree(nextX, nextY))
		{
			if (nextValue < mFloodFillGrid->GetValue(nextX,nextY))
				mFloodFillGrid->SetValue(nextX, nextY, nextValue);
		}
	}
	for (int i = 0; i < 4 ; ++i)
	{
		int nextX = x + dirX[i]; int nextY = y + dirY[i];
		if (mFloodFillGrid->GetValue(nextX, nextY) == nextValue)
			computeFloodFill(nextX, nextY);
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
