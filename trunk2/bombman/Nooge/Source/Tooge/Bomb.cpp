#include "Bomb.h"
#include "Md2Object.h"

Bomb::Bomb()
{
	mModel = Md2Object::Load("c:\\bomb.md2","c:\\bombt.bmp");
	this->AddChild(mModel);
	mTimer = Ref<Timer>(new Timer);
	mTimer->Begin();
	mFlamePower = 1;
	
}

void Bomb::Update(float dt)
{
	/*if(mTimeToExplosion > 0.0)
		mTimeToExplosion -= dt;
	else
		this->RemoveFromParent();
		*/
	if(mTimer->End()>3.0)
		this->RemoveFromParent();
}
