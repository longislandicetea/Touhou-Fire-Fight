#pragma once

#include "GameObjectContainer.h"
#include "GameObject.h"
#include "Md2Object.h"
#include "Ref.h"

class Dwall : public Sprite
{
public :
	Dwall();
	virtual ~Dwall();
	virtual Grid GetBoundingBox();
private:
	Ref<GameObject> mModel;

};