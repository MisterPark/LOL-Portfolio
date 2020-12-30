#include "stdafx.h"
#include "CGameServer.h"
#include "CJobOnRecv.h"

CJobOnRecv::CJobOnRecv(__int64 sessionID, CPacket* packet, CGameServer* pGameServer)
{
	this->sessionID = sessionID;
	this->pPacket = packet;
	this->pGameServer = pGameServer;
}

CJobOnRecv::~CJobOnRecv()
{
}

void CJobOnRecv::Excute()
{
	pGameServer->PacketProc(sessionID, pPacket);
}

void CJobOnRecv::Clear()
{
	PacketPool::Free(pPacket);
	this->sessionID = 0;
	this->pPacket = nullptr;
}
