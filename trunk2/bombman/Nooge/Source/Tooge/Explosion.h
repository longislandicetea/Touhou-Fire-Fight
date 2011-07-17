#pragma once

#include <vector>
#include "GameObject.h"
#include "Ref.h"
#include "Texture.h"

#define MAX_PARTICLE 50
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

class Explosion : public GameObject
{
public:
	Explosion(float x,float y,float z);
	virtual void Draw(bool is3D);
	virtual void Update(float dt);
	virtual ~Explosion(){}

private:
	std::vector<Particle> mParticles;
	Ref<Texture> mFlameTex;
	float mParticleSize;
	bool isDead;
	//sbool isDead();
};