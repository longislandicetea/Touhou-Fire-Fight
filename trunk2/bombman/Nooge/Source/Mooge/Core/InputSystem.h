#pragma once
#include <set>

class InputSystem
{
public:
	void KeyDown(int key);
	void KeyUp(int key);
	bool IsKeyDown(int key);
private:
	std::set<int> down;
};