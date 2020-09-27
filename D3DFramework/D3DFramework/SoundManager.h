#pragma once

namespace PKH
{
	enum SoundChannel { BGM, PLAYER, MONSTER, EFFECT, MAXCHANNEL };

	class SoundManager
	{
	public:
		static SoundManager* GetInstance();
		static void Destroy();

	private:
		SoundManager();
		~SoundManager();

	public:
		static void Initialize();

		static void Release();
	public:
		static void PlaySound(TCHAR* pSoundKey, SoundChannel eID);
		static void PlayBGM(TCHAR* pSoundKey);
		static void StopSound(SoundChannel eID);
		static void StopAll();
		static void SetVolume(SoundChannel channel, float per);

	private:
		static void LoadSoundFile();

	private:
		// 사운드 리소스 정보를 갖는 객체 
		map<TCHAR*, FMOD_SOUND*> soundMap;
		// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
		FMOD_CHANNEL* channels[MAXCHANNEL];
		// 사운드 ,채널 객체 및 장치를 관리하는 객체 
		FMOD_SYSTEM* pSystem;

	};


}
