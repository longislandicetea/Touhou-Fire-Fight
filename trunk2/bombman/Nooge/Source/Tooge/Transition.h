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
	Transition(NPCController* ctrl,Ref<State> nextState);
	virtual ~Transition(){};
	Ref<State> GetNextState();
	virtual bool IsTrue() = 0;

protected:
	Ref<State> mNextState;
	NPCController* mCtrl;
	
};

class ToFlee: public Transition
{
public:
	ToFlee(NPCController* ctrl,Ref<State> next);
	virtual bool IsTrue();

};
