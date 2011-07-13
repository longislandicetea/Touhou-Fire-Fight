#include "BSlower.h"
#include "Md2Object.h"

BSlower::BSlower()
{
	//mModel = Md2Object::Load("c:\\box.md2","c:\\boxbrown.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","slower","resource\\data.ini"),DataManager::GetDataPath("Texture","slowerT","resource\\data.ini"));
	this->AddChild(mModel);
}
