#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "MoogeType.h"

class GameObjectContainer;
class GameObject
{
public:
	friend class GameObjectContainer;
	
	virtual void Draw() = 0;
	virtual void Update() {}
	virtual ~GameObject() {}
	
	float GetX();
	float GetY();
	float GetZ();
	float GetScale();
	float GetRotateX();
	float GetRotateY();
	float GetRotateZ();
	float GetAlpha();

	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetScale(float scale);
	void SetRotateX(float rotateX);
	void SetRotateY(float rotateY);
	void SetRotateZ(float rotateZ);
	void SetAlpha(float alpha);
	void RemoveFromParent();
	GameObjectContainer* GetParent();
	GameObject* GetRoot();

protected:
	GameObject() {}
	void SetParent(GameObjectContainer* obj);
	
private:
	float mAlpha;
	float mX,mY,mZ;
	float mScale;
	float mRotateX, mRotateY, mRotateZ;
	GameObjectContainer *mParent;
	//Stage *stage;
};

#endif