#include "stdafx.h"
#include "SoundManager.h"
#include "fmod.h"
#include <io.h>

using namespace PKH;

PKH::SoundManager* pSoundManager = nullptr;

SoundManager* PKH::SoundManager::GetInstance()
{
	if (pSoundManager == nullptr)
	{
		pSoundManager = new SoundManager;
	}
	return pSoundManager;
}

void PKH::SoundManager::Destroy()
{
	if (pSoundManager)
	{
		delete pSoundManager;
		pSoundManager = nullptr;
	}
}

PKH::SoundManager::SoundManager()
{
	pSystem = nullptr; 
}


PKH::SoundManager::~SoundManager()
{
	Release();
}

void PKH::SoundManager::Initialize()
{
	FMOD_System_Create(&pSoundManager->pSystem);
	
	// 1. 시스템 포인터, 2. 사용할 가상채널 수 , 초기화 방식) 
	FMOD_System_Init(pSoundManager->pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile(); 
}
void PKH::SoundManager::Release()
{
	for (auto& Mypair : pSoundManager->soundMap)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	pSoundManager->soundMap.clear();
	FMOD_System_Release(pSoundManager->pSystem);
	FMOD_System_Close(pSoundManager->pSystem);
}




void PKH::SoundManager::PlaySound(TCHAR * pSoundKey, SoundChannel eID)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter; 

	iter = find_if(pSoundManager->soundMap.begin(), pSoundManager->soundMap.end(), [&](auto& iter)
	{
		return !lstrcmp(pSoundKey, iter.first);
	});

	if (iter == pSoundManager->soundMap.end())
		return;

	FMOD_BOOL bPlay = FALSE; 
	if (FMOD_Channel_IsPlaying(pSoundManager->channels[eID], &bPlay))
	{
		FMOD_System_PlaySound(pSoundManager->pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &pSoundManager->channels[eID]);
	}
	FMOD_System_Update(pSoundManager->pSystem);
}

void PKH::SoundManager::PlayBGM(TCHAR * pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(pSoundManager->soundMap.begin(), pSoundManager->soundMap.end(), [&](auto& iter)
	{
		return !lstrcmp(pSoundKey, iter.first);
	});

	if (iter == pSoundManager->soundMap.end())
		return;

	FMOD_System_PlaySound(pSoundManager->pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &pSoundManager->channels[BGM]);
	FMOD_Channel_SetMode(pSoundManager->channels[BGM], FMOD_LOOP_NORMAL);
	FMOD_System_Update(pSoundManager->pSystem);
}

void PKH::SoundManager::StopSound(SoundChannel eID)
{
	FMOD_Channel_Stop(pSoundManager->channels[eID]);
}

void PKH::SoundManager::StopAll()
{
	for (int i = 0 ; i < MAXCHANNEL ; ++i)
		FMOD_Channel_Stop(pSoundManager->channels[i]);
}

void PKH::SoundManager::SetVolume(SoundChannel channel, float per)
{
	FMOD_Channel_SetVolume(pSoundManager->channels[channel], per);
}


void PKH::SoundManager::LoadSoundFile()
{
	_finddata_t fd; 

	long handle = _findfirst("Sound/*.*", &fd);

	if (handle == 0)
		return; 
	if (handle == -1)
		return;

	int iResult = 0; 

	char szCurPath[128] = "Sound/";
	char szFullPath[128] = ""; 

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath); 
		strcat_s(szFullPath, fd.name);
		FMOD_SOUND* pSound = nullptr; 

		FMOD_RESULT eRes = FMOD_System_CreateSound(pSoundManager->pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1; 

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);
			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			pSoundManager->soundMap.emplace(pSoundKey, pSound);
		}
		iResult = _findnext(handle, &fd);
	}
	FMOD_System_Update(pSoundManager->pSystem);
	_findclose(handle);
}
