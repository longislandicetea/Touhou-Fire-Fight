#pragma once
#include"Ref.h"
#include"Transition.h"
#include"FSM.h"
#include"NPCController.h"
#include<vector>
using namespace std;

//declaration of class
class State;
class Transition;
class FSM;

class State
{
public:
	enum Action { MOVE_UP, MOVE_DOWN, MOVE_RIGHT, MOVE_LEFT, DROP_BOMB, TRIGGER_BOMB,IDLE, ACTION_CNT};
	State(NPCController* ctrl);
	virtual ~State(){}
	void AddTransition(Transition* transition);
	State* Update(float dt);
	virtual int GetAction() = 0;
protected:
	vector<Transition*> mTransitionList;
	FSM* mOwner;

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

class OpenState: public State
{
public:
	OpenState(NPCController* ctrl);
	virtual ~OpenState(){};
	virtual int GetAction();
};

class DropBombState: public State
{
public:
	DropBombState(NPCController* ctrl);
	virtual ~DropBombState(){};
	virtual int GetAction();
};