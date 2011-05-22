#include "Grid.h"

float Grid::SideLen = 10.0;

Grid::Grid( float x1,float y1,float x2,float y2 )
{
	mX1 = x1;
	mY1 = y1;
	mX2 = x2;
	mY2 = y2;
}

Grid::Grid( int row,int col )
{
	mX1 = (col-7)*SideLen;
	mY1 = (row-5)*SideLen;
	mX2 = (col-6)*SideLen;
	mY2 = (row-6)*SideLen;
}

float Grid::X1()
{
	return mX1;
}

float Grid::Y1()
{
	return mY1;
}

float Grid::X2()
{
	return mX2;
}

float Grid::Y2()
{
	return mY2;
}

bool Grid::TestPoint( float x,float y )
{
	if(x<mX2 && x>mX1 && y<mY2 && y>mY1)
		return true;
	return false;
}

bool Grid::Intersect(Grid grid )
{
	float x1 = grid.X1();
	float x2 = grid.X2();
	float y1 = grid.Y1();
	float y2 = grid.Y2();

	if(TestPoint(x1,y1) || TestPoint(x1,y2) || TestPoint(x2,y1) || TestPoint(x2,y2))
		return true;
	return false;
}

float Grid::CenterX()
{
	return (mX1+mX2)/2;
}

float Grid::CenterY()
{
	return (mY1+mY2)/2;
}

int Grid::Row()
{
	return mRow;
}

int Grid::Col()
{
	return mCol;
}
