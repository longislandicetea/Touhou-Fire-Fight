#include "PlayerController.h"
#include "App.h"

PlayerController::PlayerController()
{
	mIsSpacePressed = false;
	mIsShiftPressed = false;
}

int PlayerController::Update( Character* character,float dt )
{
	Ref<InputSystem> inputSys = App::Inst().InputSys();
	if(inputSys->IsKeyDown(VK_UP))
		return CharacterController::MOVE_UP;
	else if(inputSys->IsKeyDown(VK_DOWN))
		return CharacterController::MOVE_DOWN;
	else if(inputSys->IsKeyDown(VK_LEFT))
		return CharacterController::MOVE_LEFT;
	else if(inputSys->IsKeyDown(VK_RIGHT))
		return CharacterController::MOVE_RIGHT;
	else if(inputSys->IsKeyDown(VK_SPACE))
		mIsSpacePressed = true;
	else if(inputSys->IsKeyDown(VK_SHIFT))
		//return CharacterController::TRIGGER_BOMB;
		mIsShiftPressed = true;
	if(!inputSys->IsKeyDown(VK_SPACE) && mIsSpacePressed)
	{
		mIsSpacePressed = false;
		return CharacterController::DROP_BOMB;
	}
	if(!inputSys->IsKeyDown(VK_SHIFT) && mIsShiftPressed)
	{
		mIsShiftPressed = false;
		return CharacterController::TRIGGER_BOMB;
	}
	return CharacterController::IDLE;
}
