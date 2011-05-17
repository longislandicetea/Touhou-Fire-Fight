#pragma once
#include"GameObjectContainer.h"

class Character;

class CharacterController
{
public:
	enum action{ UP, DOWN, RIGHT, LEFT, BOMB, IDLE};
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