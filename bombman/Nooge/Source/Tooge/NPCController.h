#pragma  once
#include"Character.h"
#include"Ref.h"
#include "AIMap.h"
#include<stack>
//#include"FSM.h"

class FSM;
class State;
class FleeState;
class SillyState;
class SearchBonusState;
class OpenState;
class ClearPathState;
class DropBombState;

class Transition;
class ToFlee;
class ToSilly;
class ToSearchBonus;
class ToOpen;
class ToDropBomb;
class ToClearPath;




class NPCController : public CharacterController
{
public:
	NPCController();
	int Update(Character *character, float dt);
	AIMap* GetInterestGrid();
	AIMap* GetDangerGrid();
	~NPCController();
	

	//for AI
	Pos NearestBonusPos();
	Pos MostInterestPos();
	Pos NearestEnemyPos();
	std::stack<Pos> getPathTo(int col,int row);
	std::stack<Pos> getPathTo(Pos pos);
	bool IsTrigChance();

private:
enum AIGridState
{
	FLOOR,DWALL,UWALL,NPC,PLAYER,BOMB,BONUS,HDU
};

	AIGridState mAIGrid;
	AIMap* mDangerGrid;
	AIMap* mInterestGrid;
	AIMap* mFloodFillGrid;
	Pos mNearestBonusPos;//the position of the nearest bonus
	Pos mMostInterest;
	Pos mNearestEnemyPos;
	bool mIsTrigChance;
	void computeFloodFill(Character *character);
	void computeFloodFill(int col,int row);
	
	void computePerception(Character* character,float dt);
	void computeDangerGrid(GameStage* gs, Character* character,float dt);
	void computeInterestGrid(GameStage*gs,Character* character,float dt);
	void computeBonus(GameStage*gs,Character*character,float dt);
	void computeDwall(GameStage* gs,Character* character,float dt);
	void computeEnemy(GameStage* gs, Character* character, float dt);

	void computeWalls();
	void initFSM();
	
	FSM* mFsm;

	State* flee;
	Transition* transToFlee;
	
	State* silly;
	Transition* transToSilly;

	State* dropBomb;
	Transition* transToDropBomb;

	State* clearPath;
	Transition* transToClearPath;

	State* trigger;
	Transition* transToTrigger;
};

