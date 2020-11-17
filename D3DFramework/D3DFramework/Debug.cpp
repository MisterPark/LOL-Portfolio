#include "stdafx.h"
#include "Debug.h"

Debug* pDebug = nullptr;

Debug::Debug()
{
}

Debug::~Debug()
{
}

Debug * Debug::GetInstance()
{
	if (pDebug == nullptr)
	{
		pDebug = new Debug();
	}
	return pDebug;
}

void Debug::Destroy()
{
	if (pDebug)
	{
		delete pDebug;
		pDebug = nullptr;
	}

}

void Debug::Initialize()
{
}

void Debug::Release()
{
}
