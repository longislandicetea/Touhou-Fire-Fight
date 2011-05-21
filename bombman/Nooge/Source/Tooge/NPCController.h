#pragma  once
#include"Character.h"

class NPCController : public CharacterController
{
public:
	int Update(Character *character, float dt);
};