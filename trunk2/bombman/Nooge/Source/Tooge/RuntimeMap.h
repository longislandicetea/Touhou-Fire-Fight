#pragma once

#include "Map.h"
#include "GameObjectContainer.h"
#include "GameObject.h"
#include "Ref.h"

class RuntimeMap : public Map
{
public:
	RuntimeMap();
	void SetMap();
	//virtual void Update();
	bool CanPass(GameObject* obj);

private:
	Ref<GameObject> mDwall;
	Ref<GameObject> mUwall;
	Ref<GameObject> mBonus;
	Ref<GameObject> mNPC;
	Ref<GameObject> mPlayer;
	Ref<Map> mMap;
};