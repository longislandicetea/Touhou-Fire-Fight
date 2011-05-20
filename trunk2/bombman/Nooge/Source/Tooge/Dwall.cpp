#include "Dwall.h"

Dwall::Dwall()
{
	mModel = Md2Object::Load("c:\\mh_normal.md2","c:\\t2.bmp");
	this->AddChild(mModel);
}
