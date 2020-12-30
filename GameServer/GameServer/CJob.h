#pragma once
#include "IJob.h"
class CJob : public IJob
{
public:
	CJob();
	CJob(__int64 sessionID, CPacket* packet, CGameServer* pGameServer);
	virtual ~CJob();
	virtual void Excute();
	virtual void Clear();

private:
	__int64 sessionID = -1;
	CPacket* pPacket = nullptr;
	CGameServer* pGameServer = nullptr;

};

