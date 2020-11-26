#pragma once
#include <process.h>
#define dfMaxThreadCount 3

enum class LoadType
{
	STATIC_MESH,
	DYNAMIC_MESH,
};

class LoadManager
{
public:
	struct ThreadInfo
	{
		UINT number = 0;
		LoadManager* pLoad = nullptr;
		bool isWorking = false;
		bool shutdownFlag = false;
	};

	struct LoadingElement
	{
		wstring filePath;
		wstring fileName;
		LoadType type;
		void(*Callback)() = nullptr;
	};

private:
	LoadManager();
	~LoadManager();

public:
	static LoadManager* GetInstance();
	static void Destroy();
private:
	void Initialize();
	void Release();
public:
	static bool IsFinish();
	static float GetProgress();
	static wstring GetText();
public:
	static unsigned int __stdcall LodingThread(void* arg);

	// 놀고있는 or 일이 적은 쓰레드 찾기
	static UINT FindUnemployedThread();
	static void LoadStaticMeshAsync(const wstring& filePath, const wstring& fileName, void(*Callback)() = nullptr);
	static void LoadDynamicMeshAsync(const wstring& filePath, const wstring& fileName, void(*Callback)() = nullptr);

private:
	ThreadInfo threadInfo[dfMaxThreadCount] = {};
	HANDLE hThread[dfMaxThreadCount] = {};
	bool isFinish = false;
	float percent = 0.f;
	wstring text;
	queue<LoadingElement> jobQ[dfMaxThreadCount];
	CRITICAL_SECTION csQ[dfMaxThreadCount];

};

