#pragma once
#include"GameObjectContainer.h"

class Character;

class CharacterController
{
public:
	enum Action { UP, DOWN, RIGHT, LEFT, BOMB, IDLE, ACTION_CNT};
	virtual int Update(Character *character, float dt) = 0;
};

class Character : public Sprite
{
public:
	void Update(float dt);
private:
	CharacterController& mCtrl;
	void doAction(int currentAction, float dt);
	void Up(float dt);
	void Down(float dt);
	void Left(float dt);
	void Right(float dt);
};