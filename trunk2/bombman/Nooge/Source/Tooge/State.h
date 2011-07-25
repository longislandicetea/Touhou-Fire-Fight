#pragma once
#include"Ref.h"
#include"Transition.h"
#include"FSM.h"
#include"NPCController.h"
#include<vector>
//using namespace std;

//declaration of class
class State;
class Transition;
class FSM;

class State
{
public:
	enum Action { MOVE_LEFT, MOVE_DOWN, MOVE_RIGHT,  MOVE_UP,DROP_BOMB, TRIGGER_BOMB,IDLE, ACTION_CNT};
	State(NPCController* ctrl);
	virtual ~State(){}
	void AddTransition(Transition* transition);
	State* Update(float dt);
	virtual int GetAction() = 0;
	void SetTimer(bool open);
	double GetTimer();
protected:
	std::vector<Transition*> mTransitionList;
	FSM* mOwner;
	Ref<Timer> mTimer;
	NPCController* mCtrl;
	
};

class ClearPathState:public State
{
public:
	ClearPathState(NPCController* ctrl);
	int GetAction();
};

class FleeState:public State
{
public:
	FleeState(NPCController* ctrl);
	virtual ~FleeState(){};
	virtual int GetAction();
};

class SearchBonusState:public State
{
public:
	SearchBonusState(NPCController* ctrl);
	virtual ~SearchBonusState(){};
	virtual int GetAction();
};

class SillyState:public State
{
public:
	SillyState(NPCController* ctrl);
	virtual ~SillyState(){};
	virtual int GetAction();
};

class FreeState: public State
{
public:
	FreeState(NPCController* ctrl);
	virtual ~FreeState(){};
	virtual int GetAction();
};

class DropBombState: public State
{
public:
	DropBombState(NPCController* ctrl);
	virtual ~DropBombState(){};
	virtual int GetAction();
};

class TriggerState: public State
{
public:
	TriggerState(NPCController* ctrl);
	virtual ~TriggerState(){}
	virtual int GetAction();
};

class AttackState: public State
{
public:
	AttackState(NPCController* ctrl);
	virtual ~AttackState(){}
	virtual int GetAction();
};