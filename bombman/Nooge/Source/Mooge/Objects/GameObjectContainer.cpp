#include "GameObjectContainer.h"
#include <algorithm>
#include <functional>

void GameObjectContainer::AddChild( GameObject *child )
{
	AddChildAt(child,mChildren.size());
}

void GameObjectContainer::AddChildAt( GameObject *child, int idx )
{
	//pay attention to the order! remove->set->add
	child->RemoveFromParent();
	child->SetParent(this);
	ChildrenContainer::const_iterator it = mChildren.begin();
	mChildren.insert(it+idx,child);
}

void GameObjectContainer::RemoveChild( GameObject *child )
{
	ChildrenContainer::const_iterator it;
	it = std::find(mChildren.begin(),mChildren.end(),child);
	if(it != mChildren.end())
	{
		child->SetParent(NULL);
		mChildren.erase(it);
	}
}


GameObject* GameObjectContainer::GetChild( int idx )
{
	return mChildren[idx];
}

int GameObjectContainer::NumOfChild()
{
	return mChildren.size();
}

void GameObjectContainer::Draw()
{
	ChildrenContainer::const_iterator it = mChildren.begin();
	for(;it!=mChildren.end();++it)
	{
		(*it)->Draw();
	}
}

void GameObjectContainer::Update()
{
	ChildrenContainer::const_iterator it = mChildren.begin();
	for(;it!=mChildren.end();++it)
	{
		(*it)->Update();
	}
}

GameObjectContainer::~GameObjectContainer()
{
	ChildrenContainer::const_iterator it = mChildren.begin();
	for(;it!=mChildren.end();++it)
	{
		delete *it;
	}
}
