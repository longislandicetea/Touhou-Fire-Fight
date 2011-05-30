#pragma once

#include <time.h>

class Timer 
{
public:
	typedef double diff_type;

	Timer(): mStart(clock()), mElapsed(0) {}
	diff_type Last() const ;
	void Begin();
	diff_type End();

private:
	clock_t mStart;
	diff_type    mElapsed;
};