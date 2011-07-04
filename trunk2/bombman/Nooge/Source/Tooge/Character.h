#pragma once
#include"GameObjectContainer.h"

#include "GameStage.h"
#include "Ref.h"
#include "GameObject.h"
#include "Grid.h"
#include "Bomb.h"
#include <vector>

class Character;

class CharacterController
{
public:
	enum Action { MOVE_UP, MOVE_DOWN, MOVE_RIGHT, MOVE_LEFT, DROP_BOMB, TRIGGER_BOMB,IDLE, ACTION_CNT};

	virtual int Update(Character* Character, float dt) = 0;

private:
	Character* mOwner;
};


class Character : public Sprite
{
public:
	void Update(float dt);
	static Ref<GameObject> AddController(CharacterController* ctrl);
	void SetSpeed(int factor);
	void SetPower(int factor);

	int GetPower();

private:
	Character(CharacterController* ctrl);
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
	GameStage* mStage;
	Ref<GameObject> mModel;
};