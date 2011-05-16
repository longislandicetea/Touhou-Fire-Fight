#include"Map.h"
#include <string>
#include<vector>
#include "tinyxml.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>


void Map::Load(const char* filename)
{
	TiXmlDocument* doc = new TiXmlDocument();
	doc->LoadFile(filename);
	TiXmlElement* rootElement = doc->RootElement();
	TiXmlElement* gridsElement = rootElement->FirstChildElement();
	TiXmlElement* gridElement = gridsElement->FirstChildElement();
	while(gridElement)
	{
		GridInfo tmp;
		TiXmlElement* rowElement = gridElement->FirstChildElement();
		tmp.row = atoi(rowElement->GetText());
		TiXmlElement* colElement = rowElement->NextSiblingElement();
		tmp.col = atoi(colElement->GetText());
		TiXmlElement* stateElement = colElement->NextSiblingElement();
		tmp.gridState = Trans(stateElement->GetText());
		mGrids.push_back(tmp);
		gridElement = gridElement->NextSiblingElement();
	}
	TiXmlElement* bonusElement = gridsElement->NextSiblingElement();
	while(bonusElement)
	{
		std::string tmp(bonusElement->Value());
		mBonus[tmp] = (float)(atoi(bonusElement->GetText())/100.0);
		bonusElement = bonusElement->NextSiblingElement();
	}
}

bool Map::CanPass( int gridId )
{
	if(mGrids[gridId].gridState == DWALL||mGrids[gridId].gridState == UWALL)
		return false;
	return true;
}

GridState Map::Trans( const char* gridState )
{
	if(!strcmp(gridState,"Empty"))
		return EMPTY;
	else if(!strcmp(gridState,"Dwall"))
		return DWALL;
	else if(!strcmp(gridState,"Uwall"))
		return UWALL;
	else if(!strcmp(gridState,"Player"))
		return PLAYER;
	else
		return NPC;
}

void Map::Display()
{
	for(unsigned int i = 0;i<mGrids.size();++i)
	{
		std::cout<<mGrids[i].row<<" "<<mGrids[i].col<<" "<<mGrids[i].gridState<<std::endl;
	}

	std::map<std::string,float>::iterator it;
	for(it = mBonus.begin();it!=mBonus.end();++it)
		std::cout<<it->first<<" "<<it->second<<std::endl;
}
