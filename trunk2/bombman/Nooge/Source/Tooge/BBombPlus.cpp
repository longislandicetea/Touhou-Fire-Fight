#include "BBombPlus.h"
#include "Md2Object.h"

BBombPlus::BBombPlus()
{
	//mModel = Md2Object::Load("c:\\box.md2","c:\\bluebox.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","bonus","resource\\data.ini"),DataManager::GetDataPath("Texture","blue","resource\\data.ini"));
	mModel->SetRotateY(270);
	mModel->SetScale(0.7);
	this->AddChild(mModel);
}
