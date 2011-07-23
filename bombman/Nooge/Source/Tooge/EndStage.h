#pragma once

#include "Stage.h"
#include "GameObject.h"

#include <vector>

class EndStage : public Stage
{
public:
	static Ref<Stage> LoadStage(const std::string& result);
	void HandleClickEvent(int x,int y);
	virtual ~EndStage() {}
private:
	EndStage(const std::string& result);
	Ref<GameObject> mGuiObject;
};