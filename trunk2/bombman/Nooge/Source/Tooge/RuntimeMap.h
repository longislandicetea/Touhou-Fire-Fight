#pragma once

#include "Map.h"
#include "GameObjectContainer.h"

class RuntimeMap : public Map
{
public:
	void SetMap();
	virtual void Update();
	virtual void Draw();

private:
	Ref<Sprite> mDwall;
	Ref<Sprite> mUwall;
	Ref<Sprite> mBonus;
	Ref<Sprite> mNPC;

};