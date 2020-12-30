#include "stdafx.h"
#include "CLanClient.h"

CLanClient::CLanClient(const char* ip, WORD port)
{
	memcpy(this->ip, ip, 20);
	this->port = port;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("[CLanClient] WSAStartup 실패\n");
		return;
	}

	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, dfLAN_RUNNING_COUNT);
	if (hIOCP == NULL)
	{
		printf("[Error] LanClient : IOCP Creation Failed\n");
		return;
	}

	for (int i = 0; i < dfLAN_THREAD_COUNT; i++)
	{
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, WorkerThread, this, 0, &threadID[i]);
	}

}

CLanClient::~CLanClient()
{
	CloseHandle(hIOCP);
	for (int i = 0; i < dfLAN_THREAD_COUNT; i++)
	{
		CloseHandle(hThread[i]);
	}
	WSACleanup();
}

bool CLanClient::Connect()
{
	if (isConnected) return false;

	int retval;
	SOCKADDR_IN sockaddr;
	ZeroMemory(&sockaddr, sizeof(SOCKADDR_IN));
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &sockaddr.sin_addr);

	retval = connect(sock, (SOCKADDR*)(&sockaddr), sizeof(sockaddr));
	if (retval == SOCKET_ERROR)
	{
		return false;
	}

	session.sock = sock;
	session.sockaddr = sockaddr;
	session.isUsed = true;


	CreateIoCompletionPort((HANDLE)session.sock, hIOCP, (ULONG_PTR)&session, 0);

	OnEnter();
	PostRecv(&session);

	isConnected = true;

	return true;
}

void CLanClient::Disconnect()
{
	session.isUsed = false;
	shutdown(session.sock, SD_BOTH);
	isConnected = false;
}

unsigned __stdcall CLanClient::WorkerThread(LPVOID arg)
{
	printf("LAN WorkerThread Start\n");

	CLanClient* pNet = (CLanClient*)arg;
	DWORD transferred;
	Session* pSession;
	OVERLAPPED* pOverlapped;

	for (;;)
	{
		transferred = 0;
		pSession = nullptr;
		pOverlapped = nullptr;

		int ret = GetQueuedCompletionStatus(pNet->hIOCP, &transferred, (PULONG_PTR)&pSession, &pOverlapped, INFINITE);

		if (transferred == 0 && pSession == nullptr && pOverlapped == nullptr) { break; }
		if (pOverlapped == nullptr) { continue; }
		if (pSession == nullptr) { continue; }

		if (transferred == 0)
		{
			pNet->Disconnect();
		}
		else if (pOverlapped == &pSession->recvOL)
		{
			pSession->recvQ.MoveRear(transferred);
			pNet->RecvProc(pSession);

			pNet->PostRecv(pSession);
		}
		else if (pOverlapped == &pSession->sendOL)
		{
			pSession->sendQ.MoveFront(pSession->sendBytes);
			if (pSession->sendBytes != transferred)
			{
				printf("sendBytes : %d / trans : %d\n", pSession->sendBytes, transferred);
			}
			InterlockedExchange(&pSession->sendFlag, false);
			if (pSession->sendQ.GetUseSize() > 0)
			{
				pNet->PostSend(pSession);
			}

		}


		if (InterlockedDecrement((long*)&pSession->IOCount) == 0)
		{
			SESSION_ID sessionID = pSession->sessionID;
			pNet->DeleteSession(pSession);

			pNet->OnLeave();
		}

	}
	printf("LAN WorkerThread End\n");
	return 0;
}

void CLanClient::RecvProc(Session* pSession)
{
	CPacket pack;
	WORD len;

	while (pSession->recvQ.GetUseSize() > 0)
	{
		pack.Clear();
		pSession->recvQ.Peek((char*)&len, sizeof(len));
		if (pSession->recvQ.GetUseSize() < len + sizeof(len)) break;

		pSession->recvQ.MoveFront(sizeof(len));
		pSession->recvQ.Dequeue(pack.GetBufferPtr(), len);
		pack.MoveWritePos(len);
		OnRecv(&pack);
	}
}

int CLanClient::PostSend(Session* pSession)
{
	WSABUF wsabuf[2];
	DWORD ret;
	int bufCount = 1;
	int useSize;
	int deqSize;
	if (pSession == nullptr) return -1;

	if (InterlockedExchange(&pSession->sendFlag, true))
	{
		return 0;
	}

	pSession->sendQ.GetUseDeqSize(&useSize, &deqSize);
	if (useSize <= 0)
	{
		InterlockedExchange(&pSession->sendFlag, false);
		return 1;
	}

	wsabuf[0].buf = pSession->sendQ.GetFrontBufferPtr();
	wsabuf[0].len = deqSize;

	if (useSize > deqSize)
	{
		bufCount = 2;
		wsabuf[1].buf = pSession->sendQ.GetBufferPtr();
		wsabuf[1].len = useSize - deqSize;
	}

	InterlockedIncrement((long*)&pSession->IOCount);
	memset(&pSession->sendOL, 0, sizeof(pSession->sendOL));
	pSession->sendBytes = useSize;


	ret = WSASend(pSession->sock, wsabuf, bufCount, NULL, 0, &pSession->sendOL, NULL);
	if (ret == SOCKET_ERROR)
	{
		int errCode = WSAGetLastError();
		if (errCode != WSA_IO_PENDING)
		{
			if (InterlockedDecrement((long*)&pSession->IOCount) == 0)
			{
				DeleteSession(pSession);
			}
			else
			{
				Disconnect();
			}
		}
	}

	return 0;
}

int CLanClient::PostRecv(Session* pSession)
{
	WSABUF wsabuf[2];
	DWORD ret;
	DWORD recvSize = 0;
	DWORD flag = 0;
	int errCode = 0;
	int bufCount = 1;

	memset(&pSession->recvOL, 0, sizeof(pSession->recvOL));
	int enqSize = 0;
	int freeSize = 0;
	pSession->recvQ.GetFreeEnqSize(&freeSize, &enqSize);
	wsabuf[0].buf = pSession->recvQ.GetRearBufferPtr();
	wsabuf[0].len = enqSize;

	if (freeSize > enqSize)
	{
		bufCount = 2;
		wsabuf[1].buf = pSession->recvQ.GetBufferPtr();
		wsabuf[1].len = freeSize - enqSize;
	}


	InterlockedIncrement((long*)&pSession->IOCount);

	ret = WSARecv(pSession->sock, wsabuf, bufCount, &recvSize, &flag, &pSession->recvOL, NULL);
	if (ret == SOCKET_ERROR)
	{
		int errCode = WSAGetLastError();
		if (errCode != WSA_IO_PENDING)
		{
			if (InterlockedDecrement((long*)&pSession->IOCount) == 0)
			{
				DeleteSession(pSession);
			}
			else
			{
				Disconnect();
			}
		}
	}

	return recvSize;
}

bool CLanClient::SendPacket(CPacket* packet)
{
	if (!session.isUsed)
	{
		//printf("[Error]SendPacket() : Session not found\n");
		return false;
	}

	// 헤더 세팅
	WORD header = packet->GetUseSize();
	packet->SetHeader(header);
	// 센드큐 인큐
	session.sendQ.Enqueue(packet->GetBufferPtr(), packet->GetUseSize());

	PostSend(&session);

	return true;
}

void CLanClient::DeleteSession(Session* pSession)
{
	pSession->isUsed = false;
}
