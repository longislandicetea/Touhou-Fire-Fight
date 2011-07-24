#include "NPCController.h"
#include "App.h"
#include "GameStage.h"
#include "RuntimeMap.h"
#include"AIMap.h"
#include<queue>
#include"FSM.h"

#include "BBombPlus.h"
#include "BDrop.h"
#include "BFaster.h"
#include "BFlamePlus.h"
#include "BPush.h"
#include "BSlower.h"
#include "BTrigger.h"

#include "WinFrame.h"

NPCController::NPCController()
{
	mDangerGrid = new AIMap(100);
	mFloodFillGrid  = new AIMap(100);
	mInterestGrid = new AIMap(0);


	initFSM();

}

void NPCController::initFSM()
{

	//states
	flee = new FleeState(this);
	silly = new SillyState(this);
	dropBomb = new DropBombState(this);
	clearPath = new ClearPathState(this);
	trigger = new TriggerState(this);
	attack = new AttackState(this);

	//transitions
	transToFlee = new ToFlee(this,flee);
	transToSilly = new ToSilly(this,silly);
	transToClearPath = new ToClearPath(this,clearPath);
	transToDropBomb = new ToDropBomb(this,dropBomb);
	transToTrigger = new ToTrigger(this,trigger);
	transToAttack = new ToAttack(this,attack);

	//add transitions to states
	flee->AddTransition(transToFlee);
	flee->AddTransition(transToTrigger);
	//flee->AddTransition(transToAttack);
	flee->AddTransition(transToDropBomb);
	flee->AddTransition(transToClearPath);
	flee->AddTransition(transToSilly);

	silly->AddTransition(transToFlee);
	trigger->AddTransition(transToFlee);
	trigger->AddTransition(transToTrigger);
	//trigger->AddTransition(transToAttack);
	trigger->AddTransition(transToDropBomb);
	trigger->AddTransition(transToClearPath);
	trigger->AddTransition(transToSilly);
	
	silly->AddTransition(transToFlee);
	silly->AddTransition(transToTrigger);
	//silly->AddTransition(transToAttack);
	silly->AddTransition(transToDropBomb);
	silly->AddTransition(transToClearPath);
	silly->AddTransition(transToSilly);

	clearPath->AddTransition(transToFlee);
	clearPath->AddTransition(transToTrigger);
	//clearPath->AddTransition(transToAttack);
	clearPath->AddTransition(transToDropBomb);
	clearPath->AddTransition(transToClearPath);
	clearPath->AddTransition(transToSilly);

	dropBomb->AddTransition(transToFlee);
	dropBomb->AddTransition(transToTrigger);
	//dropBomb->AddTransition(transToAttack);
	dropBomb->AddTransition(transToDropBomb);
	dropBomb->AddTransition(transToClearPath);
	dropBomb->AddTransition(transToSilly);

    attack->AddTransition(transToFlee);
	attack->AddTransition(transToTrigger);
	attack->AddTransition(transToAttack);
	attack->AddTransition(transToDropBomb);
	attack->AddTransition(transToClearPath);
	attack->AddTransition(transToSilly);

	//fsm
	mFsm = new FSM(this,silly);
	mFsm->AddState(flee);
	mFsm->AddState(trigger);
	mFsm->AddState(silly);
	mFsm->AddState(dropBomb);
	mFsm->AddState(clearPath);
	mFsm->AddState(attack);

}

int NPCController::Update(Character *character, float dt)
{
	mOwner = character;
	//return rand() %4;
	GameStage* gs = (GameStage*)App::Inst().CurrentStage();

	//reset AIMaps
	mFloodFillGrid->Reset(100);
	mDangerGrid->Reset(100);
	mInterestGrid->Reset(0);
	mNearestBonusPos = Pos(-1,-1);
	mMostInterest = Pos(-1,-1);
	mNearestEnemyPos = Pos(-1,-1);
	mIsTrigChance = false;
	if(!mEnemyPos.empty())
		mEnemyPos.clear();

	computeWalls();

	computePerception(character,dt);
	computeFloodFill(character);
	computeEnemy(gs,character,dt);

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
	if(Dwall != NULL){
	int DwallNum = Dwall->NumOfChild();
	for(int i = 0;i<DwallNum;++i)
	{
		if(!Dwall->GetChild(i).IsNull()) {
		int row = Dwall->GetChild(i)->GetBoundingBox().Row();
		int col = Dwall->GetChild(i)->GetBoundingBox().Col();

		//set Dwall Value
		mFloodFillGrid->SetValue(col,row,-DWALL);
		mDangerGrid->SetValue(col,row,-DWALL);
		mInterestGrid->SetValue(col,row,-DWALL);}

	}
	}
}
void NPCController::computeFloodFill(Character* character)
{
	int row = character->GetBoundingBox().Row();
	int col = character->GetBoundingBox().Col();
	//mFloodFillGrid->Reset(100);
	if(mFloodFillGrid->GetValue(col,row) == 100)//not in the wall( = =+ )
	{
		mFloodFillGrid->SetValue(col,row,0);
		computeFloodFill(col,row);
	}
}
void NPCController::computeFloodFill( int col,int row )
{
	//floodfill by queue

	static int dirX[4] = { -1, 0, 1,  0};
	static int dirY[4] = {  0, 1, 0, -1};
	std::queue<Pos> myQueue;
	myQueue.push(Pos(col,row));

	while(!myQueue.empty())
	{

		Pos pos = myQueue.front();
		myQueue.pop();
		for(int i = 0;i<4;++i)
		{
			int nextX = pos.col + dirX[i]; int nextY = pos.row + dirY[i];
			if (mFloodFillGrid->GetValue(nextX,nextY)!=-UWALL 
				&& mFloodFillGrid->GetValue(nextX,nextY)!=-DWALL 
				&& mFloodFillGrid->IsInside(nextX,nextY) 
				&& mDangerGrid->GetValue(nextX,nextY) >=3.0)//no danger
			{
				float nextValue = mFloodFillGrid->GetValue(pos.col,pos.row) +1;
				if (nextValue< mFloodFillGrid->GetValue(nextX,nextY))
				{
					mFloodFillGrid->SetValue(nextX, nextY, nextValue);
					myQueue.push(Pos(nextX,nextY));
					if(mInterestGrid->GetValue(nextX,nextY)>0 && mDangerGrid->GetValue(nextX,nextY)>=3.0)
					{
						if(mMostInterest == Pos(-1,-1))
							mMostInterest = Pos(nextX,nextY);
						//else if(nextValue<=mFloodFillGrid->GetValue(mMostInterest)
							//&& mInterestGrid->GetValue(nextX,nextY)>mInterestGrid->GetValue(mMostInterest))
						//{
							//mMostInterest = Pos(nextX,nextY);
						//}

					}
				}
			}
		}
	}
	if(  mMostInterest != Pos(-1,-1) 
		&& mNearestBonusPos != Pos(-1,-1)
		&& ((mFloodFillGrid->GetValue(mMostInterest)+3 )>= mFloodFillGrid->GetValue(mNearestBonusPos)))
		mMostInterest = mNearestBonusPos;
	//LogTrace("MostInterestPos: %d  %d\n",mMostInterest.col,mMostInterest.row);
}
stack<Pos> NPCController::getPathTo(int col,int row)
{
	int dirX[4] = { -1, 0, 1,  0};
	int dirY[4] = {  0, 1, 0, -1};

	stack<Pos> path;
	if(mFloodFillGrid->IsInside(col,row))
	{
		float dValue = mFloodFillGrid->GetValue(col,row);
		if(dValue != 100 && dValue != -DWALL && dValue != -UWALL)
		{
			//path.push(Pos(col,row));
			int nextCol = col;
			int nextRow = row;

			while(dValue--)
			{
				path.push(Pos(nextCol,nextRow));
				for(int i = 0;i<4;++i)
				{
					if(mFloodFillGrid->GetValue(nextCol+dirX[i],nextRow+dirY[i])==dValue)
					{
						nextCol = nextCol+dirX[i];
						nextRow = nextRow + dirY[i];
						//path.push(Pos(col+dirX[i],row+dirY[i]));
						break;
					}
				}
			}
		}
	}
	return path;
}
void NPCController::computePerception(Character* character, float dt)
{
	//get bomb container
	GameStage* gs = (GameStage*)App::Inst().CurrentStage();

	computeDangerGrid(gs,character,dt);
	computeInterestGrid(gs,character,dt);
}

void NPCController::computeEnemy(GameStage* gs, Character* character, float dt)
{
	GameObjectContainer* npc = cast<GameObjectContainer>(gs->GetChild(NPC));
	GameObjectContainer* player = cast<GameObjectContainer>(gs->GetChild(PLAYER));
	mEnemyPos;

	//add player
	if(player != NULL) {GameObject* play = cast<GameObject>(player->GetChild(0));
	mNearestEnemyPos = Pos(play->GetBoundingBox().Col(),play->GetBoundingBox().Row());
	mEnemyPos.push_back(mNearestEnemyPos);}

	//compare npcs
	if(npc!=NULL) {
	for(int i = 0;i<npc->NumOfChild();++i)
	{
		GameObject * child = cast<GameObject>(npc->GetChild(i));
		if(child != NULL) {
		if(child != character)
		{
			Pos pos = Pos(child->GetBoundingBox().Col(),child->GetBoundingBox().Row());
			//if(mFloodFillGrid->GetValue(mNearestEnemyPos) !=)
			mEnemyPos.push_back(pos);
			if(mFloodFillGrid->GetValue(mNearestEnemyPos) > mFloodFillGrid->GetValue(pos))
			{
				mNearestEnemyPos = Pos(pos);
			}
		}
		}
	}
	}
	if(mFloodFillGrid->GetValue(mNearestEnemyPos) == 100)
		mNearestEnemyPos = Pos(-1,-1);

	if(character->HasTrigBonus() && mDangerGrid->GetValue(character->GetBoundingBox().Col(),character->GetBoundingBox().Row())!=-5)
	{
		for(int i = 0;i<mEnemyPos.size();++i)
		{
			if(mDangerGrid->GetValue(mEnemyPos[i]) == -5)
				mIsTrigChance = true;
		}
	}
}

std::vector<Pos> NPCController::GetEnemyPos()
{
	return mEnemyPos;
}

std::stack<Pos> NPCController::getPathTo(Pos pos)
{
	std::stack<Pos> path = getPathTo(pos.col,pos.row);
	return path;
}
Pos NPCController::MostInterestPos()
{
	return mMostInterest;
}

Pos NPCController::NearestEnemyPos()
{
	return mNearestEnemyPos;
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

		int dx[4] = {-1,0,1,0};
		int dy[4] = {0,1,0,-1};
		
		int dValid[4] = {1,1,1,1};
		for(int i = 0;i<=power;++i)
		{
			int row = b->GetBoundingBox().Row();
			int col = b->GetBoundingBox().Col();

			double remain;

			//trigger
			if(b->IsInTriggerState() && character == b->GetOwner())
			{
				remain = -5;
			}
			else if(b->IsInTriggerState() && character != b->GetOwner())   //trigger bomb is not mine!
				remain = 0;
			else
				remain = 3.0-b->GetTimer()->Last();   //not trigger bomb

			for(int j = 0;j<4;++j)
			{
				if(dValid[j])
				{
					int nRow = row + i*dx[j];
					int nCol = col + i*dy[j];
					float rowValue = mDangerGrid->GetValue(nCol,nRow);
					if(rowValue != -UWALL)
					{
						if(rowValue!=-DWALL && remain<rowValue)
							mDangerGrid->SetValue(nCol,nRow,remain);
					}
					else
						dValid[j] = 0;
				}
			}
		}
	}
}
void NPCController::computeInterestGrid(GameStage*gs,Character* character,float dt)
{

	//about Bonuses
	computeBonus(gs,character,dt);

	//aboutDwalls
	computeDwall(gs,character,dt);

}

void NPCController::computeDwall(GameStage* gs,Character* character,float dt)
{
	const int dx[4] = {-1,0,1,0};
	const int dy[4] = {0,1,0,-1};
	GameObjectContainer* dwall = cast<GameObjectContainer>(gs->GetChild(DWALL));
	if(dwall!= NULL) {
	int ndwall = dwall->NumOfChild();
	for(int t = 0;t<ndwall;++t)
	{
		Ref<GameObject> child = dwall->GetChild(t);
		if(!child.IsNull()) {
		int col = child->GetBoundingBox().Col();
		int row = child->GetBoundingBox().Row();
		for(int i = 0;i<4;++i)
		{
			int value = mInterestGrid->GetValue(col+dx[i],row+dy[i]);
			if(value!=-UWALL && value!=-DWALL)
			{
				mInterestGrid->SetValue(col+dx[i],row+dy[i],value+1);
			}
		}
		}
	}
	}
}

void NPCController::computeBonus(GameStage*gs,Character*character,float dt)
{
	GameObjectContainer* bonus = cast<GameObjectContainer>(gs->GetChild(BONUS));
	if(bonus!=NULL) {
	int nbonus = bonus->NumOfChild();

	for(int t = 0;t<nbonus;++t)
	{
		Bonus* child = cast<Bonus>(bonus->GetChild(t));
		if(child != NULL) {
		if(child->GetTimer()->End()>1.5)//time for NPCs to detect the bonus
		{
			if(typeid(*child) == typeid(BFlamePlus) || typeid(*child) == typeid(BBombPlus)
				|| typeid(*child) == typeid(BFaster)
				|| typeid(*child) == typeid(BTrigger)
				|| typeid(*child) == typeid(BPush))
			{
				int col = child->GetBoundingBox().Col();
				int row = child->GetBoundingBox().Row();

				//interestGrid
				mInterestGrid->SetValue(col,row,4);

			}
			else if(typeid(*child)== typeid(BSlower)|| typeid(*child)== typeid(BDrop))
			{
				mInterestGrid->SetValue(child->GetBoundingBox().Col(),child->GetBoundingBox().Row(),-5);
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

	
	//flee
	delete flee;
	delete transToFlee;
	//silly
	delete silly;
	delete transToSilly;
	//clearPath
	delete clearPath;
	delete transToClearPath;
	//dropBomb
	delete dropBomb;
	delete transToDropBomb;
	//trigger
	delete trigger;
	delete transToTrigger;
	//attack
	delete attack;
	delete transToAttack;
}

Pos NPCController::NearestBonusPos()
{
	return mNearestBonusPos;
}

bool NPCController::IsTrigChance()
{
	return mIsTrigChance;
}


AIMap* NPCController::GetInterestGrid()
{
	return mInterestGrid;
}

AIMap* NPCController::GetDangerGrid()
{
	return mDangerGrid;
}


