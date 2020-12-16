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

void Debug::Print(const char* _text, ...)
{
	va_list ap;
	char buf[dfMAX_BUF_SIZE] = { 0, };
	va_start(ap, _text);
	vsprintf_s(buf, _text, ap);
	va_end(ap);

	fprintf(stdout, "%s", buf);

}
