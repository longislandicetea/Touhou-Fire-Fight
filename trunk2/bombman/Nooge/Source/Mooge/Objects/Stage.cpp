#include<Stage.h>

#include <windows.h>
#include <gl/GL.h>

void Stage::Draw()
{
	//glClearColor(0.0,0.0,0.0,0.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);
	GameObjectContainer::Draw();
}