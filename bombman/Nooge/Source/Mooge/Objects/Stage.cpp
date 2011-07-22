#include<Stage.h>

#include <windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <gl/GLU.h>

void Stage::Draw(bool is3D)
{
	GameObjectContainer::Draw(is3D);
}