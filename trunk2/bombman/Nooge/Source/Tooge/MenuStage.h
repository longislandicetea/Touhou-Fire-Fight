#pragma once

#include "Stage.h"
#include "GameObject.h"

#include <vector>

class MenuStage : public Stage
{
public:
	static Ref<Stage> LoadStage();
	void HandleClickEvent(int x,int y);
	virtual ~MenuStage() {}
private:
	MenuStage();
	Ref<GameObject> mGuiObject;
};