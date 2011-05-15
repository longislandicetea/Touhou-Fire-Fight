#ifndef _GAMEOBJECT_CONTAINER_H
#define _GAMEOBJECT_CONTAINER_H

#include "GameObject.h"
#include "Ref.h"
#include <vector>

class GameObjectContainer : public GameObject
{
public:
	typedef std::vector< Ref<GameObject> > ChildrenContainer;
	~GameObjectContainer();

	void				AddChild(Ref<GameObject> child);
	void				AddChildAt(Ref<GameObject>, int idx);
	void				RemoveChild(Ref<GameObject> child);

	Ref<GameObject>     GetChild(int idx);
	Ref<GameObject>		GetChild(GameObject *obj);

	int					NumOfChild();

	//override
	virtual void Draw();
	virtual void Update(float dt);
private:
	ChildrenContainer mChildren;
};

#endif