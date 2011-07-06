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
	void TriggerPush(int direction,float speed);
	void MoveWhenPushed(float ds);

private:
	Bomb();
	void explode();
	void actWhenSteped();

	int mPower;
	int mDirection;
	int mSpeed;
	int mPushed;
	bool mInTrigState;
	Character* mOwner;
	Ref<GameObject> mModel;
	Ref<Timer> mTimer;
	std::vector< Ref<Grid> > mFlame;
};