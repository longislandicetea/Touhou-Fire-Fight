#include "Grid.h"

Grid::Grid( float x1,float y1,float x2,float y2 )
{
	mX1 = x1;
	mY1 = y1;
	mX2 = x2;
	mY2 = y2;
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

bool Grid::Intersect( Ref<Grid> grid )
{
	float x1 = grid->X1();
	float x2 = grid->X2();
	float y1 = grid->Y1();
	float y2 = grid->Y2();

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
