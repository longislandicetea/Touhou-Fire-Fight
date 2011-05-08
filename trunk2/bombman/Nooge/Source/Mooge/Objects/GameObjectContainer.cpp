#include "GameObjectContainer.h"
#include <algorithm>
#include <functional>

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

Ref<GameObject> GameObjectContainer::GetChild(GameObject *obj) {
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
		float childAlpha = (*it)->GetAlpha();
		if(childAlpha != 0.0)
		{
			glPushMatrix();
			(*it)->Draw();
			childAlpha *= alpha;
			(*it)->SetAlpha(childAlpha);
			glPopMatrix();
		}
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
	/*ChildrenContainer::const_iterator it = mChildren.begin();
	for(;it!=mChildren.end();++it)
	{
		delete *it;
	}*/
}
