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
	Ref<State> GetNextState();
	bool IsTrue();

private:
	Ref<State> mNextState;
	bool mIsTrue;
};