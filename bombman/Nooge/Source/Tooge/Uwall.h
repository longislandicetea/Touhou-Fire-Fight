#pragma once

#include "GameObjectContainer.h"

class Uwall : public Sprite
{
public :
	Uwall();
	virtual ~Uwall();

private:
	Ref<GameObject> mModel;

};