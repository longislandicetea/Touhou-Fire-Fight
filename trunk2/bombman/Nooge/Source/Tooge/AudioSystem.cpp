#include "AudioSystem.h"

AudioSystem::AudioSystem()
{
	mResult = FMOD::System_Create(&mSys);
	mResult = mSys->init(100, FMOD_INIT_NORMAL, 0);

	FMOD::Sound* buf;
	mResult = mSys->createStream("resource\\youngforyou.mp3",FMOD_DEFAULT,0,&buf);
	mSounds["background"] = buf;

	mResult = mSys->createStream("resource\\730880.mp3",FMOD_DEFAULT,0,&buf); 
	mSounds["menubackground"] = buf;

	mResult = mSys->createStream("resource\\cursor.mp3",FMOD_DEFAULT,0,&buf); 
	mSounds["menubutton"] = buf;

	FMOD::Channel* channel1;
	FMOD::Channel* channel2;

	mChannels.push_back(channel1);
	mChannels.push_back(channel2);
}

void AudioSystem::PlayStream( int channelId, const std::string& key )
{
	mResult = mSys->playSound(FMOD_CHANNEL_FREE, mSounds[key], false, &mChannels[channelId]);
}

void AudioSystem::PlayEffectSound( int channelId, const std::string& key )
{
	mResult = mSys->playSound(FMOD_CHANNEL_FREE, mSounds[key], false, &mChannels[channelId]);
}

void AudioSystem::Pause(int channelId)
{
	mResult = mChannels[channelId]->setPaused(false);	
}

void AudioSystem::Update()
{
	mResult = mSys->update();
}

void AudioSystem::Stop( int channelId )
{
	mResult = mChannels[channelId]->stop();	
}
