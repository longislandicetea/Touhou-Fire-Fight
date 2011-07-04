#include"FSM.h"


FSM::FSM()
{

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

State* FSM::CurrentState()
{
	return mCurrentState;
}



