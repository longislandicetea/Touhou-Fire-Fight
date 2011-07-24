#include"FSM.h"


FSM::FSM(NPCController* ctrl, State* startState)//
{
	mCtrl = ctrl;
	mCurrentState = startState;
	startState->SetTimer(true);
}

int FSM::Update(float dt)
{
    mCurrentState = mCurrentState->Update(dt);
	int temp = mCurrentState->GetAction();
    return temp;
}

NPCController*  FSM::GetNPCController()
{
	return mCtrl;
}

State* FSM::CurrentState()
{
	return mCurrentState;
}

void FSM::AddState(State* state)
{
	mStateList.push_back(state);
}



