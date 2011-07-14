#include"Transition.h"


///////////////////////////////////////////////////////transition///////////////////////////////////////////////////
Transition::Transition(Ref<NPCController> ctrl, Ref<State> nextState):
mNextState(nextState)
{
	mCtrl = ctrl;
}

Ref<State> Transition::GetNextState()
{
	return mNextState;
}

//////////////////////////////////////////////////ToFlee///////////////////////////////////////////////

ToFlee::ToFlee(Ref<NPCController> ctrl,Ref<State> next):
Transition(ctrl,next)
{}

bool ToFlee::IsTrue()
{
	Grid g = mCtrl->GetCharacter()->GetBoundingBox();
	int row = g.Row();
	int col = g.Col();
	if(mCtrl->GetDangerGrid()->GetValue(col,row)<=3.0)
		return true;
	return false;
}