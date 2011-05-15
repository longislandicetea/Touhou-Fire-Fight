#ifndef MoogeH
#define MoogeH

#include "Ref.h"

//Forward declare of engine component class.
class CCore;
class CPrimitiveManager;
class CCameraManager;
class CTextManager;
class CConsole;
class CAuxiliary;
class Stage;

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

		//Update
		void Update(float dt);

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
			
		Ref<Stage>	CurrentStage;
};

#endif