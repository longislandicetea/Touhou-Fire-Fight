#include "Timer.h"

Timer::diff_type Timer::Last() const
{
	return mElapsed;
}

void Timer::Begin()
{
	mStart = clock(); 
	mElapsed = 0;
}

Timer::diff_type Timer::End()
{
	mElapsed = (diff_type)clock() - mStart;
	mElapsed /= CLOCKS_PER_SEC;
	return mElapsed;
}

