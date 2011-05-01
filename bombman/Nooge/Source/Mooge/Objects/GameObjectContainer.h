#ifndef _GAMEOBJECT_CONTAINER_H
#define _GAMEOBJECT_CONTAINER_H

#include "GameObject.h"
#include <vector>

class GameObjectContainer : public GameObject
{
public:
	~GameObjectContainer();

	void				AddChild(GameObject *child);
	void				AddChildAt(GameObject *child, int idx);
	void				RemoveChild(GameObject *child);
	GameObject*			GetChild(int idx);
	int					NumOfChild();

	//override
	virtual void Draw();
	virtual void Update();
private:
	std::vector<GameObject*> mChildren;
	int mNumOfChild;
};

#endif