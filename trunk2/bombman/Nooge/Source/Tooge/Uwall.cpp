#include "Uwall.h"
#include "Md2Object.h"

Uwall::Uwall()
{
	mModel = Md2Object::Load("c:\\box.md2","c:\\bluebox.bmp");
	this->AddChild(mModel);
}