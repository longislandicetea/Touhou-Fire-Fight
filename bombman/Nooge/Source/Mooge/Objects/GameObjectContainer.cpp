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
	/*if(!child.IsNull())
	{
		child->RemoveFromParent();
		child->SetParent(this);
	}
	ChildrenContainer::const_iterator it = mChildren.begin();
	mChildren.insert(it+idx,child);*/
	child->RemoveFromParent();
	child->SetParent(this);
	ChildrenContainer::const_iterator it = mChildren.begin();
	mChildren.insert(it+idx,child);
}

void GameObjectContainer::RemoveChild( Ref<GameObject> child )
{
	/*ChildrenContainer::const_iterator it;
	for(it = mChildren.begin();it != mChildren.end();)
	{
		if(*it == child)
		{
			//child->SetParent(NULL);
			it = mChildren.erase(it);
		}
		else
			it++;
	}
	//it = std::find(mChildren.begin(),mChildren.end(),child);
	if(it != mChildren.end())
	{
		child->SetParent(NULL);
		mChildren.erase(it);
	}*/
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

void GameObjectContainer::Draw(bool is3D)
{
	ChildrenContainer::const_iterator it = mChildren.begin();
	float alpha = this->GetAlpha();
	for(;it!=mChildren.end();++it)
	{
		Ref<GameObject> obj = *it;
		if(!obj.IsNull()) {
		float childAlpha = obj->GetAlpha();
		if(childAlpha>0.0)
		{
			glPushMatrix();
			glScalef(obj->GetScale(), obj->GetScale(), obj->GetScale());
			glTranslatef(obj->GetX(), obj->GetY(), obj->GetZ());

			glRotatef(obj->GetRotateX(), 1.0, 0.0, 0.0);
			glRotatef(obj->GetRotateY(), 0.0, 1.0, 0.0);
			glRotatef(obj->GetRotateZ(), 0.0, 0.0, 1.0);

			obj->Draw(is3D);
			childAlpha *= alpha;
			obj->SetAlpha(childAlpha);
			glPopMatrix();
		}
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
