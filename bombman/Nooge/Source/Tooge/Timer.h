#pragma once

#include <time.h>

class Timer 
{
public:
	typedef double diff_type;

	Timer(): mStart(clock()), mElapsed(0),mIsOpen(false) {}
	diff_type Last() const ;
	void Begin();
	diff_type End();
	bool IsOpen();
	void SetOpen(bool open);

private:
	clock_t mStart;
	diff_type    mElapsed;
	bool mIsOpen;
};