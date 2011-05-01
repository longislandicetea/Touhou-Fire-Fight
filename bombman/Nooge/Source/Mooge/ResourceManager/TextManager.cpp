#include "TextManager.h"
#include <windows.h>
#include <gl/GL.h>
#include "2DText.h"

//Default constructor.
CTextManager::CTextManager()
{
	TEXTIDSEQ = 1000000000;
}

//Default destructor.
CTextManager::~CTextManager()
{
	for (map<TEXTID, C2DText*>::iterator MapIter = m2DTextMap.begin() ; MapIter != m2DTextMap.end() ; MapIter++)
	{
		delete MapIter->second;
	}
	m2DTextMap.clear();
}

//Render all Text.
void CTextManager::Draw(unsigned int FontList)
{
	for (map<TEXTID, C2DText*>::iterator MapIter = m2DTextMap.begin() ; MapIter != m2DTextMap.end() ; MapIter++)
	{
		MapIter->second->Draw(FontList);
	}
}

bool CTextManager::Add2DText(string Str, unsigned int PosX, unsigned int PosY, C2DText*& ReturnPtr)
{
	//Current primitive seq +1;
	TEXTIDSEQ++;

	//New the object and store it into the map.
	m2DTextMap[TEXTIDSEQ] = new C2DText(Str, PosX, PosY, TEXTIDSEQ);

	//Return the object ptr to user.
	ReturnPtr = m2DTextMap[TEXTIDSEQ];

	return true;
}

bool CTextManager::Remove2DText(C2DText*& ObjectPtr)
{
	//Is user a monkey?
	if(ObjectPtr == NULL)
		return false;

	//Try fine the ID in map first.
	PRIMITIVEID Text2DID = ObjectPtr->GetObjectID();
	map<TEXTID, C2DText*>::iterator MapIter = m2DTextMap.find(Text2DID);

	if(MapIter != m2DTextMap.end())
	{
		//Found it.
		//Delete the object.
		delete m2DTextMap[Text2DID];
		//Set NULL to the user specific ptr.
		ObjectPtr = NULL;
		//Erase from map.
		m2DTextMap.erase(Text2DID);
		return true;
	}else
	{
		//Not found. Delete element failed.
		return false;
	}
}

void CTextManager::RemoveAll2DText()
{

}