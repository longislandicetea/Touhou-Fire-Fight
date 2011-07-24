#pragma once

#include "Stage.h"
#include "GameObject.h"

#include <vector>

class ConfigStage : public Stage
{
public:
	static Ref<Stage> LoadStage();
	void HandleClickEvent(int x,int y);
	virtual ~ConfigStage() {}

	virtual void Update(float dt);
private:
	ConfigStage();
	Ref<GameObject> mGuiObject;
	bool isBgmOn,isSndOn;
	int mouseX,mouseY;
};