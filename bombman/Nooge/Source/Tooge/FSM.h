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
	FSM(NPCController* ctrl, State* startState);
	int Update(float dt);
	State* CurrentState();
	~FSM(){};
	void AddState(State* state);
	NPCController*  GetNPCController();
private:
	std::vector<State*> mStateList;
	State* mCurrentState;
	NPCController* mCtrl;
	
};

