#include "BPush.h"
#include "Md2Object.h"


BPush::BPush()
{
	//mModel = Md2Object::Load("c:\\box.md2","c:\\boxpink.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","push","resource\\data.ini"),DataManager::GetDataPath("Texture","pushT","resource\\data.ini"));
	mModel->SetRotateY(90);
	mModel->SetY(GetY()-3);
	//mModel->SetRotateX(90);
	this->AddChild(mModel);
}
