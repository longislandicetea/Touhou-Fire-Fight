#ifndef LineH
#define LineH

#include "MoogeType.h"

using namespace MoogeType;

//Forward declaure of friend class.
class CPrimitiveManager;
class CAuxiliary;

class CLine
{
	friend CPrimitiveManager;
	friend CAuxiliary;
	public:
		//Get ID of this object.
		PRIMITIVEID GetObjectID();

		//Set the line color.(rgba)
		void SetColor(const COLOR4UBS& Color4ubS);
		void SetColor(COLOR4UBA Color4ubA);

	private:
		//Default constructor.
		CLine();

		//Construct Line object given two Pos and one unique primitive ID.
		CLine(VECTORFA StartPos, VECTORFA EndPos, PRIMITIVEID ObjectID);

		//Default destructor.
		~CLine();	

		//Draw the line using gl command.
		void Draw();

	private:
		//Object ID.
		PRIMITIVEID mObjectID;

		//Two vertexs(vector form) represent the line.
		VECTORFA mSrartPos;
		VECTORFA mEndPos;
		//Line color.
		COLOR4UBA mLineColor;
};



#endif