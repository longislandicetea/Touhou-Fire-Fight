#ifndef AppTwoH
#define AppTwoH
#include <time.h>

#include "MoogeType.h"
#include "Thread.h"

using namespace MoogeType;

class CRenderForm;
class CMooge;
class CCore;
class CCamera;
class C2DText;
struct WinMsgPackage;

enum MoveKey
{
	MoveKey_W = 0,
	MoveKey_A,
	MoveKey_S,
	MoveKey_D
};

static const int MOVEKEYTYPE = 4;

//AppTwo: to test CMooge.
//Todo: camera object / move / rotate.
//Simple coordinate system.
class CAppTwo : public CThread
{
	public:
		CAppTwo();

		~CAppTwo();

	private:
		void OnRenderFormCreate(const WinMsgPackage& MsgPack);
		void OnRenderFormDestroy(const WinMsgPackage& MsgPack);
		void OnRenderFormTimer(const WinMsgPackage& MsgPack);
		void OnRenderFormKeyDown(const WinMsgPackage& MsgPack);
		void OnRenderFormKeyUp(const WinMsgPackage& MsgPack);
		void OnRenderFormLBtnDown(const WinMsgPackage& MsgPack);
		void OnRenderFormChar(const WinMsgPackage& MsgPack);

	private:
		//[NOTE]: This function MUST be called in Execute().
		//Here we setup engine rendering in a seperated thread.
		void SetupEngine();
		//Render thread execution.
		void Execute();

	private:
		CRenderForm* mRenderForm;
		CMooge* mMooge;
		CCamera* mMainCamera;

	private:

		//=============== Keyboard input ================
		//Camera shift process.
		void ProcessCameraShift();
		//Keydown trigger.
		bool mKeyTrigger[MOVEKEYTYPE];
		//Shift position vector.
		float mMoveSpeed[MOVEKEYTYPE];
		//===============================================

		//================= Mouse input =================
		//Mouse capture trigger.
		bool mMouseCaptured;
		void MouseProcess();
		//Rotation setup.(Degree)
		//Rotation base by every pixiel mouse move.
		float mRotBase;
		//Rotation acceleration by every mouse move.
		float mRotAcc;
		//===============================================

		clock_t mLeastTime;
};

#endif