#include "BDrop.h"
#include "Md2Object.h"

BDrop::BDrop()
{
	mModel = Md2Object::Load("c:\\box.md2","c:\\boxred.bmp");
	this->AddChild(mModel);
}
