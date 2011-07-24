#pragma once
#include<vector>

class Pos
{
public:
	int row;
	int col;

	Pos(int tcol,int trow){row = trow;col = tcol;}
	Pos(){}
	int GetRow(){return row;}
	int GetCol(){return col;}
	//"=="
	bool operator == (const Pos& pos)
	{
		if(this->col == pos.col && this->row == pos.row)
			return true;
		return false;
	}
	
};

class AIMap
{
public:
	AIMap(int initValue);
	void Reset(int value);
	int GetValue(int col,int row);
	int GetValue(Pos pos);
	void SetValue(int row,int col,float value);
	bool IsFree(int row, int col);
	 std::vector<Pos> GetValuePositions(float tvalue);

	bool IsInside(int col,int row);
	int GetWidth();
	int GetHeight();

private:
	static const int WIDTH = 15;
	static const int HEIGHT = 13;
	float value[WIDTH][HEIGHT];
	float maxValue;
};