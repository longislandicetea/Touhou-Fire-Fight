#include "Decoration.h"
#include "Md2Object.h"
#include <iostream>

#include "DataManager.h"

Decoration::Decoration()
{
	mModel = Md2Object::Load("c:\\floor.md2","c:\\floor1.bmp");
	//mModel = Md2Object::Load(DataManager::GetDataPath("Model","floor","resource\\data.ini"),DataManager::GetDataPath("Texture","floorT","resource\\data.ini"));
	this->AddChild(mModel);
}

Decoration::~Decoration()
{
}