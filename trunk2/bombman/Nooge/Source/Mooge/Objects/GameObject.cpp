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
	if (mParent)
		mParent->RemoveChild(
		mParent->GetChild(this));
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

float GameObject::GetAlpha()
{
	return mAlpha;
}

GameObject::GameObject()
{
	mAlpha = 1.0f;
	mX = mY = mZ = 0.0f;
	mScale = 1.0f;
	mRotateX = mRotateY = mRotateZ = 0.0f;
	mParent = NULL;
}

void GameObject::SetScale( float scale )
{
	mScale = scale;
}

void GameObject::SetX( float x )
{
	mX = x;
}

void GameObject::SetY( float y )
{
	mY = y;
}

void GameObject::SetZ( float z )
{
	mZ = z;
}

void GameObject::SetRotateX( float rotateX )
{
	mRotateX = rotateX;
}

void GameObject::SetRotateY( float rotateY )
{
	mRotateY = rotateY;
}

void GameObject::SetRotateZ( float rotateZ )
{
	mRotateZ = rotateZ;
}

void GameObject::SetPos( float x, float y, float z )
{
	SetX(x);
	SetY(y);
	SetZ(z);
}

void GameObject::SetCol()
{
	//SetX(col*Grid::SideLen);
	//SetX(GetBoundingBox().Col()*Grid::SideLen);
   int offset = GetX();
	if( offset%10<5)
		SetX(offset+5-offset%5);
	else
		SetX(offset-offset%5);
}

void GameObject::SetRow()
{
	//SetZ(row*Grid::SideLen);
	//SetZ(GetBoundingBox().Row()*Grid::SideLen);
	   int offset = GetZ();
	if( offset%10<5)
		SetZ(offset+5-offset%5);
	else
		SetZ(offset-offset%5);
}

Grid GameObject::GetBoundingBox()
{
	float offset = Grid::SideLen/2-0.8;
	return Grid(mX-offset,mZ+offset,mX+offset,mZ-offset);
}


