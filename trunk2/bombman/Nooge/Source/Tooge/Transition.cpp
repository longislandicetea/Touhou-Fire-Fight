#include"Transition.h"

bool Transition::IsTrue()
{
	return mIsTrue;
}

State* Transition::GetNextState()
{
	return mNextState;
}