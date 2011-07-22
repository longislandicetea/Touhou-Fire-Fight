#include "BDrop.h"
#include "Md2Object.h"

BDrop::BDrop()
{
	//mModel = Md2Object::Load("c:\\box.md2","c:\\boxred.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","drop","resource\\data.ini"),DataManager::GetDataPath("Texture","dropT","resource\\data.ini"));
	mModel->SetRotateY(270);
	mModel->SetY(GetY()-5);
	this->AddChild(mModel);
}
