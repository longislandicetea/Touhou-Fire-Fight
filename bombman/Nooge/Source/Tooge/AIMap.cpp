#include "AIMap.h"

AIMap::AIMap( int initValue )
{
	Reset(initValue);
}

void AIMap::Reset( int value )
{
	for(int i = 0;i<WIDTH;++i)
		for(int j = 0;j<HEIGHT;++j)
			this->value[i][j] = value;
}

int AIMap::GetValue( int row,int col )
{
	return this->value[row][col];
}

void AIMap::SetValue( int row,int col,float value )
{
	this->value[row][col] = value;
}


bool AIMap::IsFree( int row, int col )
{
	if(value[row][col] == -1)
		return false;
	return true;
}

bool AIMap::IsInside(int row,int col)
{
	if(row>=0 && row<WIDTH && col >=0 && col<HEIGHT)
		return true;
	return false;
}

int AIMap::GetHeight()
{
	return HEIGHT;
}

int AIMap::GetWidth()
{
	return WIDTH;
}
