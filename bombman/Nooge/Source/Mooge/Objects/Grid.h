#pragma once

#include "Ref.h"

class Grid
{
public:
	Grid(float x1,float y1,float x2,float y2);
	Grid(int row,int col);
	static float SideLen;

	float X1();
	float Y1();
	float X2();
	float Y2();
	float CenterX();
	float CenterY();
	int Row();
	int Col();

	bool TestPoint(float x,float y);
	bool Intersect(Grid grid);

private:
	float mX1,mY1,mX2,mY2;
	int mRow,mCol;
};