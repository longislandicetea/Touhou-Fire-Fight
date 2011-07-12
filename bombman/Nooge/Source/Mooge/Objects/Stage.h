#ifndef _STAGE_H
#define _STAGE_H
#include<GameObjectContainer.h>

#include "Ref.h"

class Stage: public GameObjectContainer
{
public:
	virtual void Draw();
	virtual void HandleClickEvent(int x,int y) {}

private:

};


#endif