#pragma once

class AIMap
{
public:
	AIMap(int initValue);
	void Reset(int value);
	int GetValue(int row,int col);
	void SetValue(int row,int col,int value);
	void ComputeFloodFill();
	bool IsFree(int row, int col);

private:
	static const int WIDTH = 15;
	static const int HEIGHT = 13;
	int value[WIDTH][HEIGHT];
};