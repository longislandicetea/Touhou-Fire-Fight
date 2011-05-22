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

void AIMap::SetValue( int row,int col,int value )
{
	this->value[row][col] = value;
}

void AIMap::ComputeFloodFill()
{

}
