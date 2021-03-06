#pragma once

#include "Stage.h"
#include "GameObject.h"

#include <vector>

class SelectStage : public Stage
{
public:
	static Ref<Stage> LoadStage();
	void HandleClickEvent(int x,int y);
	virtual void Update(float dt);
	virtual ~SelectStage() {}
private:
	SelectStage();
	Ref<GameObject> mGuiObject;
};