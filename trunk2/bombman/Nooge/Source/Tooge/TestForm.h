#ifndef TestFormH
#define TestFormH

#include "WinFrame.h"
#include "Text.h"
#include "Button.h"
#include "Edit.h"

using namespace std;

//A Test form class.
class CTestForm : public CWinFrame
{
	public:
		//Default constructor.
		CTestForm();

		//Simple constructor.
		CTestForm(string Name, string title);

		//Advance constructor.
		CTestForm(string Name, string title, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height);

		//Destructor.
		~CTestForm();

	private:
		//listening WM_CREATE event.
		void OnCreate(const WinMsgPackage& MsgPack);

		//Custom proc.
		void TestProc(const WinMsgPackage& MsgPack);

		//Button click event.
		void OnButtonOKClick();

		//Button click event.
		void OnButtonKaboomClick();

		//Button click event.
		void OnButtonReadEditClick();

	private:
		//Text object member.
		CText mText;

		//Button object member.
		CButton mButtonOk;
		CButton mButtonKaboom;
		CButton mButtonReadEdit;

		//Edit object.
		CEdit mInputEdit;
};

#endif