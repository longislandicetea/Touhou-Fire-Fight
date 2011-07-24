#pragma once

#include "Stage.h"
#include "GameObject.h"

#include <vector>

class HelpStage : public Stage
{
public:
	static Ref<Stage> LoadStage();
	void HandleClickEvent(int x,int y);
	virtual ~HelpStage() {}

	virtual void Update(float dt);
private:
	HelpStage();
	Ref<GameObject> mGuiObject;
};