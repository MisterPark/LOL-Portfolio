#include "stdafx.h"
#include "Time.h"

using namespace Engine;

Engine::Time* pTime = nullptr;

Engine::Time::Time()
{
}

Engine::Time::~Time()
{
}

Engine::Time* Time::GetInstance()
{
    if (pTime == nullptr)
    {
        pTime = new Time;
        Initialize();
    }
    return pTime;
}

void Engine::Time::Destroy()
{
    if (pTime)
    {
        delete pTime;
        pTime = nullptr;
    }
}

void Engine::Time::Initialize()
{
    if (QueryPerformanceFrequency(&pTime->frequency))
    {
        pTime->isUsedQueryPerformance = true;
        pTime->cpuTick = pTime->frequency.QuadPart / 1000;
    }
}

void Engine::Time::Release()
{
}

bool Engine::Time::SkipFrame()
{
    LARGE_INTEGER time;
    __int64 curTime;
    __int64 elapsed; // 1프레임 경과시간(ms)

    QueryPerformanceCounter(&time);
    curTime = time.QuadPart;
    
    if (pTime->oldTime == 0)
    {
        pTime->oldTime = curTime;
        return false;
    }

    // 프레임당 걸린 시간 (마이크로세컨) -> 밀리세컨
    elapsed = (curTime - pTime->oldTime) / pTime->cpuTick;

    pTime->elapseSum += elapsed;
    // 올드타임 갱신
    pTime->oldTime = curTime;
    // 델타타임 갱신 (초단위)
    pTime->deltaTime = float(elapsed) / 1000;
    // 치트
    if (Input::GetKeyDown(VK_F6))
    {
        pTime->deltaTime *= 2.f;
    }
    else if (Input::GetKeyDown(VK_F7))
    {
        pTime->deltaTime *= 3.f;
    }
    //프레임 카운트
    pTime->frameCount++;

    if (pTime->elapseSum >= 1000) // 1초 경과시
    {
        WCHAR str[64] = {};
        wsprintfW(str, L"FPS : %d / Render : %d",pTime->frameCount, pTime->renderCount);
        SetWindowTextW(g_hwnd, str);
        //UpdateWindow(g_hwnd);

        pTime->fps = pTime->frameCount;
        pTime->frameCount = 0;
        pTime->elapseSum = 0;
        pTime->renderCount = 0;
    }
    
    // 프레임당 초과/미만 시간 누적
    //pTime->timeStack += (int)(elapsed - pTime->targetFrame);

    //if (pTime->timeStack >= pTime->targetFrame) // 느릴때
    //{
    //    pTime->timeStack -= pTime->targetFrame;
    //    return true;
    //}
    //else // 빠를때
    //{
    //    //Sleep(abs(pTime->timeStack));
    //}

    pTime->renderCount++;
    return false;
}

int Engine::Time::GetFPS()
{
    return pTime->fps;
}

void Engine::Time::SetFPS(int _fps)
{
    pTime->fps = _fps;
    pTime->targetFrame = (int)(1000.f / _fps);
}

float Engine::Time::DeltaTime()
{
    return pTime->deltaTime;
}

void Engine::Time::RenderFPS()
{
}
