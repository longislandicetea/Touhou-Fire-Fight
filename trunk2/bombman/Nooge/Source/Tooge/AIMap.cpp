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

int AIMap::GetValue( int col,int row )
{
	return this->value[col][row];
}

void AIMap::SetValue( int col,int row,float value )
{
	this->value[col][row] = value;
}


bool AIMap::IsFree( int row, int col )
{
	if(value[row][col] == -1)
		return false;
	return true;
}

bool AIMap::IsInside(int col,int row)
{
	if(row>=0 && row<HEIGHT && col >=0 && col<WIDTH)
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
