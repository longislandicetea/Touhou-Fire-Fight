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
	State(){}
	~State(){}
	void AddTransition(Ref<Transition> transition);
	Ref<State> Update(float dt);
	int GetAction();
protected:
	vector<Ref<Transition>> mTransitionList;
	FSM* mOwner;
	int mTNum;//TransitionNumber
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
	FleeState();
	int GetAction();
};

class SearchBonusState:public State
{
public:
	SearchBonusState();
	int GetAction();
};