#pragma once

#include "GameObjectContainer.h"
#include "Ref.h"
#include "GameObject.h"
#include "Timer.h"

class Bomb : public Sprite
{
public:
	static void CreateBomb(int x,int y);
	virtual void Update(float dt);

private:
	Bomb();
	Ref<GameObject> mModel;
	Ref<Timer> mTimer;
	int mFlamePower;
};