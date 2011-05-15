#include"InputSystem.h"
#include <windows.h>

void InputSystem::KeyDown(int key)
{
	down.insert(key);
}

void InputSystem::KeyUp(int key)
{
	/*set<int>::iterator it = down.find(key);
	down.erase(it);*/
	down.erase(key);
}

bool InputSystem::IsKeyDown(int key)
{
	return down.find(key) != down.end();
}
