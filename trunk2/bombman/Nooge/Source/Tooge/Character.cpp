#include"Character.h"

void Character::Update(float dt)
{
	int currentAction = mCtrl.Update(this,dt);
	doAction(currentAction,dt);

}

void Character::doAction( int currentAction, float dt )
{
	switch (currentAction)
	{
	case 0:
		{

		}
	case 1:
		{

		}
	case 2:
		{

		}
	}
}
