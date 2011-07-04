#pragma once
#include"Ref.h"
#include"NPCController.h"

//declaration of class
class State;
class Transition;
class FSM;

class Transition
{
public:
	Transition();
	State* GetNextState();
	bool IsTrue();

private:
	State* mNextState;
	bool mIsTrue;//??????
};