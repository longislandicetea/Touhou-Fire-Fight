#pragma once

#include<vector>
//using namespace std;

#include"Ref.h"
#include"State.h"
#include"Transition.h"
#include"NPCController.h"
//declaration of class
class State;
class Transition;
class FSM;

class FSM
{
public:
	FSM(Ref<NPCController> ctrl, Ref<State> startState);//
	int Update(float dt);
	Ref<State> CurrentState();
	~FSM(){};
	void AddState(Ref<State> state);
	Ref<NPCController>  GetNPCController();
private:
	std::vector<Ref<State>> mStateList;
	Ref<State> mCurrentState;
	Ref<NPCController> mCtrl;
	
};
