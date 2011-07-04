#include "BSlower.h"
#include "Md2Object.h"

BSlower::BSlower()
{
	mModel = Md2Object::Load("c:\\box.md2","c:\\boxbrown.bmp");
	this->AddChild(mModel);
}
