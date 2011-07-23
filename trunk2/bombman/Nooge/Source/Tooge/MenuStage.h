#pragma once

#include "Stage.h"
#include "GameObject.h"
#include <GL/glut.h>

#include <vector>

/*void glMouseMotion(int x, int y)
{

}*/

class MenuStage : public Stage
{
public:
	static Ref<Stage> LoadStage();
	void HandleClickEvent(int x,int y);
	void HandleMouseOverEvent(int x,int y);
	void HandleMouseLeaveEvent(int x,int y);
	virtual void Draw(bool is3D);
	virtual void Update(float dt);
	virtual ~MenuStage() {}
private:
	MenuStage();
	Ref<GameObject> mGuiObject;

	int mLastX,mLastY;
};