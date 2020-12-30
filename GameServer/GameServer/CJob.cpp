#include "stdafx.h"
#include "CJob.h"

CJob::CJob()
{
}

CJob::CJob(__int64 sessionID, CPacket* packet, CGameServer* pGameServer)
{
	this->sessionID = sessionID;
	this->pPacket = packet;
	this->pGameServer = pGameServer;
}

CJob::~CJob()
{
}

void CJob::Excute()
{
}

void CJob::Clear()
{
}
