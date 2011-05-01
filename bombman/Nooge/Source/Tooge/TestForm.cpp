#include "TestForm.h"
#include <functional>

CTestForm::CTestForm(): CWinFrame()
{
	AddCallBackEvent(WM_CREATE, bind(&CTestForm::OnCreate, this, _1));
}

//Simple constructor.
CTestForm::CTestForm(string Name, string title)
{
	//[Important]: WM_CREATE and CustomProc must be listened before Load().
	AddCallBackEvent(WM_CREATE, bind(&CTestForm::OnCreate, this, _1));
	AssignCustomProc(bind(&CTestForm::TestProc, this, _1));
	Load(Name, title);
}

//Advance constructor.
CTestForm::CTestForm(string Name, string title, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height)
{
	//[Important]: WM_CREATE and CustomProc must be listened before Load().
	AddCallBackEvent(WM_CREATE, bind(&CTestForm::OnCreate, this, _1));
	AssignCustomProc(bind(&CTestForm::TestProc, this, _1));
	Load(Name, title, Left, Top, Width, Height);
}

CTestForm::~CTestForm()
{
	mText.UnLoad();
	mButtonOk.UnLoad();
	mInputEdit.UnLoad();
	mButtonReadEdit.UnLoad();
	Unload();
}

//listen WM_CREATE
void CTestForm::OnCreate(const WinMsgPackage& MsgPack)
{
	//[Important]: Load all your component here.
	mText.Load(this);
	mText.SetPosition(10, 10);

	mButtonOk.Load(this, "Ok");
	mButtonOk.SetPosition(10, 30);
	mButtonOk.SetOnClick(bind(&CTestForm::OnButtonOKClick, this));

	mButtonKaboom.Load(this, "Kaboom");
	mButtonKaboom.SetPosition(10, 70);
	mButtonKaboom.SetOnClick(bind(&CTestForm::OnButtonKaboomClick, this));

	mButtonReadEdit.Load(this, "TestEdit");
	mButtonReadEdit.SetPosition(10, 110);
	mButtonReadEdit.SetOnClick(bind(&CTestForm::OnButtonReadEditClick, this));

	mInputEdit.Load(this, 10, 150, 100);
	mInputEdit.SetPosition(10, 150);
}

//Custom proc.
void CTestForm::TestProc(const WinMsgPackage& MsgPack)
{

}

//Button click event.
void CTestForm::OnButtonOKClick()
{
	mText.SetText("Ok clicked!");
}

//Button click event.
void CTestForm::OnButtonKaboomClick()
{
	mText.SetText("Kaboom clicked!");
}

//Button click event.
void CTestForm::OnButtonReadEditClick()
{
	mText.SetText(mInputEdit.GetText());
}