#pragma once

class AIMap
{
public:
	AIMap(int initValue);
	void Reset(int value);
	int GetValue(int col,int row);
	void SetValue(int row,int col,float value);
	bool IsFree(int row, int col);
	void GetBestValuePosition(int x,int y);

	bool IsInside(int col,int row);
	int GetWidth();
	int GetHeight();

private:
	static const int WIDTH = 15;
	static const int HEIGHT = 13;
	float value[WIDTH][HEIGHT];
};