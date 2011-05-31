#include "BFlamePlus.h"
#include "Md2Object.h"

BFlamePlus::BFlamePlus()
{
	mModel = Md2Object::Load("c:\\box.md2","c:\\bluebox.bmp");
	this->AddChild(mModel);
}
