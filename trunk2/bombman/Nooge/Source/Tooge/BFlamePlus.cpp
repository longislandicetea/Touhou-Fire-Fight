#include "BFlamePlus.h"
#include "Md2Object.h"

BFlamePlus::BFlamePlus()
{
	//mModel = Md2Object::Load("c:\\box.md2","c:\\boxgreen.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","bonus","resource\\data.ini"),DataManager::GetDataPath("Texture","green","resource\\data.ini"));
	this->AddChild(mModel);
}
