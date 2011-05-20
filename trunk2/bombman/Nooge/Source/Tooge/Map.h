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
	bool CanPass(int gridId);
private:
	std::vector<GridInfo> mGrids;
	std::map<std::string,float> mBonus;
	
	GridState Trans(const char* gridState);
};