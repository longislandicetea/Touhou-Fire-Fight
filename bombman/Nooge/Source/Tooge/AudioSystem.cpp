#include "AudioSystem.h"
#include "DataManager.h"

AudioSystem::AudioSystem()
{
	mResult = FMOD::System_Create(&mSys);
	mResult = mSys->init(100, FMOD_INIT_NORMAL, 0);

	FMOD::Sound* buf;
	mResult = mSys->createStream((DataManager::GetDataPath("Stream","gameBgm1","resource\\data.ini")).c_str(),FMOD_DEFAULT,0,&buf);
	mSounds["bgm1"] = buf;
	
	mResult = mSys->createStream((DataManager::GetDataPath("Stream","gameBgm2","resource\\data.ini")).c_str(),FMOD_DEFAULT,0,&buf);
	mSounds["bgm2"] = buf;

	mResult = mSys->createStream((DataManager::GetDataPath("Stream","gameBgm3","resource\\data.ini")).c_str(),FMOD_DEFAULT,0,&buf);
	mSounds["bgm3"] = buf;
	
	mResult = mSys->createStream((DataManager::GetDataPath("Stream","menuBgm","resource\\data.ini")).c_str(),FMOD_DEFAULT,0,&buf); 
	mSounds["menubackground"] = buf;

	mResult = mSys->createSound((DataManager::GetDataPath("Effect","enterButton","resource\\data.ini")).c_str(),FMOD_DEFAULT,0,&buf); 
	mSounds["menubutton"] = buf;

	mResult = mSys->createSound((DataManager::GetDataPath("Effect","dropBomb","resource\\data.ini")).c_str(),FMOD_DEFAULT,0,&buf); 
	mSounds["dropbomb"] = buf;
	
	mResult = mSys->createSound((DataManager::GetDataPath("Effect","explode","resource\\data.ini")).c_str(),FMOD_DEFAULT,0,&buf); 
	mSounds["explode"] = buf;

	mResult = mSys->createSound((DataManager::GetDataPath("Effect","eatBonus","resource\\data.ini")).c_str(),FMOD_DEFAULT,0,&buf); 
	mSounds["eatbonus"] = buf;

	mResult = mSys->createSound((DataManager::GetDataPath("Effect","dead","resource\\data.ini")).c_str(),FMOD_DEFAULT,0,&buf); 
	mSounds["dead"] = buf;

	mResult = mSys->createStream((DataManager::GetDataPath("Effect","win","resource\\data.ini")).c_str(),FMOD_DEFAULT,0,&buf); 
	mSounds["win"] = buf;

	mResult = mSys->createStream((DataManager::GetDataPath("Effect","lose","resource\\data.ini")).c_str(),FMOD_DEFAULT,0,&buf); 
	mSounds["lose"] = buf;   

	std::map<std::string, FMOD::Sound*>::iterator it = mSounds.begin();
	for(;it!=mSounds.end();++it)
		it->second->setMode(FMOD_LOOP_OFF);


	FMOD::Channel* channel1;
	FMOD::Channel* channel2;

	mChannels.push_back(channel1);
	mChannels.push_back(channel2);

	mBgmMute = mSndMute = false;
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

void AudioSystem::Resume( int channelId, const std::string& key)
{
	//mResult = mChannels[channelId]->setMode(FMOD_LOOP_NORMAL);
	mResult = mSounds[key]->setMode(FMOD_LOOP_NORMAL);
}

void AudioSystem::Mute( int channelId,bool isMute )
{
	mResult = mChannels[channelId]->setMute(isMute);

	if(channelId == 0)
		mBgmMute = isMute;
	else
		mSndMute = isMute;
}

AudioSystem::~AudioSystem()
{
	mResult = mSys->release();
}
