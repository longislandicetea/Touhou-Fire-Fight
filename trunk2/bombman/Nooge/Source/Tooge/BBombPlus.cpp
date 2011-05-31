#include "BBombPlus.h"
#include "Md2Object.h"

BBombPlus::BBombPlus()
{
	mModel = Md2Object::Load("c:\\box.md2","c:\\bluebox.bmp");
	this->AddChild(mModel);
}
