#pragma once

#include "GameObjectContainer.h"
#include "Ref.h"
#include "GameObject.h"

class Bomb : public Sprite
{
public:
	Bomb();
	virtual void Update();
private:
	Ref<GameObject> mModel;
	float mTimeToExplosion;
	int mFlamePower;

};