#include "RenderForm.h"

//Simple constructor.
CRenderForm::CRenderForm()
{

}

//Advance load.
void CRenderForm::Load(string title, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height)
{
	//Simple way.
	CWinFrame::Load("RenderForm", title, Left, Top, Width, Height);
}

//Simple unload.
void CRenderForm::Unload()
{
	CWinFrame::Unload();
}

//Destructor.
CRenderForm::~CRenderForm()
{
	Unload();
}