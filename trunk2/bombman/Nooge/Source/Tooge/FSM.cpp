#include"FSM.h"


FSM::FSM()
{
	//mStateList.push_back(Ref<State>(new FleeState));
	//mStateList.push_back(Ref<State>(new ClearPathState));
	//mStateList.push_back(Ref<State>(new SearchBonusState));
	//mCurrentState = mStateList[0];
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



