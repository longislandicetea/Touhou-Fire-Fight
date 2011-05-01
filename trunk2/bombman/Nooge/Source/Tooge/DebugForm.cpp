#include "DebugForm.h"

//Simple constructor.
CDebugForm::CDebugForm()
{

}

//Simple load.
void CDebugForm::Load(string title)
{
	//Simple way.
	CWinFrame::Load("DebugForm", title, 900, 50, 100, 100);

	mPosXTag.Load(this, "PosX =", 10, 10);
	mPosXValue.Load(this, "0", 55, 10);
	mPosYTag.Load(this, "PosY =", 10, 30);
	mPosYValue.Load(this, "0", 55, 30);

	mOkButton.Load(this, "ok");
	mOkButton.SetPosition(25, 70);
}

//Simple Unload();
void CDebugForm::Unload()
{
	mPosXTag.UnLoad();
	mPosYTag.UnLoad();
	mOkButton.UnLoad();
	CWinFrame::Unload();
}

//Destructor.
CDebugForm::~CDebugForm()
{
	Unload();
}

void CDebugForm::SetPosXValue(const int& IntIn)
{
	mPosXValue.SetText(IntIn);
}

void CDebugForm::SetPosYValue(const int& IntIn)
{
	mPosYValue.SetText(IntIn);
}