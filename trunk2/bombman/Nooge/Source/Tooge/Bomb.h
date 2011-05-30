#pragma once

#include "GameObjectContainer.h"
#include "Ref.h"
#include "GameObject.h"
#include "Timer.h"

class Bomb : public Sprite
{
public:
	Bomb();
	virtual void Update(float dt);

private:
	Ref<GameObject> mModel;
	Ref<Timer> mTimer;
	int mFlamePower;
};