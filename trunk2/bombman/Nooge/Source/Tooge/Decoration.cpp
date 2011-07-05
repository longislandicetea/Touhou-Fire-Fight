#include "Decoration.h"
#include "Md2Object.h"
#include <iostream>

#include "DataManager.h"

Decoration::Decoration()
{
	mModel = Md2Object::Load("c:\\floor.md2","c:\\floor1.bmp");
	//mModel = Md2Object::Load(DataManager::GetDataPath("Model","uwall","c:\\data.ini"),"c:\\bluebox.bmp");
	this->AddChild(mModel);
}

Decoration::~Decoration()
{
}