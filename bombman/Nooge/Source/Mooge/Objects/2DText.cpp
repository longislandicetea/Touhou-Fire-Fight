#include "2DText.h"
#include "MoogeUtility.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

//Default constructor.
C2DText::C2DText()
{

}

//Advance constructor.
C2DText::C2DText(string Str, unsigned int PosX, unsigned int PosY, TEXTID ObjectID): mTextStr(Str), mPosX(PosX), mPosY(PosY), mObjectID(ObjectID)
{
	//Initial color element with all 128. (Light gray color)
	memset(mTextColor, 128, 4);
}

//Default destructor.
C2DText::~C2DText()
{

}

//Draw the text using gl command.
void C2DText::Draw(unsigned int FontList)
{
	if(mVisible)
	{
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		//[ToDo]: customize res setup from caller.
		glOrtho(0,800,600, 0, -1, 1);

		glColor4ubv(mTextColor);
		glRasterPos2i(mPosX, mPosY);
		glListBase(FontList);
		glCallLists(mTextStr.size(), GL_UNSIGNED_BYTE, mTextStr.c_str());

		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		/*glPopMatrix();
		glMatrixMode( GL_PROJECTION );
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);*/
	}
}

//Get ID of this object.
TEXTID C2DText::GetObjectID()
{
	return mObjectID;
}

//Set text to this object.
void C2DText::SetText(const string& Str)
{
	mTextStr = Str;
}

//Set color of the text
void C2DText::SetColor(const COLOR4UBS& Color4ubS)
{
	ConvertColor4ubS2A(Color4ubS, mTextColor);
}

void C2DText::SetColor(COLOR4UBA Color4ubA)
{
	memcpy(mTextColor, Color4ubA, sizeof(COLOR4UBA));
}

//Set 2D position of the text.
void C2DText::SetPosition(unsigned int PosX, unsigned int PosY)
{
	mPosX = PosX;
	mPosY = PosY;
}

//Set visible.
void C2DText::SetVisible(bool Vis)
{
	mVisible = Vis;
}