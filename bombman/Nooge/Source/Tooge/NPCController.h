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

class Transition;
class ToFlee;
class ToSilly;
class ToSearchBonus;


struct Pos
{
	int row;
	int col;
public:
	Pos(int tcol,int trow){row = trow;col = tcol;}
	Pos(){}
	//"=="
	bool operator == (const Pos& pos)
	{
		if(this->col == pos.col && this->row == pos.row)
			return true;
		return false;
	}
	
};

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
	std::stack<Pos> getPathTo(int col,int row);
	std::stack<Pos> getPathTo(Pos pos);

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
	void computeFloodFill(Character *character);
	void computeFloodFill(int col,int row);
	
	void computePerception(Character* character,float dt);
	void computeDangerGrid(GameStage* gs, Character* character,float dt);
	void computeInterestGrid(GameStage*gs,Character* character,float dt);

	void computeWalls();
	void initFSM();
	
	FSM* mFsm;
	State* flee;
	Transition* transToFlee;
	
	State* silly;
	Transition* transToSilly;

	State* searchBonus;
	Transition* transToSearchBonus;
};

