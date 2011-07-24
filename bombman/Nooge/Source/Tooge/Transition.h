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
	Transition(NPCController* ctrl,State* nextState);
	virtual ~Transition(){};
	State* GetNextState();
	virtual bool IsTrue() = 0;

protected:
	State* mNextState;
	NPCController* mCtrl;
	
};

class ToFlee: public Transition
{
public:
	ToFlee(NPCController* ctrl,State* next);
	virtual bool IsTrue();

};

class ToSilly: public Transition
{
public:
	ToSilly(NPCController* ctrl,State* next);
	virtual bool IsTrue();
};

class ToSearchBonus: public Transition
{
public:
	ToSearchBonus(NPCController* ctrl,State* next);
	virtual bool IsTrue();
};

class ToOpen: public Transition
{
public:
	ToOpen(NPCController* ctrl,State*next);
	virtual bool IsTrue();
};

class ToDropBomb: public Transition
{
public:
	ToDropBomb(NPCController* ctrl, State* next);
	virtual bool IsTrue();
};

class ToClearPath: public Transition
{
public:
	ToClearPath(NPCController* ctrl, State* next);
	virtual bool IsTrue();
};

class ToTrigger: public Transition
{
public:
	ToTrigger(NPCController* ctrl, State* next);
	virtual bool IsTrue();
};

class ToAttack: public Transition
{
public:
	ToAttack(NPCController* ctrl, State* next);
	virtual bool IsTrue();
};
