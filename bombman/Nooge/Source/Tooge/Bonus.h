#pragma once

#include "GameObjectContainer.h"
#include "Ref.h"
#include "GameObject.h"
#include "Timer.h"

class Bonus : public Sprite
{
public:
	Bonus()
	{	
		mTimer = Ref<Timer>(new Timer);
	    mTimer->Begin();	
	}
	static void CreateBonus(int x,int y);

	//for AI
	Ref<Timer> GetTimer();
protected:
	Ref<GameObject> mModel;
	Ref<Timer> mTimer;
};