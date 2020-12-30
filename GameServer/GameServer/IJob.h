#pragma once
#include "CPacket.h"

class CGameServer;

class IJob
{
public:
	IJob();
	virtual ~IJob();
	virtual void Excute() = 0;
	virtual void Clear() = 0;
};

