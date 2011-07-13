#include"FSM.h"


FSM::FSM(Ref<State> startState)
{
	mCurrentState = startState;
}

int FSM::Update(float dt)
{
    mCurrentState = mCurrentState->Update(dt);

    return mCurrentState->GetAction();
}

/*NPCController*  FSM::GetNPCController()
{
	return mCtrl;
}*/

Ref<State> FSM::CurrentState()
{
	return mCurrentState;
}

void FSM::AddState(Ref<State> state)
{
	mStateList.push_back(state);
}



