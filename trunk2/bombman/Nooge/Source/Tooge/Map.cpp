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
