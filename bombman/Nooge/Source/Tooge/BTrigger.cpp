#include "BTrigger.h"
#include "Md2Object.h"

BTrigger::BTrigger()
{
	mModel = Md2Object::Load("c:\\box.md2","c:\\bluebox.bmp");
	this->AddChild(mModel);
}
