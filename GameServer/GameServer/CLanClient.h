#pragma once
#include "CNetwork.h"

#define dfLAN_WORKER_COUNT 2
#define dfLAN_THREAD_COUNT (dfLAN_WORKER_COUNT)
#define dfLAN_RUNNING_COUNT 2

class CLanClient
{
public:
	CLanClient(const char* ip, WORD port);
	virtual ~CLanClient();

	bool Connect();
	void Disconnect();

	virtual void OnEnter() = 0;
	virtual void OnLeave() = 0;
	virtual void OnRecv(CPacket* packet) = 0;
	virtual void OnSend() = 0;
	virtual void OnError() = 0;

	static unsigned WINAPI WorkerThread(LPVOID arg);

	void RecvProc(Session* pSession);
	int PostSend(Session* pSession);
	int PostRecv(Session* pSession);

	bool SendPacket(CPacket* packet);

	void DeleteSession(Session* pSession);
	


private:
	HANDLE hIOCP = INVALID_HANDLE_VALUE;
	HANDLE hThread[dfLAN_THREAD_COUNT] = { INVALID_HANDLE_VALUE, };
	unsigned int threadID[dfLAN_THREAD_COUNT] = { 0, };
	char ip[20];
	WORD port;

	Session session;
	bool isConnected = false;

};

