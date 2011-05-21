#include "PlayerController.h"
#include "App.h"

PlayerController::PlayerController()
{
}

int PlayerController::Update( Character* character,float dt )
{
	Ref<InputSystem> inputSys = App::Inst().InputSys();
	if(inputSys->IsKeyDown(VK_UP))
		return CharacterController::UP;
	else if(inputSys->IsKeyDown(VK_DOWN))
		return CharacterController::DOWN;
	else if(inputSys->IsKeyDown(VK_LEFT))
		return CharacterController::LEFT;
	else if(inputSys->IsKeyDown(VK_RIGHT))
		return CharacterController::RIGHT;
}
