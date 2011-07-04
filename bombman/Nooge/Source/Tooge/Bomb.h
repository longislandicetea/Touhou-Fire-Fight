#pragma once

#include "GameObjectContainer.h"
#include "Ref.h"
#include "GameObject.h"
#include "Timer.h"
//#include <vector>

class Character;

class Bomb : public Sprite
{
public:
	static void CreateBomb(int x,int y, Character* owner);
	virtual void Update(float dt);

private:
	Bomb();
	void explode();

	int mPower;
	Ref<GameObject> mModel;
	Ref<Timer> mTimer;
	std::vector< Ref<Grid> > mFlame;
};