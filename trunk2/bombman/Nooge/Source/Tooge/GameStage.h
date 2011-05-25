#pragma once

#include "Stage.h"
#include "Ref.h"
#include "RuntimeMap.h"
#include "GameObject.h"

class GameStage : public Stage
{
public:
	GameStage(Ref<GameObject> map);
	Ref<GameObject> CurrentMap();
private:
	Ref<GameObject> mCurrentMap;
};                                                                                                                                                                                                                                                                                                                                                                                                     