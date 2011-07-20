#pragma once

#include "Stage.h"
#include "GameObject.h"

#include <vector>

class SelectStage : public Stage
{
public:
	static Ref<Stage> LoadStage();
	void HandleClickEvent(int x,int y);
	//virtual void Draw(bool is3D);
	virtual ~SelectStage() {}
private:
	SelectStage();
	Ref<GameObject> mGuiObject;
};