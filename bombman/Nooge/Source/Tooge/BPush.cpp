#include "BPush.h"
#include "Md2Object.h"


BPush::BPush()
{
	//mModel = Md2Object::Load("c:\\box.md2","c:\\boxpink.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","push","resource\\data.ini"),DataManager::GetDataPath("Texture","pushT","resource\\data.ini"));
	this->AddChild(mModel);
}
