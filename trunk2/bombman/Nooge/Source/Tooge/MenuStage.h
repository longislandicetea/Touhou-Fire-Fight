#pragma once

#include "Stage.h"
#include "GameObject.h"

class MenuStage : public Stage
{
public:
	MenuStage();
private:
	Ref<GameObject> mGuiObject;
};