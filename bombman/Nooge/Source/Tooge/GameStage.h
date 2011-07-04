#pragma once

#include "Stage.h"
#include "Ref.h"
#include "Map.h"
#include "GameObject.h"

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
	void AddBomb(Ref<GameObject> bomb);
	void AddBonus(Ref<GameObject> bonus);
	virtual ~GameStage();
	Ref<GameObject> CreateBonus();

private:

	Ref<GameObject> mCurrentMap;
	Ref<GameObject> mPlayer;
	Ref<GameObject> mDwall;
	Ref<GameObject> mUwall;
	Ref<GameObject> mNpc;
	Ref<GameObject> mBomb;
	Ref<GameObject> mBonus;
	std::map<std::string,int> mBonusProb;
};                                                                                                                                                                                                                                                                                                                                                                                                     