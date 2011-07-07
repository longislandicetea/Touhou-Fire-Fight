#include "Dwall.h"
#include <iostream>
using namespace std;

Dwall::Dwall()
{
	//mModel = Md2Object::Load("c:\\wall.md2","c:\\dwallt.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","dwall","resource\\data.ini"),DataManager::GetDataPath("Texture","dwallT","resource\\data.ini"));
	this->AddChild(mModel);
}

Dwall::~Dwall()
{
	cout << "Dwall released" << endl;
}
