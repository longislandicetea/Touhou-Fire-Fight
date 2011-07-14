#pragma once

#include "GameObjectContainer.h"
#include "Ref.h"

#include <string>

class Decoration : public Sprite
{
public :
	static Ref<GameObject> CreateDecoration(const std::string& type);
	virtual ~Decoration();

private:
	Decoration(const std::string& type);
	Ref<GameObject> mModel;
};