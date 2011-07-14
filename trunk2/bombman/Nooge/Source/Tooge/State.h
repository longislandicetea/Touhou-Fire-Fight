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
	State(Ref<NPCController> ctrl);
	virtual ~State(){}
	void AddTransition(Ref<Transition> transition);
	Ref<State> Update(float dt);
	virtual int GetAction() = 0;
protected:
	vector<Ref<Transition>> mTransitionList;
	FSM* mOwner;

	Ref<NPCController> mCtrl;
	
};

class ClearPathState:public State
{
public:
	ClearPathState();
	int GetAction();
};

class FleeState:public State
{
public:
	FleeState(Ref<NPCController> ctrl);
	virtual ~FleeState(){};
	int GetAction();
};

class SearchBonusState:public State
{
public:
	SearchBonusState();
	int GetAction();
};