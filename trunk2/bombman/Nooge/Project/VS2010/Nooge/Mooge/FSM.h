#pragma once
#include"Ref.h"
#include"NPCController.h"

//declaration of class
class State;
class Transition;
class FSM;

class FSM
{
public:
	FSM(){};
	int Update(float dt);
	//Ref<State> CurrentState();
	//NPCController* getNPCController();
private:
	State mStateList[N];//N?????
	Ref<State> mCurrentState;
	NPCController* mCtrl;


};

class Transition
{
public:
	//Transition();
	//Ref<State> GetNextState();
	//bool IsTrue();

private:
	Ref<State> mNextState;
	bool mIsTrue;//??????
};

class State
{
public:
	//State();
	//Ref<State> Update();
	//int GetAction();
private:
	Transition mTransitionList[N];//N???
	FSM* mOwner;
};

class ClearPathState:public State
{
public:
	//ClearPathState();
	//int GetAction();
};

class FleeState:public State
{
public:
	//FleeState();
	//int GetAction();
};

class SearchBonusState:public State
{
public:
	//SearchBonusState();
	//int GetAction();
};

