#include "BFaster.h"
#include "Md2Object.h"

BFaster::BFaster()
{
	//mModel = Md2Object::Load("c:\\box.md2","c:\\boxorange.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","faster","resource\\data.ini"),DataManager::GetDataPath("Texture","fasterT","resource\\data.ini"));
	mModel->SetRotateY(270);
	mModel->SetScale(0.85);
	mModel->SetY(GetY()-3);
	this->AddChild(mModel);
}
