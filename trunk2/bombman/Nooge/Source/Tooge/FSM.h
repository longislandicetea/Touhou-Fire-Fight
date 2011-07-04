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
	FSM();
	int Update(float dt);
	State* CurrentState();
	//NPCController *  GetNPCController();
private:
	vector<State*> mStateList;
	State* mCurrentState;
	//NPCController* mCtrl;
	int mSNum;//StateNumber

};

