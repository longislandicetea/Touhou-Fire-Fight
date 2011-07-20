#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "MoogeType.h"
#include "Grid.h"
#include "Ref.h"

class GameObjectContainer;
class GameObject
{
public:
	friend class GameObjectContainer;
	
	virtual void Draw(bool Is3D) = 0;
	virtual void Update(float dt) {}
	virtual ~GameObject() {}
	
	float GetX();
	float GetY();
	float GetZ();
	float GetScale();
	float GetRotateX();
	float GetRotateY();
	float GetRotateZ();
	float GetAlpha();
	virtual Grid GetBoundingBox();

	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetPos(float x, float y, float z);
	void SetCol();
	void SetRow();
	void SetScale(float scale);
	void SetRotateX(float rotateX);
	void SetRotateY(float rotateY);
	void SetRotateZ(float rotateZ);
	void SetAlpha(float alpha);
	void RemoveFromParent();
	GameObjectContainer* GetParent();
	GameObject* GetRoot();


protected:
	GameObject();
	void SetParent(GameObjectContainer* obj);
	
private:
	float mAlpha;
	float mX,mY,mZ;
	float mScale;
	float mRotateX, mRotateY, mRotateZ;
	GameObjectContainer *mParent;
	Ref<Grid> mBoundingBox;
};

#endif