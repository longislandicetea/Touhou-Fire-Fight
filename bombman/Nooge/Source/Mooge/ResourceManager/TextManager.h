#ifndef TextManagerH
#define TextManagerH
#include <map>
#include "MoogeType.h"

using namespace std;
using namespace MoogeType;

//Forward declare text objects that manage by this class.
class C2DText;
class CMooge;

//Text objects manager.
class CTextManager
{
	//Only CMooge class(main interface of engine) has the power to use me.
	friend CMooge;

	public:
		//===================== [2DText Object Methods] =====================
		bool Add2DText(string Str, unsigned int PosX, unsigned int PosY, C2DText*& ReturnPtr);
		bool Remove2DText(C2DText*& ObjectPtr);
		void RemoveAll2DText();
		//===================================================================

	private:
		//Default constructor.
		CTextManager();

		//Default destructor.
		~CTextManager();

		//Render all Text.
		void Draw(unsigned int FontList);

	private:
		//Manage C2DText objects in these maps.
		map<TEXTID, C2DText*> m2DTextMap;

		//Object id generator.
		unsigned int TEXTIDSEQ;
};

#endif