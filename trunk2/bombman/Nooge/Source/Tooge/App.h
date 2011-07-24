#pragma once

#include<time.h>

#include"MoogeType.h"
#include"Thread.h"
#include "Ref.h"
#include "InputSystem.h"
#include "AudioSystem.h"
#include "Texture.h"

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
	Ref<AudioSystem> AudioSys();
	Stage *CurrentStage();
	void ChangeStage(int next);

	//i don't want this f**king function! but how can i do!
	Ref<Texture> GetFlameTexture();

private:
	App();
	void OnRenderFormCreate(const WinMsgPackage& MsgPack);
	void OnRenderFormDestroy(const WinMsgPackage& MsgPack);
	void OnRenderFormChar(const WinMsgPackage& MsgPack);
	void OnRenderFormTimer(const WinMsgPackage& MsgPack);
	void OnRenderFormKeyDown(const WinMsgPackage& MsgPack);
	void OnRenderFormKeyUp(const WinMsgPackage& MsgPack);
	void OnRenderFormClickButton(const WinMsgPackage& MsgPack);
	//void OnRenderFormMouseMove(const WinMsgPackage& MsgPack);
	void SetupEngine();
	void Execute();

	Ref<Stage> createStage(int stageId);
	
	CRenderForm* mRenderForm;
	CMooge* mMooge;
	CCamera* mMainCamera;
	Ref<InputSystem> mInputSys;
	Ref<AudioSystem> mAudioSys;
	clock_t mLeastTime;
	Ref<Texture> mFlameTexture;
};
