#include "stdafx.h"
#include "CNetwork.h"
#include "CGameServer.h"

CNetwork::CNetwork()
{
	InitializeNetwork();
}

CNetwork::~CNetwork()
{
	ReleaseNetwork();
}

void CNetwork::Shutdown()
{
	ReleaseNetwork();
}

//================================================================
// 초기화 관련
//================================================================
bool CNetwork::InitializeNetwork()
{
	printf("Initialize Server...\n");
	timeBeginPeriod(1);

	WSADATA wsa;
	SOCKADDR_IN serveraddr;
	int ret;
	// WSA 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return false;
	}
	// IOCP 핸들 생성
	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (hIOCP == NULL) { return false; }
	// 리슨 소켓 생성
	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET) { return false; }
	// 어드레스 세팅
	ZeroMemory(&serveraddr, sizeof(SOCKADDR_IN));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(dfSERVER_PORT);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	// 바인드
	ret = bind(listenSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	// 리슨
	ret = listen(listenSock, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		return false;
	}

	// 패킷풀
	packPool = PacketPool::GetInstance();

	// 쓰레드 생성
	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, AcceptThread, this, 1, &ID[0]);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, SendThread, this, 1, &ID[1]);
	for (int i = (dfMAX_THREAD - dfMAX_WORKER); i < dfMAX_THREAD; i++)
	{
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, WorkerThread, this, 1, &ID[i]);
	}
	

	printf("Complete Initialize\n");
	return true;
}

void CNetwork::ReleaseNetwork()
{
	shutdownFlag = true;

	for (int i = 0; i < dfMAX_THREAD; i++)
	{
		if (hThread[i] == INVALID_HANDLE_VALUE) continue;
		CloseHandle(hThread[i]);
		hThread[i] = INVALID_HANDLE_VALUE;
	}
	CloseHandle(hIOCP);
	hIOCP = INVALID_HANDLE_VALUE;
	timeEndPeriod(1);
	WSACleanup();
}

//================================================================
// 워커 쓰레드
//================================================================
unsigned __stdcall CNetwork::WorkerThread(void* arg)
{
	printf("WorkerThread Start\n");

	CNetwork* pNet = (CGameServer*)arg;
	DWORD transferred;
	Session* pSession;
	OVERLAPPED* pOverlapped;

	for (;!pNet->shutdownFlag;)
	{
		pNet->threadLoopCount++;
		transferred = 0;
		pSession = nullptr;
		pOverlapped = nullptr;

		int ret = GetQueuedCompletionStatus(pNet->hIOCP, &transferred, (PULONG_PTR)&pSession, &pOverlapped, INFINITE);

		if (transferred == 0 && pSession == nullptr && pOverlapped == nullptr) { break; }
		if (pOverlapped == nullptr) { continue; }
		if (pSession == nullptr) { continue; }

		if (transferred == 0)
		{
			pNet->Disconnect(pSession);
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
			pNet->sessionList.DeleteSession(pSession);

			pNet->OnLeave(sessionID);
		}

	}
	printf("WorkerThread End\n");
	return 0;
}

//================================================================
// 액셉트 쓰레드
//================================================================
unsigned __stdcall CNetwork::AcceptThread(void* arg)
{
	CNetwork* pNet = (CGameServer*)arg;

	printf("AcceptThread Start\n");

	SOCKET sock;
	DWORD size;
	int addrlen;

	for (;!pNet->shutdownFlag;)
	{
		SOCKADDR_IN sockaddr;
		char ipbuf[32] = { 0, };
		addrlen = sizeof(sockaddr);
		size = 0;

		sock = accept(pNet->listenSock, (SOCKADDR*)&sockaddr, &addrlen);
		if (sock == INVALID_SOCKET)
		{
			pNet->connectFail++;
			printf("accept err\n");
			break;
		}

		Session* pSession = pNet->sessionList.CreateSession(sock, sockaddr);
		if (pSession == nullptr)
		{
			printf("[Network] Accept : 서버 수용 가능 인원 초과\n");
			continue;
		}

		CreateIoCompletionPort((HANDLE)sock, pNet->hIOCP, (ULONG_PTR)pSession, 0);

		pNet->connectCount++;
		pNet->connectTotal++;
		//inet_ntop(AF_INET, &sockaddr.sin_addr, ipbuf, 32);
		//printf("[AcceptThread] Accept : %s:%d\n", ipbuf, ntohs(sockaddr.sin_port));
		pNet->OnJoin(pSession->sessionID, pSession->sockaddr);
		pNet->PostRecv(pSession);
	}

	printf("AcceptThread End\n");
	return 0;
}

unsigned __stdcall CNetwork::SendThread(void* arg)
{
	CNetwork* pNet = (CNetwork*)arg;
	printf("SendThread Start\n");
	SessionList sessionList = pNet->sessionList;

	for (;!pNet->shutdownFlag;)
	{
		for (int i = 0; i < dfMAX_SESSION_SIZE; i++)
		{
			pNet->PostSend(sessionList[i]);
		}
	}

	printf("SendThread End\n");
	return 0;
}

//================================================================
// 네트워크 관련
//================================================================
int CNetwork::PostSend(Session* pSession)
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
				sessionList.DeleteSession(pSession);
			}
			else
			{
				//shutdown(pSession->sock, SD_BOTH);
			}
		}
	}

	return 0;
}

int CNetwork::PostRecv(Session* pSession)
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
				sessionList.DeleteSession(pSession);
			}
			else
			{
				//shutdown(pSession->sock, SD_BOTH);
			}
		}
	}

	return recvSize;
}

void CNetwork::RecvProc(Session* pSession)
{
	CPacket pack;
	NetHeader header;
	int ret = 0;
	int size = 0;

	for (;;)
	{
		pack.Clear();
		size = pSession->recvQ.GetUseSize();
		if (size < sizeof(NetHeader)) { break; }
		pSession->recvQ.Peek((char*)&header, sizeof(NetHeader));
		if (size < sizeof(NetHeader) + header.len) { break; }
		pSession->recvQ.MoveFront(sizeof(NetHeader));

		pSession->recvQ.Dequeue(pack.GetBufferPtr(), header.len);
		pack.MoveWritePos(header.len);
		if (!pack.Decryption(header))
		{
			printf("[Warning] Decyption Failed\n");
			Disconnect(pSession);
			break;
		}
		recvTPS++;
		OnRecv(pSession->sessionID, &pack);
		
		
	}
}

int CNetwork::SendUnicast(SESSION_ID sessionID, CPacket* pPacket)
{
	Session* session = sessionList.FindSession(sessionID);
	if (session == nullptr)
	{
		printf("[Error] SendPacket() : Session Not Found\n");
		return -1;
	}

	pPacket->Encryption();
	session->sendQ.Enqueue(pPacket->GetBufferPtr(), pPacket->GetUseSize());
	sendTPS++;
	//PostSend(session);
	return 0;
}

int CNetwork::SendBroadcast(CPacket* pPacket)
{
	pPacket->Encryption();

	for (int i = 0; i < dfMAX_SESSION_SIZE; i++)
	{
		if (sessionList[i]->isUsed == false) continue;
		
		sessionList[i]->sendQ.Enqueue(pPacket->GetBufferPtr(), pPacket->GetUseSize());
		sendTPS++;
	}
	return 0;
}

bool CNetwork::Disconnect(SESSION_ID sessionID)
{
	Session* session = sessionList.FindSession(sessionID);
	if (session == nullptr) return false;

	shutdown(session->sock, SD_BOTH);
	return true;
}

bool CNetwork::Disconnect(Session* pSession)
{
	if (pSession == nullptr) return false;

	shutdown(pSession->sock, SD_BOTH);
	return true;
}

unsigned CNetwork::GetSessionSize()
{
	return sessionList.GetSessionCount();
}


/*PostSend 디버그용
	static CRingBuffer checkQ;
	static CPacket checkPack(10000);
	short h = 0;
	short h2 = 0;
	__int64 p = 0;
	__int64 p2 = 0;
	static __int64 op = 0;
	checkQ.Clear();
	checkPack.Clear();
	checkQ.Enqueue(wsabuf[0].buf, wsabuf[0].len);
	if (useSize > deqSize)
	{
		checkQ.Enqueue(wsabuf[1].buf, wsabuf[1].len);
	}
	checkQ.Dequeue(checkPack.GetBufferPtr(), useSize);
	CPacket checkPack2 = checkPack;
	int loop = useSize / 10;
	for (int i = 0; i < loop; i++)
	{
		checkPack >> h;
		checkPack >> p;
		if (op == 0)
		{
			op = p;
			continue;
		}
		if (h != 8 || p != op + 1)
		{
			printf("PREV [%08d] -> NEXT [%08d]\n", op, p);
			for (int j = 0; j < loop; j++)
			{
				checkPack2 >> h2;
				checkPack2 >> p2;
				printf("[%08d]", p2);
			}
			printf("\n");

			int a = 10;
		}
		op = p;
	}*/