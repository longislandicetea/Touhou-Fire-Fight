#include "BDrop.h"
#include "Md2Object.h"

BDrop::BDrop()
{
	//mModel = Md2Object::Load("c:\\box.md2","c:\\boxred.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","bonus","resource\\data.ini"),DataManager::GetDataPath("Texture","red","resource\\data.ini"));
	this->AddChild(mModel);
}
