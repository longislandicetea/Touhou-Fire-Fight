#include "NPCController.h"

int NPCController::Update(Character *character, float dt)
{
	return rand() % CharacterController::ACTION_CNT;
}

