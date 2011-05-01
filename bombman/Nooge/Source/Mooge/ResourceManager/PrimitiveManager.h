#ifndef PrimitiveManagerH
#define PrimitiveManagerH
#include <map>
#include "MoogeType.h"

using namespace std;
using namespace MoogeType;

//Forward declare primitives that manage by this class.
class CLine;
class CMooge;

//Primitive objects manager.
class CPrimitiveManager
{
	//Only CMooge class(main interface of engine) has the power to use me.
	friend CMooge;

	public:
		//===================== [Line Object Methods] =====================
		bool AddLine(VECTORFA StartPos, VECTORFA EndPos);
		bool AddLine(VECTORFS StartPos, VECTORFS EndPos);
		bool AddLine(VECTORFA StartPos, VECTORFA EndPos, CLine*& ReturnPtr);
		bool AddLine(VECTORFS StartPos, VECTORFS EndPos, CLine*& ReturnPtr);
		
		bool AddBoldLine(VECTORFA StartPos, VECTORFA EndPos);
		bool AddBoldLine(VECTORFS StartPos, VECTORFS EndPos);
		bool AddBoldLine(VECTORFA StartPos, VECTORFA EndPos, CLine*& ReturnPtr);
		bool AddBoldLine(VECTORFS StartPos, VECTORFS EndPos, CLine*& ReturnPtr);

		bool RemoveLine(CLine*& ObjectPtr);
		bool RemoveBoldLine(CLine*& ObjectPtr);

		void RemoveAllLine();
		void RemoveAllBoldLine();
		//=================================================================

	private:
		//Default constructor.
		CPrimitiveManager();

		//Default destructor.
		~CPrimitiveManager();

		//Render all primitives.
		void Draw();

	private:
		//Manage Cline objects in these maps.
		map<PRIMITIVEID, CLine*> mLineMap;
		map<PRIMITIVEID, CLine*> mBoldLineMap;

	private:
		//Object id generator.
		unsigned int PRIMITIVEIDSEQ;
};


#endif