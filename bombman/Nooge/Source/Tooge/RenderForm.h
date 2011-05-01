#ifndef RenderFormH
#define RenderFormH

#include "WinFrame.h"

using namespace std;

//A Render form class.
//Just an empty form so far. For render use.
class CRenderForm : public CWinFrame
{
	public:
		//Simple constructor.
		CRenderForm();

		//Advance load.
		void Load(string title, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height);

		//Simple unload.
		void Unload();

		//Destructor.
		~CRenderForm();
};


#endif