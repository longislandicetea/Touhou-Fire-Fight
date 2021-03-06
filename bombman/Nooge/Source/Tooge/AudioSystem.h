#pragma once

#include "fmod/fmod.h"
#include "fmod/fmod.hpp"

#include <string>
#include <vector>
#include <map>

class AudioSystem
{
public:
	AudioSystem();
	void PlayStream(int channelId, const std::string& key);
	void PlayEffectSound(int channelId, const std::string& key);
	void Pause(int channelId);
	void Stop(int channelId);
	void Resume(int channelId,const std::string& key);
	void Mute(int channelId,bool isMute);
	bool IsBgmMute() {return mBgmMute;}
	bool  IsSndMute() {return mSndMute;}

	void Update();
	~AudioSystem();
private:
	FMOD::System* mSys;
	std::map<std::string, FMOD::Sound*> mSounds;
	std::vector<FMOD::Channel*> mChannels;
	FMOD_RESULT mResult;

	bool mBgmMute,mSndMute;
};