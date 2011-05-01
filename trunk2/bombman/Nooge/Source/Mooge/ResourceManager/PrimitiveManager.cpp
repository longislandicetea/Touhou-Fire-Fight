#include "PrimitiveManager.h"
#include <windows.h>
#include <gl/GL.h>
#include "Line.h"
#include "MoogeUtility.h"

//Default constructor.
CPrimitiveManager::CPrimitiveManager()
{
	PRIMITIVEIDSEQ = 1000000000;
}

//Default destructor.
CPrimitiveManager::~CPrimitiveManager()
{
	for (map<PRIMITIVEID, CLine*>::iterator MapIter = mLineMap.begin() ; MapIter != mLineMap.end() ; MapIter++)
	{
		delete MapIter->second;
	}
	mLineMap.clear();

    for (map<PRIMITIVEID, CLine*>::iterator MapIter = mBoldLineMap.begin() ; MapIter != mBoldLineMap.end() ; MapIter++)
	{
		delete MapIter->second;
	}
	mBoldLineMap.clear();
}

//Render all primitives.
void CPrimitiveManager::Draw()
{
	//[Draw] All line objects(normal line).
	if(mLineMap.size() > 0)
	{
		glLineWidth(0.5);
		glBegin(GL_LINES);
			for(map<PRIMITIVEID, CLine*>::iterator MapIter = mLineMap.begin() ; MapIter != mLineMap.end() ; MapIter++)
			{
				MapIter->second->Draw();
			}
		glEnd();
	}

	//[Draw] All line objects(bold line).
	if(mBoldLineMap.size() > 0)
	{
		glLineWidth(3.0);
		glBegin(GL_LINES);
			for(map<PRIMITIVEID, CLine*>::iterator BoldMapIter = mBoldLineMap.begin() ; BoldMapIter != mBoldLineMap.end() ; BoldMapIter++)
			{
				BoldMapIter->second->Draw();
			}
		glEnd();
	}
}

bool CPrimitiveManager::AddLine(VECTORFA StartPos, VECTORFA EndPos)
{
	//Current primitive seq +1;
	PRIMITIVEIDSEQ++;

	//New the object and store it into the map.
	mLineMap[PRIMITIVEIDSEQ] = new CLine(StartPos, EndPos, PRIMITIVEIDSEQ);

	//This function wont failed.
	return true;
}

bool CPrimitiveManager::AddLine(VECTORFS StartPos, VECTORFS EndPos)
{
	//Convert VECTORFS to VECTORFA type.(structure to array)
	VECTORFA tmpStartPosArray;
	VECTORFA tmpEndPosArray;

	ConvertVectorS2A(StartPos, tmpStartPosArray);
	ConvertVectorS2A(EndPos, tmpEndPosArray);

	//Call sub function.
	AddLine(tmpStartPosArray, tmpEndPosArray);

	//This function wont failed.
	return true;
}

bool CPrimitiveManager::AddLine(VECTORFA StartPos, VECTORFA EndPos, CLine*& ReturnPtr)
{
	//Call sub function.
	AddLine(StartPos, EndPos);

	//Return the object pointer to user.
	ReturnPtr = mLineMap[PRIMITIVEIDSEQ];

	//This function wont failed.
	return true;
}

bool CPrimitiveManager::AddLine(VECTORFS StartPos, VECTORFS EndPos, CLine*& ReturnPtr)
{
	//Call sub function.
	AddLine(StartPos, EndPos);

	//Return the object pointer to user.
	ReturnPtr = mLineMap[PRIMITIVEIDSEQ];

	//This function wont failed.
	return true;
}

bool CPrimitiveManager::AddBoldLine(VECTORFA StartPos, VECTORFA EndPos)
{
	//Current primitive seq +1;
	PRIMITIVEIDSEQ++;

	//New the object and store it into the map.
	mBoldLineMap[PRIMITIVEIDSEQ] = new CLine(StartPos, EndPos, PRIMITIVEIDSEQ);

	return true;
}

bool CPrimitiveManager::AddBoldLine(VECTORFS StartPos, VECTORFS EndPos)
{
	//Convert VECTORFS to VECTORFA type.(structure to array)
	VECTORFA tmpStartPosArray;
	VECTORFA tmpEndPosArray;

	ConvertVectorS2A(StartPos, tmpStartPosArray);
	ConvertVectorS2A(EndPos, tmpEndPosArray);

	//Call sub function.
	AddBoldLine(tmpStartPosArray, tmpEndPosArray);

	return true;
}

bool CPrimitiveManager::AddBoldLine(VECTORFA StartPos, VECTORFA EndPos, CLine*& ReturnPtr)
{
	//Call sub function.
	AddBoldLine(StartPos, EndPos);

	//Return the object pointer to user.
	ReturnPtr = mBoldLineMap[PRIMITIVEIDSEQ];

	//This function wont failed.
	return true;
}

bool CPrimitiveManager::AddBoldLine(VECTORFS StartPos, VECTORFS EndPos, CLine*& ReturnPtr)
{
	//Call sub function.
	AddBoldLine(StartPos, EndPos);

	//Return the object pointer to user.
	ReturnPtr = mBoldLineMap[PRIMITIVEIDSEQ];

	//call the origin array type add function.
	return true;
}

bool CPrimitiveManager::RemoveLine(CLine*& ObjectPtr)
{
	//Is user a monkey?
	if(ObjectPtr == NULL)
		return false;

	//Try fine the ID in map first.
	PRIMITIVEID LineID = ObjectPtr->GetObjectID();
	map<PRIMITIVEID, CLine*>::iterator MapIter = mLineMap.find(LineID);

	if(MapIter != mLineMap.end())
	{
		//Found it.
		//Delete the object.
		delete mLineMap[LineID];
		//Set NULL to the user specific ptr.
		ObjectPtr = NULL;
		//Erase from map.
		mLineMap.erase(LineID);
		return true;
	}else
	{
		//Not found. Delete element failed.
		return false;
	}
}

bool CPrimitiveManager::RemoveBoldLine(CLine*& ObjectPtr)
{
	//Is user a monkey?
	if(ObjectPtr == NULL)
		return false;

	//Try fine the ID in map first.
	PRIMITIVEID LineID = ObjectPtr->GetObjectID();
	map<PRIMITIVEID, CLine*>::iterator MapIter = mBoldLineMap.find(LineID);

	if(MapIter != mBoldLineMap.end())
	{
		//Found it.
		//Delete the object.
		delete mBoldLineMap[LineID];
		//Set NULL to the user specific ptr.
		ObjectPtr = NULL;
		//Erase from map.
		mBoldLineMap.erase(LineID);
		return true;
	}else
	{
		//Not found. Delete element failed.
		return false;
	}
}

void CPrimitiveManager::RemoveAllLine()
{
	for (map<PRIMITIVEID, CLine*>::iterator MapIter = mLineMap.begin() ; MapIter != mLineMap.end() ; MapIter++)
	{
		delete MapIter->second;
	}
	mLineMap.clear();
}

void CPrimitiveManager::RemoveAllBoldLine()
{
	for (map<PRIMITIVEID, CLine*>::iterator MapIter = mBoldLineMap.begin() ; MapIter != mBoldLineMap.end() ; MapIter++)
	{
		delete MapIter->second;
	}
	mBoldLineMap.clear();
}