#pragma once

namespace PKH
{
	class TimeManager
	{
	private:
		TimeManager();
		~TimeManager();

	public:
		static TimeManager* GetInstance();
		static void Destroy();

		static void Initialize();
		static void Release();

		static bool SkipFrame();

		static float GetFPS();
		static void SetFPS(float _fps);

		static float DeltaTime();

		// 디버그용
		static void RenderFPS();

	private:
		LARGE_INTEGER frequency;
		float fps = 50.f;

		bool isUsedQueryPerformance = false;
		__int64 oldTime = 0;
		__int64 elapseSum = 0;
		float deltaTime = 0.f;
		__int64 frameCount = 0;
		float targetFrame = 0.f;
		float timeStack = 0; // 프레임당 초과 미만 시간 누적

	};
}

