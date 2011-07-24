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

	maxValue = value;
}

int AIMap::GetValue( int col,int row )
{
	return this->value[col][row];
}

int AIMap::GetValue(Pos pos)
{
	return GetValue(pos.GetCol(),pos.GetRow());
}

void AIMap::SetValue( int col,int row,float value )
{
	this->value[col][row] = value;
	
	if(value>maxValue)
		maxValue = value;
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

std::vector<Pos> AIMap::GetValuePositions(float tvalue)
{
	std::vector<Pos> positions;
	
	//if the value is too large
	if(tvalue>maxValue)
		return positions;

	//float maxVal = value[0][0];
	for(int col = 0;col<WIDTH;++col)
	{
		for(int row = 0; row<HEIGHT;++row)
		{
			if(value[col][row]==tvalue)
				positions.push_back(Pos(col,row));
			/*if(value[col][row]>maxVal)
			//{
				if(value[col][row]>maxVal)
					positions.clear();
				positions.push_back(Pos(col,row));
			}*/
		}
	}
	return positions;
}
