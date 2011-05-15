#pragma once
#include"GameObjectContainer.h"

class Character;

struct CharacterController
{
	enum action{ UP, DOWN, RIGHT, LEFT, BOMB, IDLE};
	virtual int GetCommand(Character *character) = 0;
};

class Character: public Sprite
{
public:
	void Update();
private:
	CharacterController& mCtrl;
};