#pragma once

#include "Stage.h"
#include "Ref.h"
#include "Map.h"
#include "GameObject.h"

class GameStage : public Stage
{
public:
	GameStage(Ref<GameObject> map);
	Ref<GameObject> CurrentMap();
	Ref<GameObject> Player();
	bool CanPass(GameObject* obj);
	void AddBomb(Ref<GameObject> bomb);
	virtual ~GameStage();

private:
	Ref<GameObject> mCurrentMap;
	Ref<GameObject> mPlayer;
	Ref<GameObject> mDwall;
	Ref<GameObject> mUwall;
	Ref<GameObject> mNpc;
	Ref<GameObject> mBomb;
};                                                                                                                                                                                                                                                                                                                                                                                                     