#include "GameObjectContainer.h"
#include <algorithm>
#include <functional>
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>


void GameObjectContainer::AddChild( Ref<GameObject> child )
{
	AddChildAt(child,mChildren.size());
}

void GameObjectContainer::AddChildAt( Ref<GameObject> child, int idx )
{
	//pay attention to the order! remove->set->add
	child->RemoveFromParent();
	child->SetParent(this);
	ChildrenContainer::const_iterator it = mChildren.begin();
	mChildren.insert(it+idx,child);
}

void GameObjectContainer::RemoveChild( Ref<GameObject> child )
{
	ChildrenContainer::const_iterator it;
	it = std::find(mChildren.begin(),mChildren.end(),child);
	if(it != mChildren.end())
	{
		child->SetParent(NULL);
		mChildren.erase(it);
	}
}


Ref<GameObject> GameObjectContainer::GetChild( int idx )
{
	return mChildren[idx];
}

Ref<GameObject> GameObjectContainer::GetChild(GameObject *obj) 
{
	//Ref<xxx> : mChildren[i]
	//xxx : *mChildren[i]
	//xxx* : &*mChildren[i]
	for (size_t i = 0; i < mChildren.size(); ++i) {
		if (&*mChildren[i] == obj)
			return mChildren[i];
	}
	throw std::logic_error("cannot find this object");
}

int GameObjectContainer::NumOfChild()
{
	return mChildren.size();
}

void GameObjectContainer::Draw()
{
	ChildrenContainer::const_iterator it = mChildren.begin();
	float alpha = this->GetAlpha();
	for(;it!=mChildren.end();++it)
	{
		Ref<GameObject> obj = *it;
		float childAlpha = obj->GetAlpha();
		if(childAlpha>0.0)
		{
			glPushMatrix();
			//scale
			glScalef(obj->GetScale(), obj->GetScale(), obj->GetScale());
			
			//pos
			glTranslatef(obj->GetX(), obj->GetY(), obj->GetZ());

			//rotate
			glRotatef(obj->GetRotateX(), 1.0, 0.0, 0.0);
			glRotatef(obj->GetRotateY(), 0.0, 1.0, 0.0);
			glRotatef(obj->GetRotateZ(), 0.0, 0.0, 1.0);

			obj->Draw();
			childAlpha *= alpha;
			obj->SetAlpha(childAlpha);
			glPopMatrix();
		}
	}
}

void GameObjectContainer::Update(float dt)
{
	ChildrenContainer children = mChildren;
	for(int i = 0;i < children.size();++i)
	{
		children[i]->Update(dt);
	}
}

GameObjectContainer::~GameObjectContainer()
{
}

GameObjectContainer::ChildrenContainer GameObjectContainer::GetAllChildren()
{
	return mChildren;
}
