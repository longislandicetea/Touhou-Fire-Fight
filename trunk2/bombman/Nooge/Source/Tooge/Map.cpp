#include"Map.h"
#include <string>
#include<vector>
#include "tinyxml.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "Dwall.h"
#include "Uwall.h"
#include "Bonus.h"
#include "Character.h"
#include "PlayerController.h"
#include "NPCController.h"
#include "Grid.h"
#include "AIMap.h"
#include "Decoration.h"
#include "DataManager.h"


Ref<GameObject> Map::Load( const std::string& filename,int level)
{
	Ref<GameObject> tmp (new Map);
	Map* ret= cast<Map>(tmp);
	TiXmlDocument* doc = new TiXmlDocument();
	doc->LoadFile(filename.c_str());
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
		tmp.gridState = ret->trans(stateElement->GetText());
		ret->mGrids.push_back(tmp);
		gridElement = gridElement->NextSiblingElement();
	}
	TiXmlElement* bonusElement = gridsElement->NextSiblingElement();
	while(bonusElement)
	{
		std::string tmp(bonusElement->Value());
		ret->mBonus[tmp] = (float)(atoi(bonusElement->GetText()));
		bonusElement = bonusElement->NextSiblingElement();
	}
	cast<Map>(tmp)->mLevel = level;
	return tmp;
}

GridState Map::trans( const char* gridState )
{
	if(!strcmp(gridState,"Empty"))
		return EMPTY;
	else if(!strcmp(gridState,"Dwall"))
		return DWALL;
	else if(!strcmp(gridState,"Uwall"))
		return UWALL;
	else if(!strcmp(gridState,"Player"))
		return PLAYER;
	else if(!strcmp(gridState,"NPC"))
		return NPC;
}

Map::Map()
{

}

std::map< std::string,Ref<GameObject> > Map::Parse()
{
	switch (mLevel)
	{
	case 1:
		this->Load(DataManager::GetDataPath("Map","level1","resource\\data.ini"),1);
	case 2:
		this->Load(DataManager::GetDataPath("Map","level2","resource\\data.ini"),2);
	case 3:
		this->Load(DataManager::GetDataPath("Map","level3","resource\\data.ini"),3);
	}
	Ref<GameObject> uwallContainer(new Sprite),dwallContainer(new Sprite),npcContainer(new Sprite),playerContainer(new Sprite);
	Ref<GameObject> decContainer(new Sprite);
	std::map< std::string,Ref<GameObject> > ret;

	ret["uwall"] = uwallContainer;
	ret["dwall"] = dwallContainer;
	ret["npc"] = npcContainer;
	ret["player"] = playerContainer;
	ret["decoration"] = decContainer;

	Ref<GameObject> floor = Decoration::CreateDecoration("floor");
	floor->SetScale(1.5);
	floor->SetPos(55,-10,55);

	Ref<GameObject> bamboo = Decoration::CreateDecoration("bamboo");
	bamboo->SetPos(0,0,0);

	cast<Sprite>(decContainer)->AddChild(floor);
	cast<Sprite>(decContainer)->AddChild(bamboo);

	int npcCnt= 0;

	for(int i = 0;i<mGrids.size();++i)
	{
		GridInfo tmp = mGrids[i];
		int row = tmp.row;
		int col = tmp.col;

		Grid*  currentGrid = new Grid(row,col);

		switch (tmp.gridState)
		{
		case DWALL:
			{
				Ref<GameObject> dwall(new Dwall);
				dwall->SetPos(currentGrid->CenterX(),0.0,currentGrid->CenterY());
				dwall->SetY(-5);
				cast<Sprite>(dwallContainer)->AddChild(dwall);
				break;
			}
		case UWALL:
			{
				Ref<GameObject> uwall(new Uwall);
				uwall->SetPos(currentGrid->CenterX(),0.0,currentGrid->CenterY());
				cast<Sprite>(uwallContainer)->AddChild(uwall);
				break;
			}
		case PLAYER:
			{
				/*PlayerController* playerCtrl = new PlayerController();
				Ref<GameObject> player = Character::AddController(playerCtrl);*/
				Ref<GameObject> player = Character::CreateCharacter("player");
				player->SetPos(currentGrid->CenterX(),0.0,currentGrid->CenterY());
				player->SetRotateY(90);
				cast<Sprite>(playerContainer)->AddChild(player);
				break;
			}
		case NPC :
			{
				/*NPCController* npcCtrl = new NPCController();
				Ref<GameObject> npc = Character::AddController(npcCtrl);*/
				Ref<GameObject> npc;
				switch(npcCnt)
				{
				case 0:
					npc = Character::CreateCharacter("npc1");
					break;
				case 1:
					npc = Character::CreateCharacter("npc2");
					break;
				case 2:
					npc = Character::CreateCharacter("npc3");
					break;
				}
				++npcCnt;
				npc->SetPos(currentGrid->CenterX(),0.0,currentGrid->CenterY());
				npc->SetRotateY(90);
				cast<Sprite>(npcContainer)->AddChild(npc);
				break;
			}
		case EMPTY:
			break;
		}

		if(currentGrid != NULL)
			delete currentGrid;
	}

	return ret;
}

std::map<std::string,int> Map::GetBonusProb()
{
	return mBonus;
}
