#include"Transition.h"


///////////////////////////////////////////////////////transition///////////////////////////////////////////////////
Transition::Transition(NPCController* ctrl, State* nextState):
mNextState(nextState)
{
	mCtrl = ctrl;
}

State* Transition::GetNextState()
{
	return mNextState;
}

//////////////////////////////////////////////////ToFlee///////////////////////////////////////////////

ToFlee::ToFlee(NPCController* ctrl,State* next):
Transition(ctrl,next)
{}

bool ToFlee::IsTrue()
{
	//Grid g = mCtrl->GetCharacter()->GetBoundingBox();
	int row = mCtrl->GetCharacter()->GetBoundingBox().Row();
	int col = mCtrl->GetCharacter()->GetBoundingBox().Col();
	if(mCtrl->GetDangerGrid()->GetValue(col,row)<=3.0)
		return true;
	return false;
}