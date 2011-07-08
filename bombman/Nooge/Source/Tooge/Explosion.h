#pragma once

#include <vector>
#include "GameObjectContainer.h"

#define MAX_PARTICLE 100
#define DEFAULT_R 0.75f
#define DEFAULT_G 0.2f
#define DEFAULT_B 0.1f

typedef struct
{
	float x,y,z;  //position
	float xi,yi,zi; //direction
	float r,g,b; //color
	float life;
	float fade;
	float gx,gy,gz;
}
Particle;

class Explosion : public Sprite
{
public:
	Explosion(float x,float y,float z);
	void Draw();
	virtual ~Explosion(){}

private:
	std::vector<Particle> mParticles;
	float mParticleSize;

};