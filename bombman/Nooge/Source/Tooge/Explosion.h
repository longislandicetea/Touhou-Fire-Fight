#pragma once

#include <vector>
#include "GameObject.h"
#include "Ref.h"
#include "Texture.h"

class Explosion : public GameObject
{
public:
	Explosion(float x,float y,float z);
	virtual void Draw(bool is3D);
	virtual void Update(float dt);
	virtual ~Explosion(){}

private:
	float mParticleSize;
	bool isDead;
	float mLife;
	Ref<Texture> mFlameTex;
};
