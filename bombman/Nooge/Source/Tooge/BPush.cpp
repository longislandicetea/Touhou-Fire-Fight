#include "BPush.h"
#include "Md2Object.h"


BPush::BPush()
{
	mModel = Md2Object::Load("c:\\box.md2","c:\\bluebox.bmp");
	this->AddChild(mModel);
}
