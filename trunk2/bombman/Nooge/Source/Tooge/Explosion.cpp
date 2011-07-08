#include "Explosion.h"

#include<windows.h>
#include <GL/gl.h>

#include <stdlib.h>

Explosion::Explosion( float x,float y,float z )
{
	//glEnable(GL_BLEND);
	//glEnable(GL_TEXTURE_2D);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBlendFunc(GL_ONE,GL_ZERO);
	//glEnable(GL_POINT_SMOOTH); 

	for(int i = 0;i<MAX_PARTICLE;++i)
	{
		Particle p;
		p.x = x;
		p.y = y;
		p.z = z;
		p.xi = p.yi = p.zi = 0.0;
		p.r = DEFAULT_R;
		p.g = DEFAULT_G;
		p.b = DEFAULT_B;
		p.life = 0.7;
		p.fade = (rand()%10)/10000+0.003;

		float factor = 0.05;
		p.gx = -p.xi*factor;
		p.gy = -p.yi*factor;
		p.gz = -p.zi*factor;

		mParticles.push_back(p);
	}
	mParticleSize = 0.1;
}

void Explosion::Draw()
{
	glEnable (GL_BLEND); 
	glBlendFunc (GL_ONE,GL_ONE);
	glClear(GL_ACCUM_BUFFER_BIT);

	for(int i = 0;i<MAX_PARTICLE;++i)
	{
		glPointSize(5.0);
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

		glBegin(GL_QUADS);
		//glTexCoord2f(0.0f,0.0f);
		glVertex3f(x-mParticleSize,y-mParticleSize,z);
		//glTexCoord2f(1.0f,0.0f);
		glVertex3f(x-mParticleSize,y+mParticleSize,z);
		//glTexCoord2f(1.0f,1.0f);
		glVertex3f(x+mParticleSize,y+mParticleSize,z);
		//glTexCoord2f(0.0f,1.0f);
		glVertex3f(x+mParticleSize,y-mParticleSize,z);
		glEnd();
	}  
	glDisable(GL_BLEND);
}
