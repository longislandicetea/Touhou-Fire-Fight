#pragma  once
#include"Character.h"
#include"Ref.h"
#include "AIMap.h"
#include"FSM.h"

class NPCController : public CharacterController
{
public:
	NPCController(){};
	int Update(Character *character, float dt);
	AIMap* GetInterestGrid();
	AIMap* GetDangerGrid();
	~NPCController();

	//for AI
	//Character* GetCharacter();

private:
	AIMap* mDangerGrid;
	AIMap* mInterestGrid;
	AIMap* mFloodFillGrid;
	void computeFloodFill(Character *character);
	void computeFloodFill(int x,int y);
	void computePerception(Character* character,float dt);
	void computeDangerGrid(GameStage* gs, Character* character,float dt);
	//Ref<FSM> mFsm;
};

