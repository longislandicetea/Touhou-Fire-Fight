#include "Dwall.h"
#include <iostream>


Dwall::Dwall()
{
	//mModel = Md2Object::Load("c:\\wall.md2","c:\\dwallt.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","dwall","resource\\data.ini"),DataManager::GetDataPath("Texture","dwallT","resource\\data.ini"));
	this->AddChild(mModel);
}

Dwall::~Dwall()
{
	//cout << "Dwall released" << endl;
}

Grid Dwall::GetBoundingBox()
{
	float offset = Grid::SideLen/2-1.5;
	return Grid(GetX()-offset,GetZ()+offset,GetX()+offset,GetZ()-offset);
}
