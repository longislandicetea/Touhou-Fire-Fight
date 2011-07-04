#include "BFaster.h"
#include "Md2Object.h"

BFaster::BFaster()
{
	mModel = Md2Object::Load("c:\\box.md2","c:\\boxorange.bmp");
	this->AddChild(mModel);
}
