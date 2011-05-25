#include "Bomb.h"
#include "Md2Object.h"

Bomb::Bomb()
{
	mModel = Md2Object::Load("c:\\box.md2","c:\\yellowbox.bmp");
	this->AddChild(mModel);
	mTimeToExplosion = 1.0;
	mFlamePower = 1;
}

/*void Bomb::Update()
{

}*/
