#ifndef MoogeH
#define MoogeH

//Forward declare of engine component class.
class CCore;
class CPrimitiveManager;
class CCameraManager;
class CTextManager;
class CConsole;
class CAuxiliary;

//Engine primary interface class.
class CMooge
{
	public:
		//Default constructor.
		CMooge();

		//Default destructor.
		~CMooge();

		//Render.
		void Render();

	public:
		//Component managers here.

		//Core component.
		CCore* Core;

		//Console component.
		CConsole* Console;

		//Primitive component.
		CPrimitiveManager* Primitives;	

		//Camera manager.
		CCameraManager* Cameras;

		//Test manager.
		CTextManager* Text;

		//Build in functionality.
		CAuxiliary* Auiliary;
};

#endif