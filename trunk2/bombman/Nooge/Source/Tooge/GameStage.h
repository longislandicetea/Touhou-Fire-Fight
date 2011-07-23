#pragma once

#include "Stage.h"
#include "Ref.h"
#include "Map.h"
#include "GameObject.h"
#include "Timer.h"

#include <map>
#include <string>
#include "Font.h"
#include "2DText.h"

class Character;

class GameStage : public Stage
{
public:
	GameStage(Ref<GameObject> map, int level);
	~GameStage();
	Ref<GameObject> CurrentMap();
	Ref<GameObject> Player();
	bool CanPass(GameObject* obj);
	bool HasUwall( int row,int col);
	bool HasDwall( int row,int col);
	void DwallExplode( int row,int col);
	void EatBonus(Character* obj);
	void StepOnBomb(Character* obj);
	void AddBomb(Ref<GameObject> bomb);
	void AddBonus(Ref<GameObject> bonus);
	void AddExplosion(Ref<GameObject> explosion);
	//virtual ~GameStage();
	Ref<GameObject> CreateBonus();

	void CheckCharacterLife(int row,int col);

	virtual void Draw(bool is3D);
	virtual void Update(float dt);

	//for AI
	GameObjectContainer::ChildrenContainer GetAllBombs();

private:

	//map data
	Ref<GameObject> mCurrentMap;
	std::map<std::string,int> mBonusProb;
	int mWallMap[13][15];

	//rendered objects
	Ref<GameObject> mPlayer;
	Ref<GameObject> mDwall;
	Ref<GameObject> mUwall;
	Ref<GameObject> mNpc;
	Ref<GameObject> mBomb;
	Ref<GameObject> mBonus;
	Ref<GameObject> mDecoration;
	Ref<GameObject> mExplosion;
	
	Ref<GameObject> mHUD;
	Ref<GameObject> mCountdownTimerFont;
	
	bool isDead[4];

	//timer
	Ref<Timer> mTimer;
	float mCountdownTimer;

	//level
	int mLevel;
	
	void initWallMap();

	std::string timeToString(int restTime);
};                                                                                                                                                                                                                                                                                                                                                                                                     