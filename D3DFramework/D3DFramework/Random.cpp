#include "stdafx.h"
#include "Random.h"

void PKH::Random::InitState()
{
    srand(GetTickCount());
}

void PKH::Random::InitState(int seed)
{
    srand(seed);
}

int PKH::Random::Value(int numOfCases)
{
    return (rand() % numOfCases);
}

int PKH::Random::Range(int min, int max)
{
    int range = max - min + 1;
    int random = rand() % range + min;
    return random;
}

float PKH::Random::Range(float min, float max)
{
    int iMin = (int)(min * 100);
    int iMax = (int)(max * 100);
    int range = iMax - iMin + 1;
    int random = rand() % range;
    float fRandom = random / 100.f + min;
    return fRandom;
}
