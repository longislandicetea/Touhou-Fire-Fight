#include"Transition.h"

bool Transition::IsTrue()
{
	return mIsTrue;
}

Ref<State> Transition::GetNextState()
{
	return mNextState;
}