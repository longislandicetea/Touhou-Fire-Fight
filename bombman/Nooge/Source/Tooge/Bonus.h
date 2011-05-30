#pragma once

#include "GameObjectContainer.h"
#include "Ref.h"
#include "GameObject.h"
#include "Timer.h"

class Bonus : public Sprite
{
public:

protected:
	Ref<GameObject> mModel;
	Ref<Timer> mTimer;
};