#include "Explosion.h"

#include<windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/GLU.h>

#include <stdlib.h>

#include "WinFrame.h"
#include "DataManager.h"

Explosion::Explosion( float x,float y,float z )
{
	this->SetPos(x, y, z);
	mParticleSize = 1;
	mLife = 0.8;
	mFlameTex = Texture::Load(DataManager::GetDataPath
		("Texture","flameT","resource\\data.ini"));
}

void Explosion::Draw(bool is3D)
{
	//return;
	if (!is3D) return;

	Texture::Bind(mFlameTex);
	glScalef(mParticleSize, mParticleSize, mParticleSize);
	/*glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);glVertex3f(-1.0,1,0.0);
	glTexCoord2f(0.0,1.0);glVertex3f(-1.0,-1.0,0.0);
	glTexCoord2f(1.0,1.0);glVertex3f(1,0.-1,0.0);
	glTexCoord2f(1.0,0.0);glVertex3f(1,1,0.0);*/

	GLUquadricObj *quadric;
	quadric = gluNewQuadric();

	gluQuadricDrawStyle(quadric, GLU_POINT );
	gluSphere( quadric , .5 , 36 , 18 );

	gluDeleteQuadric(quadric); 

	glEnd();
}

void Explosion::Update( float dt )
{
	mLife -= dt;
	if (mLife < 0) 
	{
		this->RemoveFromParent();
	}
	mParticleSize += dt * 10;
}