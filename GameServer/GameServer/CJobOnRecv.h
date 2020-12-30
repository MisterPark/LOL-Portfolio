#pragma once
#include "IJob.h"

class CJobOnRecv : public IJob
{
public:
	CJobOnRecv(__int64 sessionID, CPacket* packet, CGameServer* pGameServer);
	virtual ~CJobOnRecv();
	virtual void Excute();
	virtual void Clear();

private:
	__int64 sessionID;
	CPacket* pPacket;
	CGameServer* pGameServer;
};

