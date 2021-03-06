#pragma once
#include"GameObjectContainer.h"

#include "GameStage.h"
#include "Ref.h"
#include "GameObject.h"
#include "Grid.h"
#include "Bomb.h"
#include "Timer.h"

#include <vector>
#include <string>

class Character;

class CharacterController
{
public:
	enum Action { MOVE_LEFT, MOVE_DOWN, MOVE_RIGHT,  MOVE_UP,DROP_BOMB, TRIGGER_BOMB,IDLE, ACTION_CNT};

	virtual int Update(Character* Character, float dt) = 0;
	Character* GetCharacter(){return mOwner;}
	

protected:
	Character* mOwner;
};


class Character : public Sprite
{
public:
	static Ref<GameObject> CreateCharacter(const std::string& type);
	void Update(float dt);
	void SetSpeed(float factor);
	void SetPower(int factor);
	void SetBombCnt(int factor);
	void SetLifeCnt(int factor);
	void SetTimer();
	void SetPushBonus(bool hasBonus);
	void SetTrigBonus(bool hasBonus);

	int GetPower();
	int GetBombCnt();
	int GetCurState();
	void SetCurState(int action);
	virtual Grid GetBoundingBox();
	float GetSpeed();

	bool HasPushBonus();
	bool HasTrigBonus();

	Ref<Timer> TrigBonusTimer();

	

private:
	Character(CharacterController* ctrl,const std::string& type);
	Ref<GameObject> AddController(CharacterController* ctrl);
	CharacterController& mCtrl;

	void doAction(int currentAction, float dt);
	void up(float dt);
	void down(float dt);
	void left(float dt);
	void right(float dt);

	float mSpeed;
	int mBombPower;
	int mLifeCnt;
	int mBombCnt;
	bool mHasDropMalus;
	bool mHasPushBonus;
	bool mHasTrigBonus;

	CharacterController::Action mLastAction;
	
	//int mDirection;//0-left 1-down 2-right 3-up
	int mCurrentAction;
	GameStage* mStage;
	Ref<GameObject> mModel;
	
	Ref<Timer> mTrigTimer;
	Ref<Timer> mTimer;
};