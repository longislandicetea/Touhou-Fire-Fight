#pragma  once
#include"Character.h"
#include"Ref.h"

class NPCController : public CharacterController
{
public:
	int Update(Character *character, float dt);
private:
	//void computeFloodFill();
	//void computeConception();
	//Ref<FSM> mFsm;
};