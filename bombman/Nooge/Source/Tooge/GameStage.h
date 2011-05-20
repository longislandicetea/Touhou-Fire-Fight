#pragma once

#include "Stage.h"
#include "Ref.h"
#include "Map.h"

class GameStage : public Stage
{
public:
	GameStage();
	void SetMap(Ref<Map> map);
private:
	Ref<Map> mCurrentMap;
};