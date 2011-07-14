#include "NPCController.h"
#include "App.h"
#include "GameStage.h"
#include "RuntimeMap.h"
#include"AIMap.h"
#include<queue>
//using namespace std;
#include"FSM.h"//???

NPCController::NPCController()
{
	mDangerGrid = new AIMap(100);
	mFloodFillGrid  = new AIMap(100);
	mInterestGrid = new AIMap(0);
	
	initFSM();

}

	/*// Higher level state machine
	State* idle = new IdleState();
	State* fight = new FightState();
	FSM* fsm = new FSM(idle);

	Transition * trueFight = new AllwaysTrue(fight);
	idle->addTransition(trueFight);
	Transition * trueFire = new AllwaysTrue(fire);
	fight->addTransition(trueFire);

	fsm->addState(idle);
	fsm->addState(fight);
	fsm->addState(fire);

	// Update many times
	fsm->update();
	fsm->update();
	fsm->update();
	fsm->update();
	fsm->update();*/
void NPCController::initFSM()
{

	//states
	//Ref<State> flee(new FleeState(this));
	 flee = new FleeState(this);

	
	//transitions
	//Ref<Transition> toFlee(new ToFlee(this,flee));
	 transToFlee = new ToFlee(this,flee);
	flee->AddTransition(transToFlee);//notice prority
	

	//fsm
	//mFsm = Ref<FSM>(new FSM(this,flee));
	mFsm = new FSM(this,flee);
	mFsm->AddState(flee);

}

int NPCController::Update(Character *character, float dt)
{
	mOwner = character;
	//return rand() %4;

	//reset AIMaps
	mFloodFillGrid->Reset(100);
	mDangerGrid->Reset(100);
	mInterestGrid->Reset(0);

	computeWalls();
	
	computeFloodFill(character);
	
	//computePerception(character,dt);
	return  mFsm->Update(dt);

	return 0;
}

void NPCController::computeWalls()
{
	GameStage* gs = (GameStage*)App::Inst().CurrentStage();
	//set UWALL
	GameObjectContainer* Uwall = cast<GameObjectContainer>( gs->GetChild(UWALL));
	int UwallNum = Uwall->NumOfChild();
	for(int i = 0;i<UwallNum;++i)
	{
		int row = Uwall->GetChild(i)->GetBoundingBox().Row();
		int col = Uwall->GetChild(i)->GetBoundingBox().Col();
		
		//set Uwall Value
		mFloodFillGrid->SetValue(col,row,-UWALL);
		mDangerGrid->SetValue(col,row,-UWALL);
		mInterestGrid->SetValue(col,row,-UWALL);
	}

	//set DWALL
	GameObjectContainer* Dwall = cast<GameObjectContainer>(gs->GetChild(DWALL));
	int DwallNum = Dwall->NumOfChild();
	for(int i = 0;i<DwallNum;++i)
	{
		int row = Dwall->GetChild(i)->GetBoundingBox().Row();
		int col = Dwall->GetChild(i)->GetBoundingBox().Col();

		//set Dwall Value
		mFloodFillGrid->SetValue(col,row,-DWALL);
		mDangerGrid->SetValue(col,row,-DWALL);
		mInterestGrid->SetValue(col,row,-DWALL);

	}
}
void NPCController::computeFloodFill(Character* character)
{
	int x = character->GetBoundingBox().Row();
	int y = character->GetBoundingBox().Col();
	//mFloodFillGrid->Reset(100);
	if(mFloodFillGrid->GetValue(x,y) == 100)//not in the wall( = =+ )
	{
	mFloodFillGrid->SetValue(x,y,0);
	computeFloodFill(x,y);
	}
}

void NPCController::computeFloodFill( int x,int y )
{
	//floodfill by queue

	static int dirX[4] = { -1, 0, 1,  0};
	static int dirY[4] = {  0, 1, 0, -1};
	std::queue<pair<int,int>> myQueue;
	myQueue.push(make_pair(x,y));
	

	while(!myQueue.empty())
	{
		
		pair<int,int> pos = myQueue.front();
		myQueue.pop();
		for(int i = 0;i<4;++i)
		{
			int nextX = pos.first + dirX[i]; int nextY = pos.second + dirY[i];
			if (mFloodFillGrid->GetValue(nextX,nextY)!=-UWALL && mFloodFillGrid->GetValue(nextX,nextY)!=-DWALL && mFloodFillGrid->IsInside(nextX,nextY) )
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
	
	GameObjectContainer::ChildrenContainer bombs = gs->GetAllBombs();
	int nbomb = bombs.size();
	

	
	for(int t = 0;t<nbomb;++t)
	{
		Bomb* b = cast<Bomb>(gs->GetAllBombs()[t]);
		int power = b->GetPower();
		
		int rowCount = 0; int colCount =0;
		for(int i = -power;i<=power;++i)
		{
			int row = b->GetBoundingBox().Row();
			int col = b->GetBoundingBox().Col();
			
			double remain;
			
			//trigger
			if(b->IsInTriggerState() && character == b->GetOwner())         //trigger bomb is mine~
			{
				continue;
			}
			else
			{
				if(b->IsInTriggerState() && character != b->GetOwner())   //trigger bomb is not mine!
					remain = 0;
				else
					remain = 3.0-b->GetTimer()->Last();   //not trigger bomb

				//compute dangerous rows
				if(row+i>=0 && row+i<=WIDTH)
				{
					float rowValue = mDangerGrid->GetValue(row+i,col);
					
					if(rowValue!=-DWALL && rowValue != -UWALL)
					{
						   if(rowCount ==1|| rowCount ==0 )
						   {
							   rowCount =1 ;
							   mDangerGrid->SetValue(col, row+i,remain);
						   }
					}
					else 
					{
						if(rowCount == 1)
							rowCount = 2;
					}
					
				}

				//compute dangerous cols
				if(col+i>=0 && col+i<=HEIGHT)
				{
					float colValue = mDangerGrid->GetValue(col,row+i);
					if(colValue!=-DWALL && colValue != -UWALL)
					{
						if(colCount == 1 || colCount == 0)
						{
							colCount = 1;
							mDangerGrid->SetValue(col,row+i,remain);
						}
					}
					else
					{
						if(colCount == 1)
							colCount = 2;
					}
				}
			}
		}
	}
}

NPCController::~NPCController()
{
	delete mDangerGrid;
	delete mInterestGrid;
	delete mFloodFillGrid;
	delete mFsm;

	//temp
	delete flee;
	delete transToFlee;
}


AIMap* NPCController::GetInterestGrid()
{
	return mInterestGrid;
}

AIMap* NPCController::GetDangerGrid()
{
	return mDangerGrid;
}


