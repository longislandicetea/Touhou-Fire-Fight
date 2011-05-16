#pragma once
#include<vector>
#include <map>
#include<string>


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

class Map
{
public:
	void Load(const char* filename);
	bool CanPass(int gridId);
	//void SetBomb(int gridId);

	void Display();

	//void HasBomb(int gridId);
private:
	std::vector<GridInfo> mGrids;
	std::map<std::string,float> mBonus;
	
	GridState Trans(const char* gridState);
};