#include "Decoration.h"
#include "Md2Object.h"
#include <iostream>

#include "DataManager.h"

Decoration::Decoration(const std::string& type)
{
	//mModel = Md2Object::Load("c:\\floor.md2","c:\\floor1.bmp");
	if(type == "floor")
	{
		mModel = Md2Object::Load(DataManager::GetDataPath("Model","floor","resource\\data.ini"),DataManager::GetDataPath("Texture","floorT","resource\\data.ini"));
	}
	else if (type == "bamboo")
	{
		mModel = Md2Object::Load(DataManager::GetDataPath("Model","bamboo","resource\\data.ini"),DataManager::GetDataPath("Texture","bambooT","resource\\data.ini"));
	}
	this->AddChild(mModel);
}

Decoration::~Decoration()
{
}

Ref<GameObject> Decoration::CreateDecoration( const std::string& type )
{
	return Ref<GameObject> (new Decoration(type));
}
