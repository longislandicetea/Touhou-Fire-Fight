#pragma once

#include "Ref.h"
#include "Texture.h"
#include "GameObject.h"

class Cube :
	public GameObject
{
public:
	Cube(void);
	~Cube(void);

	virtual void Draw();
	virtual void Update(float dt);

private:
	Ref<Texture> mTex;
};

