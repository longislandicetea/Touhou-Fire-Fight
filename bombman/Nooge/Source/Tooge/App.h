#pragma once

#include<time.h>

#include"MoogeType.h"
#include"Thread.h"

using namespace MoogeType;

class CRenderForm;
class CMooge;
class CCore;
class CCamera;
class C2DText;
struct WinMsgPackage;

class App : public CThread
{
public:
	App(void);
	~App(void);

private:
	void OnRenderFormCreate(const WinMsgPackage& MsgPack);
	void OnRenderFormDestroy(const WinMsgPackage& MsgPack);
	void OnRenderFormChar(const WinMsgPackage& MsgPack);
	void OnRenderFormTimer(const WinMsgPackage& MsgPack);

	void SetupEngine();
	void Execute();

	CRenderForm* mRenderForm;
	CMooge* mMooge;
	CCamera* mMainCamera;

	clock_t mLeastTime;

};

