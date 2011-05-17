#pragma  once
#include"Character.h"

class NPCController : public Character
{
public:
	int Update(Character *character, float dt);
};