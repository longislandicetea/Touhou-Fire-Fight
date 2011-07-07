#include "BTrigger.h"
#include "Md2Object.h"

BTrigger::BTrigger()
{
	//mModel = Md2Object::Load("c:\\box.md2","c:\\yellowbox.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","bonus","resource\\data.ini"),DataManager::GetDataPath("Texture","yellow","resource\\data.ini"));
	this->AddChild(mModel);
}
