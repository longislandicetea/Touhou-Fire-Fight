#include"FSM.h"


FSM::FSM(Ref<NPCController> ctrl, Ref<State> startState)//
{
	mCtrl = ctrl;
	mCurrentState = startState;
}

int FSM::Update(float dt)
{
    mCurrentState = mCurrentState->Update(dt);

    return mCurrentState->GetAction();
}

Ref<NPCController>  FSM::GetNPCController()
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



