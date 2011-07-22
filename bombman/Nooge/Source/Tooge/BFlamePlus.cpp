#include "BFlamePlus.h"
#include "Md2Object.h"

BFlamePlus::BFlamePlus()
{
	//mModel = Md2Object::Load("c:\\box.md2","c:\\boxgreen.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","addflame","resource\\data.ini"),DataManager::GetDataPath("Texture","addflameT","resource\\data.ini"));
	mModel->SetScale(0.9);
	mModel->SetY(GetY()-3);
	this->AddChild(mModel);
}
