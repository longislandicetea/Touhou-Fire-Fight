#include "Explosion.h"

#include<windows.h>
#include <GL/gl.h>

#include <stdlib.h>

#include "WinFrame.h"
#include "DataManager.h"

Explosion::Explosion( float x,float y,float z )
{
        mFlameTex = Texture::Load(DataManager::GetDataPath("Texture","flameT","resource\\data.ini"));
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
                p.fade = rand()%10/50.0+0.1;

                float factor = 3;
                p.gx = -p.xi*factor;
                p.gy = -p.yi*factor;
                p.gz = -p.zi*factor;

                mParticles.push_back(p);
        }
        mParticleSize = 1;
        isDead = false;
}

void Explosion::Draw(bool is3D)
{
        //return;
        if (!is3D) return;
        glEnable (GL_BLEND); 
        glBlendFunc (GL_ONE,GL_ONE);

        Texture::Bind(mFlameTex);
        for(int i = 0;i<MAX_PARTICLE;++i)
        {
                if(mParticles[i].life>0.0)
                {
                        int x = mParticles[i].x;
                        int y = mParticles[i].y;
                        int z = mParticles[i].z;

                        glBegin(GL_POINTS);
                                glTexCoord2d(1,1); glVertex3f(x-mParticleSize,y-mParticleSize,z); 
                                glTexCoord2d(0,1); glVertex3f(x-mParticleSize,y+mParticleSize,z); 
                                glTexCoord2d(1,0); glVertex3f(x+mParticleSize,y+mParticleSize,z); 
                                glTexCoord2d(0,0); glVertex3f(x+mParticleSize,y-mParticleSize,z);
                        glEnd();

                }
        }
        glDisable(GL_BLEND);
}

/*bool Explosion::isDead()
{
        for(int i = 0;i<mParticles.size();++i)
        {
                if(mParticles[i].life>0.0)
                        return false;
        }
        return true;
}*/

void Explosion::Update( float dt )
{
        if(isDead)
                this->RemoveFromParent();
        else
                isDead = true;
        for(int i = 0;i<MAX_PARTICLE;++i)
        {
                if(mParticles[i].life>0.0)
                {
                        isDead = false;
                        glPointSize(10.0);
                        int x = mParticles[i].x;
                        int y = mParticles[i].y;
                        int z = mParticles[i].z;

                        mParticles[i].x += mParticles[i].xi/(dt* 100000.0);
                        mParticles[i].xi += mParticles[i].gx;
                        mParticles[i].y += mParticles[i].yi/(dt* 100000.0);
                        mParticles[i].yi += mParticles[i].gy;
                        mParticles[i].z += mParticles[i].zi/(dt* 100000.0);
                        mParticles[i].zi += mParticles[i].gz;

                        mParticles[i].life -= mParticles[i].fade;
                }
        }
}
