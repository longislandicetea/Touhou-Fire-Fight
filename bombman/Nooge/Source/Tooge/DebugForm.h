#ifndef DebugFormH
#define DebugFormH

#include "WinFrame.h"
#include "Button.h"
#include "Text.h"

using namespace std;

//A debug form class.
//Provide an simple interface to operate the application.
class CDebugForm : public CWinFrame
{
	public:
		//Simple constructor.
		CDebugForm();

		//Simple load.
		void Load(string title);

		//Simple Unload();
		void Unload();

		void SetPosXValue(const int& IntIn);

		void SetPosYValue(const int& IntIn);

		//Destructor.
		~CDebugForm();
	private:
		//Ok button
		CButton mOkButton;

		//AppOne debug Text
		CText mPosXTag;
		CText mPosXValue;
		CText mPosYTag;
		CText mPosYValue;

};







#endif