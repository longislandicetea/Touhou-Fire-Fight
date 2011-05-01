#include"GameObject.h"
#include "GameObjectContainer.h"

float GameObject::GetX()
{
	return mX;
}

float GameObject::GetY()
{
	return mY;
}

float GameObject::GetZ()
{
	return mZ;
}

float GameObject::GetScale()
{
	return mScale;
}

float GameObject::GetRotateX()
{
	return mRotateX;
}

float GameObject::GetRotateY()
{
	return mRotateY;
}

float GameObject::GetRotateZ()
{
	return mRotateZ;
}

void GameObject::SetAlpha( float alpha )
{
	mAlpha = alpha;
}

void GameObject::RemoveFromParent()
{
	if(mParent != NULL)
		mParent->RemoveChild(this);
}

GameObjectContainer* GameObject::GetParent()
{
	return mParent;
}

void GameObject::SetParent( GameObjectContainer* obj )
{
	mParent = obj;
}

GameObject* GameObject::GetRoot()
{
	GameObject* tmp = this;
	while(tmp->mParent != NULL)
		tmp = tmp->mParent;
	return tmp;
}
