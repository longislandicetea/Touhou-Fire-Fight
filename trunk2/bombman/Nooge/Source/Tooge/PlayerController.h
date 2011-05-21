#pragma once

#include "Character.h"
#include "InputSystem.h"
#include "Ref.h"

class PlayerController :public CharacterController
{
public:
	PlayerController();
	int Update(Character* character,float dt);

private:
};