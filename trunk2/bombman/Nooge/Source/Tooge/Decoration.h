#pragma once

#include "GameObjectContainer.h"

class Decoration : public Sprite
{
public :
	Decoration();
	virtual ~Decoration();

private:
	Ref<GameObject> mModel;

};