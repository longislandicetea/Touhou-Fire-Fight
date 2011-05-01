#ifndef C2DTextH
#define C2DTextH

#include <string>
#include "MoogeType.h"

using namespace std;
using namespace MoogeType;

//Forward declaure of friend class.
class CTextManager;
class CConsole;
class CAuxiliary;

//2DText class.
class C2DText
{
	//This is my boss.
	friend CTextManager;
	friend CConsole;
	friend CAuxiliary;
	public:
		//Get ID of this object.
		TEXTID GetObjectID();

		//Set text to this object.
		void SetText(const string& Str);

		//Set color of the text.
		void SetColor(const COLOR4UBS& Color4ubS);
		void SetColor(COLOR4UBA Color4ubA);

		//Set 2D position of the text.
		void SetPosition(unsigned int PosX, unsigned int PosY);

		//Set visible.
		void SetVisible(bool Vis);

	private:
		//Default constructor.
		C2DText();

		//Advance constructor.
		C2DText(string Str, unsigned int PosX, unsigned int PosY, TEXTID ObjectID);

		//Default destructor.
		~C2DText();

		//Draw the text using gl command.
		void Draw(unsigned int FontList);

	private:
		//Object ID.
		TEXTID mObjectID;

		//Current displaying text.
		string mTextStr;			

		//Position of the text object.
		unsigned int mPosX;
		unsigned int mPosY;

		//Text color.
		COLOR4UBA mTextColor;

		//Visible?
		bool mVisible;
};

#endif