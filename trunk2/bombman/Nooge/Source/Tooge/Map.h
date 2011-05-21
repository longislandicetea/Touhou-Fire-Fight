#pragma once
#include<vector>
#include <map>
#include<string>
#include "GameObjectContainer.h"


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
	void Load(const char* filename);

protected:
	std::vector<GridInfo> mGrids;
	std::map<std::string,float> mBonus;
	
private:
	GridState Trans(const char* gridState);
};