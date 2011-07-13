#include"Transition.h"



Transition::Transition(Ref<State> nextState):
mNextState(nextState)
{
}

Ref<State> Transition::GetNextState()
{
	return mNextState;
}