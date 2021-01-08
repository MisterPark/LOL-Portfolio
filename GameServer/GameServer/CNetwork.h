#pragma once


#define dfMAX_WORKER 8
#define dfMAX_THREAD (2+dfMAX_WORKER)


using namespace std;

class SessionList;
typedef __int64 SESSION_ID;
typedef unsigned short HEADER;


class CNetwork
{
public:
	CNetwork();
	virtual ~CNetwork();
public:
	virtual void Shutdown();

private:
	bool InitializeNetwork();
	void ReleaseNetwork();

	// 스레드
	static unsigned __stdcall WorkerThread(void* arg);
	static unsigned __stdcall AcceptThread(void* arg);
	static unsigned __stdcall SendThread(void* arg);

	// 네트워크
	int PostSend(Session* pSession);
	int PostRecv(Session* pSession);
protected:
	virtual void OnRecv(SESSION_ID, CPacket*) = 0;
	virtual void OnSend(SESSION_ID) = 0;
	virtual void OnJoin(SESSION_ID, SOCKADDR_IN) = 0;
	virtual void OnLeave(SESSION_ID) = 0;
	virtual void OnError(SESSION_ID) = 0;
public:
	void RecvProc(Session* pSession);
	int SendUnicast(SESSION_ID sessionID, CPacket* pPacket);
	int SendBroadcast(CPacket* pPacket);
	bool Disconnect(SESSION_ID sessionID);
	bool Disconnect(Session* pSession);

	// 모니터링용 세션 갯수
	unsigned GetSessionSize(); 
private:
	// 쓰레드 관련
	HANDLE hThread[dfMAX_THREAD];
	unsigned ID[dfMAX_THREAD];
	bool shutdownFlag = false;
	// 세션 관련
	SessionList sessionList;
	// 네트워크 관련
	SOCKET listenSock = INVALID_SOCKET;
	HANDLE hIOCP = INVALID_HANDLE_VALUE;

protected:
	// 패킷풀
	PacketPool* packPool;
	
public:
	// 디버그 용
	__int64 threadLoopCount = 0;
	__int64 connectCount = 0;
	__int64 connectTotal = 0;
	__int64 connectFail = 0;
	__int64 recvTPS = 0;
	__int64 sendTPS = 0;

};




