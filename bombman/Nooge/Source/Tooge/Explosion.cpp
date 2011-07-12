#include "Explosion.h"

#include<windows.h>
#include <GL/gl.h>

#include <stdlib.h>

#include "WinFrame.h"

Explosion::Explosion( float x,float y,float z )
{
	//glEnable(GL_BLEND);
	//glEnable(GL_TEXTURE_2D);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBlendFunc(GL_ONE,GL_ZERO);
	//glEnable(GL_POINT_SMOOTH); 

	mParticles.reserve(MAX_PARTICLE);
	for(int i = 0;i<MAX_PARTICLE;++i)
	{
		Particle p;
		p.x = x;
		p.y = y;
		p.z = z;
		p.xi = rand()%50-26;
		p.yi = rand()%50-25;
		p.zi = rand()%50-25;
		//p.xi = p.yi = p.zi = 0.0;
		p.r = DEFAULT_R;
		p.g = DEFAULT_G;
		p.b = DEFAULT_B;
		p.life = 2.2;
		//p.fade = (rand()%10)/10000+0.003;
		p.fade = rand()%10/50.0+0.1;

		float factor = 3;
		p.gx = -p.xi*factor;
		p.gy = -p.yi*factor;
		p.gz = -p.zi*factor;

		mParticles.push_back(p);
	}
	mParticleSize = 1;
}

void Explosion::Draw()
{
	glEnable (GL_BLEND); 
	glBlendFunc (GL_ONE,GL_ONE);
	//glClear(GL_ACCUM_BUFFER_BIT);

	//glPushMatrix();
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	for(int i = 0;i<MAX_PARTICLE;++i)
	{
		if(mParticles[i].life>0.0)
		{
			glPointSize(10.0);
			glEnable(GL_POINT_SMOOTH);
			int x = mParticles[i].x;
			int y = mParticles[i].y;
			int z = mParticles[i].z;

			float dt = 0.03;
			mParticles[i].x += mParticles[i].xi/(dt* 100000.0);
			mParticles[i].xi += mParticles[i].gx;
			mParticles[i].y += mParticles[i].yi/(dt* 100000.0);
			mParticles[i].yi += mParticles[i].gy;
			mParticles[i].z += mParticles[i].zi/(dt* 100000.0);
			mParticles[i].zi += mParticles[i].gz;

			mParticles[i].life -= mParticles[i].fade;
			glColor4f(mParticles[i].r,mParticles[i].g,mParticles[i].b,1);

			glBegin(GL_POINTS);
			glVertex3f(x-mParticleSize,y-mParticleSize,z);
			glVertex3f(x-mParticleSize,y+mParticleSize,z);
			glVertex3f(x+mParticleSize,y+mParticleSize,z);
			glVertex3f(x+mParticleSize,y-mParticleSize,z);
			glEnd();
			LogTrace("%d %d %d\n",x,y,z);
		}
	}
	glPopMatrix();
	glDisable(GL_BLEND);
}
