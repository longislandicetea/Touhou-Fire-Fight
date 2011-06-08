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

private:
	AIMap* mDangerGrid;
	AIMap* mInterestGrid;
	AIMap* mFloodFillGrid;
	void computeFloodFill(Character *character);
	void computeFloodFill(int x,int y);
	//void computePerception();
	//Ref<FSM> mFsm;
};

