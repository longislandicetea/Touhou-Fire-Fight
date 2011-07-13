#pragma once
#include"Ref.h"
#include"State.h"
#include"Transition.h"
#include"NPCController.h"
#include<vector>
using namespace std;

//declaration of class
class State;
class Transition;
class FSM;

class FSM
{
public:
	FSM(Ref<State> startState);
	int Update(float dt);
	Ref<State> CurrentState();
	~FSM(){};
	void AddState(Ref<State> state);
	//NPCController *  GetNPCController();
private:
	vector<Ref<State>> mStateList;
	Ref<State> mCurrentState;
	//NPCController* mCtrl;
	

};

