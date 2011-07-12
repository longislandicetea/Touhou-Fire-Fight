#pragma once

#include "Stage.h"
#include "Ref.h"
#include "Map.h"
#include "GameObject.h"
#include "Timer.h"

#include <map>
#include <string>

class Character;

class GameStage : public Stage
{
public:
	GameStage(Ref<GameObject> map);
	Ref<GameObject> CurrentMap();
	Ref<GameObject> Player();
	bool CanPass(GameObject* obj);
	bool HasUwall( int row,int col);
	void DwallExplode( int row,int col);
	void EatBonus(Character* obj);
	void StepOnBomb(Character* obj);
	void AddBomb(Ref<GameObject> bomb);
	void AddBonus(Ref<GameObject> bonus);
	virtual ~GameStage();
	Ref<GameObject> CreateBonus();

	void Draw();

	//for AI
	GameObjectContainer::ChildrenContainer GetAllBombs();

private:

	Ref<GameObject> mCurrentMap;
	Ref<GameObject> mPlayer;
	Ref<GameObject> mDwall;
	Ref<GameObject> mUwall;
	Ref<GameObject> mNpc;
	Ref<GameObject> mBomb;
	Ref<GameObject> mBonus;
	Ref<GameObject> mFloor;
	Ref<GameObject> mExplosion;
	std::map<std::string,int> mBonusProb;

	Ref<GameObject> mHDU;

	Ref<Timer> mTimer;
};                                                                                                                                                                                                                                                                                                                                                                                                     