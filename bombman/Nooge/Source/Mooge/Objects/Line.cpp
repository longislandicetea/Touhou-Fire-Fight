#include "Line.h"
#include <windows.h>
#include <gl/GL.h>
#include "MoogeUtility.h"

//Construct Line object given two Pos.
CLine::CLine(VECTORFA StartPos, VECTORFA EndPos, PRIMITIVEID ObjectID): mObjectID(ObjectID)
{
	memcpy(mSrartPos, StartPos, sizeof(VECTORFA));
	memcpy(mEndPos, EndPos, sizeof(VECTORFA));
	//Initial color element with all 64. (Gray color)
	memset(mLineColor, 64, 4);
}

//Default destructor.
CLine::~CLine()
{
	ZeroMemory(mSrartPos, sizeof(VECTORFA));
	ZeroMemory(mEndPos, sizeof(VECTORFA));
}

//Draw the line using gl command.
void CLine::Draw()
{
	//Set drawing color.
	glColor4ubv(mLineColor);
	//Draw line.
	glVertex3fv(mSrartPos);
	glVertex3fv(mEndPos);
}

//Default constructor.
CLine::CLine()
{
	ZeroMemory(mSrartPos, sizeof(VECTORFA));
	ZeroMemory(mEndPos, sizeof(VECTORFA));
}

//Get ID of this object.
PRIMITIVEID CLine::GetObjectID()
{
	return mObjectID;
}

//Set the line color.(rgba)
void CLine::SetColor(const COLOR4UBS& Color4ubS)
{
	ConvertColor4ubS2A(Color4ubS, mLineColor);
}

void CLine::SetColor(COLOR4UBA Color4ubA)
{
	memcpy(mLineColor, Color4ubA, sizeof(COLOR4UBA));
}