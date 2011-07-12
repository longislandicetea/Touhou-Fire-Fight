#pragma once

#include<time.h>

#include"MoogeType.h"
#include"Thread.h"
#include "Ref.h"
#include "InputSystem.h"

using namespace MoogeType;

class CRenderForm;
class CMooge;
class CCore;
class CCamera;
class C2DText;
struct WinMsgPackage;
class Stage;

class App : public CThread
{
public:
	static App& Inst();
	~App();
	Ref<InputSystem> InputSys();
	Stage *CurrentStage();
	void ChangeStage(Ref<Stage> next);

private:
	App();
	void OnRenderFormCreate(const WinMsgPackage& MsgPack);
	void OnRenderFormDestroy(const WinMsgPackage& MsgPack);
	void OnRenderFormChar(const WinMsgPackage& MsgPack);
	void OnRenderFormTimer(const WinMsgPackage& MsgPack);
	void OnRenderFormKeyDown(const WinMsgPackage& MsgPack);
	void OnRenderFormKeyUp(const WinMsgPackage& MsgPack);
	void OnRenderFormClickButton(const WinMsgPackage& MsgPack);

	void SetupEngine();
	void Execute();

	CRenderForm* mRenderForm;
	CMooge* mMooge;
	CCamera* mMainCamera;
	Ref<InputSystem> mInputSys;

	clock_t mLeastTime;

};
