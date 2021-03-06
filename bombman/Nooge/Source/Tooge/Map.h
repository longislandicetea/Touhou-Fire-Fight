#pragma once
#include<vector>
#include <map>
#include<string>
#include "GameObjectContainer.h"
#include "GameObject.h"
#include "Ref.h"


enum GridState
{
	EMPTY, DWALL,UWALL,NPC,PLAYER
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
	static Ref<GameObject> Load(const std::string& filename,int mLevel);
	std::map< std::string,Ref<GameObject> >Parse();
	std::map<std::string,int> GetBonusProb();

protected:
	Map();
	std::vector<GridInfo> mGrids;
	std::map<std::string,int> mBonus;

private:
	GridState trans(const char* gridState);
	int mLevel;
};