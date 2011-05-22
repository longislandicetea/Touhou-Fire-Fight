#include "NPCController.h"
#include "App.h"
#include "GameStage.h"
#include "RuntimeMap.h"

int NPCController::Update(Character *character, float dt)
{
	return rand() % CharacterController::ACTION_CNT;
	mAIMap = cast<RuntimeMap>(character->GetGameStage()->CurrentMap())->CreateAIMap();
	computeFloodFill(character);
	//computeConception(dt);
	//return  mFsm.Update(dt);
	
	return 0;
}

void NPCController::computeFloodFill(Character* character)
{
	int x = character->GetX();
	int y = character->GetZ();
	mAIMap->Reset(100);
	mAIMap->SetValue(x,y,0);
	computeFloodFill(x,y);
}

void NPCController::computeFloodFill( int x,int y )
{
	static int dirX[4] = { -1, 0, 1,  0};
	static int dirY[4] = {  0, 1, 0, -1};
	int nextValue = mAIMap->GetValue(x,y) + 1;
	for (int i = 0; i < 4 ; ++i)
	{
		int nextX = x + dirX[i]; int nextY = y + dirY[i];
		if (mAIMap->IsFree(nextX, nextY))
		{
			if (nextValue < mAIMap->GetValue(nextX,nextY))
				mAIMap->SetValue(nextX, nextY, nextValue);
		}
	}
	for (int i = 0; i < 4 ; ++i)
	{
		int nextX = x + dirX[i]; int nextY = y + dirY[i];
		if (mAIMap->GetValue(nextX, nextY) == nextValue)
			computeFloodFill(nextX, nextY);
	}
}

NPCController::~NPCController()
{
	delete mAIMap;
}

