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
	Transition(Ref<State> nextState);
	virtual ~Transition(){};
	Ref<State> GetNextState();
	virtual bool IsTrue() = 0;

private:
	Ref<State> mNextState;
	
};

class ToFlee: public Transition
{
public:
	ToFlee(Ref<State> next);
	//virtual bool IsTrue();

};
