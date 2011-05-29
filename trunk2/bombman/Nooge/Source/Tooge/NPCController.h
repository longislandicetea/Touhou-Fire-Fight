#pragma  once
#include"Character.h"
#include"Ref.h"
#include "AIMap.h"

class NPCController : public CharacterController
{
public:
	//NPCController();
	int Update(Character *character, float dt);
	~NPCController();

private:
	//AIMap* mDangerGrid;
	//AIMap* mInterestGrid;
	AIMap* mFloodFillGrid;
	void computeFloodFill(Character *character);
	void computeFloodFill(int x,int y);
	//void computeConception();
	//Ref<FSM> mFsm;
};