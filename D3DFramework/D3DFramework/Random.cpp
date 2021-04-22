#include "stdafx.h"
#include "Random.h"

void Engine::Random::InitState()
{
    srand(0);
}

void Engine::Random::InitState(int seed)
{
    srand(seed);
}

int Engine::Random::Value(int numOfCases)
{
    return (rand() % numOfCases);
}

int Engine::Random::Range(int min, int max)
{
    int range = max - min + 1;
    int random = rand() % range + min;
    return random;
}

float Engine::Random::Range(float min, float max)
{
    int iMin = (int)(min * 100);
    int iMax = (int)(max * 100);
    int range = iMax - iMin + 1;
    int random = rand() % range;
    float fRandom = random / 100.f + min;
    return fRandom;
}
