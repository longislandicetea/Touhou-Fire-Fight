#pragma once

#include "Map.h"
#include "GameObjectContainer.h"
#include "GameObject.h"
#include "Ref.h"

class AIMap;
class RuntimeMap : public Map
{
public:
	static Ref<GameObject> Load(const char* filename);
	//virtual void Update();
	bool CanPass(GameObject* obj);
	void AddBomb(Ref<GameObject> bomb);

private:
	RuntimeMap(float playerX,float playerY);

	Ref<GameObject> mDwall;
	Ref<GameObject> mUwall;
	Ref<GameObject> mBomb;
	//Ref<GameObject> mBonus;
	Ref<GameObject> mNPC;
	Ref<Map> mMap;

	float mPlayerX,mPlayerY;
};