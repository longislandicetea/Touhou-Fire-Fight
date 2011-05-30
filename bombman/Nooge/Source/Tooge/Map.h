#pragma once
#include<vector>
#include <map>
#include<string>
#include "GameObjectContainer.h"
#include "GameObject.h"
#include "Ref.h"


enum GridState
{
	EMPTY, DWALL,UWALL,PLAYER,NPC
};

struct GridInfo
{
	GridState gridState;
	int col;
	int row;
};

class RuntimeMap;
class Map : public Sprite
{
public:
	friend class RuntimeMap;
	static Ref<GameObject> Load(const std::string& filename);
	std::map< std::string,Ref<GameObject> >Parse();

protected:
	Map();
	std::vector<GridInfo> mGrids;
	std::map<std::string,float> mBonus;

private:
	GridState trans(const char* gridState);
};