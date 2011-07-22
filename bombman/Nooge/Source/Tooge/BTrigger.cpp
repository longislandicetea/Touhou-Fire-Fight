#include "BTrigger.h"
#include "Md2Object.h"

BTrigger::BTrigger()
{
	//mModel = Md2Object::Load("c:\\box.md2","c:\\yellowbox.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","trigger","resource\\data.ini"),DataManager::GetDataPath("Texture","triggerT","resource\\data.ini"));
	mModel->SetRotateY(270);
	mModel->SetRotateX(270);
	mModel->SetY(GetY()-3);
	this->AddChild(mModel);
}