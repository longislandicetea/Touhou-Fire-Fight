#pragma  once
#include"Character.h"
#include"Ref.h"
#include "AIMap.h"
//#include"FSM.h"

class FSM;
//class State;
//class FleeState;

//class Transition;


typedef struct
{
	int row;
	int col;
}Pos;

class NPCController : public CharacterController
{
public:
	NPCController();
	int Update(Character *character, float dt);
	AIMap* GetInterestGrid();
	AIMap* GetDangerGrid();
	~NPCController();

	//for AI
	//Character* GetCharacter();

private:
enum AIGridState
{
	FLOOR,DWALL,UWALL,NPC,PLAYER,BOMB,BONUS,HDU
};

	AIGridState mAIGrid;
	AIMap* mDangerGrid;
	AIMap* mInterestGrid;
	AIMap* mFloodFillGrid;
	void computeFloodFill(Character *character);
	void computeFloodFill(int x,int y);
	void computePerception(Character* character,float dt);
	void computeDangerGrid(GameStage* gs, Character* character,float dt);
	
	void computeWalls();
	void initFSM();
	
	Ref<FSM> mFsm;
};

