#include"FSM.h"


FSM::FSM(NPCController* ctrl, Ref<State> startState)//
{
	mCtrl = ctrl;
	mCurrentState = startState;
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

Ref<State> FSM::CurrentState()
{
	return mCurrentState;
}

void FSM::AddState(Ref<State> state)
{
	mStateList.push_back(state);
}



