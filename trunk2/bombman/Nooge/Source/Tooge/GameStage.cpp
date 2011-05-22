#include "GameStage.h"

Ref<GameObject> GameStage::CurrentMap()
{
	return mCurrentMap;
}

GameStage::GameStage( Ref<GameObject> map ) : mCurrentMap(map)
{

}
