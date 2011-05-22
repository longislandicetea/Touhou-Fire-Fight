#pragma  once
#include"Character.h"
#include"Ref.h"
#include "AIMap.h"

class NPCController : public CharacterController
{
public:
	int Update(Character *character, float dt);
	~NPCController();

private:
	AIMap* mAIMap;
	void computeFloodFill(Character *character);
	void computeFloodFill(int x,int y);
	//void computeConception();
	//Ref<FSM> mFsm;
};