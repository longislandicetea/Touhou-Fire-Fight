#pragma once
#include"GameObjectContainer.h"

#include "GameStage.h"
#include "Ref.h"
#include "GameObject.h"
#include "Grid.h"

class Character;

class CharacterController
{
public:
	enum Action { UP, DOWN, RIGHT, LEFT, BOMB, IDLE, ACTION_CNT};

	virtual int Update(Character* Character, float dt) = 0;

private:
	Character* mOwner;
};

class Character : public Sprite
{
public:
	void Update(float dt);
	static Ref<GameObject> AddController(CharacterController* ctrl);
	GameStage* GetGameStage();
private:
	Character(CharacterController* ctrl);
	CharacterController& mCtrl;
	void doAction(int currentAction, float dt);
	void up(float dt);
	void down(float dt);
	void left(float dt);
	void right(float dt);

	float mSpeed;
	int mLife;
	GameStage* mStage;
	Ref<GameObject> mModel;
	
	//vector<Bomb> mBomb;
	//vector<Bonus> mBonus;
};