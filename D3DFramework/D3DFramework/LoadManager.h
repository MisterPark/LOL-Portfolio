#pragma once
#include <process.h>

class LoadManager
{
private:
	LoadManager();
	~LoadManager();

public:
	static LoadManager* GetInstance();
	static void Destroy();

	static void Initialize();
	static void Release();
public:
	static bool IsFinish();
	static float GetProgress();
	static wstring GetText();
public:
	static unsigned int __stdcall LodingThread(void* arg);

	static void LoadResources();


	// 로드 할거 추가하셈
	void LoadAll();

	void LoadETCSprite();
	void LoadMonsterSprite();
	void LoadPlayerSprite();
	void LoadNPCSprite();

private:
	HANDLE hThread = INVALID_HANDLE_VALUE;
	bool isFinish = false;
	float percent = 0.f;
	wstring text;
	RenderManager* pRenderMgr;

};

