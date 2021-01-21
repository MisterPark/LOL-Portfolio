#pragma once
#include "CNetwork.h"
//#include "CLanLoginClient.h"
//#include "CLanGameLogicClient.h"
#include "GameRoom.h"

#define dfMAX_THREAD_GAMESERVER 1
#define dfROOM_MAX_USER_COUNT 2

using namespace std;

typedef __int64 SESSION_ID;
typedef __int64 CLIENT_ID;

class Client
{
public:
	SESSION_ID	sessionID = -1;
	SOCKADDR_IN	sockaddr;
	wstring		nickname;
	INT			roomNum = -1; // 방번호
	INT			numInRoom = -1; // 방안에서 번호(0~9)
	BYTE		loginStatus = false;
	BYTE		champ;
	INT			progress = 0;
	bool		isCompleteLoading = false;
	BYTE		spell1 = 6;
	BYTE		spell2 = 3;
};

struct Account
{
	wstring nickname;
	INT		roomNum = -1;
	INT		number = -1;
	BYTE	champ = 0;
	BYTE	spell1 = 6;
	BYTE	spell2 = 3;
};

struct Room
{
	INT number;
	Client* users[dfROOM_MAX_USER_COUNT] = {};
	bool ready[dfROOM_MAX_USER_COUNT] = {};
};

class CGameServer : public CNetwork
{
public:
	CGameServer();
	virtual ~CGameServer();
public:
	virtual void Shutdown();
private:
	void InitializeGameServer();
	void ReleaseGameServer();
public:

	virtual void OnRecv(SESSION_ID sessionID, CPacket* pPacket);
	virtual void OnSend(SESSION_ID sessionID);
	virtual void OnJoin(SESSION_ID sessionID, SOCKADDR_IN sockaddr);
	virtual void OnLeave(SESSION_ID sessionID);
	virtual void OnError(SESSION_ID sessionID);


	// 스레드
	static unsigned WINAPI UpdateThread(LPVOID arg);
	void Update();

	// 클라이언트 관련
	Client* CreateClient(SESSION_ID sessionID, SOCKADDR_IN sockaddr);
	void	DeleteClient(SESSION_ID sessionID);
	Client* FindClient(SESSION_ID sessionID);

	void PacketProc(SESSION_ID sessionID, CPacket* pPacket);

	void ReqTest(Client* pClient, CPacket* pPacket);
	void ResTest(Client* pClient);

	void ReqNick(Client* pClient, CPacket* pPacket);
	void ResNick(Client* pClient);
	void ReqLogin(Client* pClient, CPacket* pPacket);
	void ResLogin(Client* pClient);
	void ReqJoinGame(Client* pClient, CPacket* pPacket);
	void ResJoinGame(Client* pClient, Room* room);
	void ReqSelectChamp(Client* pClient, CPacket* pPacket);
	void ResSelectChamp(Client* pClient, INT userNum, BYTE champ);
	void ReqReady(Client* pClient, CPacket* pPacket);
	void ResReady(Client* pClient);
	void ResStart(Client* pClient);
	// 여기부터 인게임 관련
	void ReqEnterGame(Client* pClient, CPacket* pPacket);
	void ResEnterGame(Client* pClient, GameRoom* pRoom);
	void ReqLoading(Client* pClient, CPacket* pPacket);
	void ResLoading(Client* pClient, int progress);
	void ReqCompleteLoading(Client* pClient, CPacket* pPacket);
	void ResCompleteLoading(Client* pClient);
	// 게임씬
	void ReqTime(Client* pClient, CPacket* pPacket);
	void ResTime(Client* pClient, DWORD time);
	void ReqMove(Client* pClient, CPacket* pPacket);
	void ResMove(Client* pClient, int gameID, list<Vector3>& path);

public:
	void Monitor();

private:
	
	// 쓰레드 관련
	HANDLE hLogicThread[dfMAX_THREAD_GAMESERVER];
	unsigned threadID[dfMAX_THREAD_GAMESERVER];
	bool releaseFlag = false;

	// 클라이언트 관련
	map<SESSION_ID, Client*> clientMap;
	SRWLOCK clientLocker;
	map<wstring, SESSION_ID> nickMap;
	SRWLOCK nickLocker;
	// 닉네임에 따른 계정정보
	// 초기접속시 생성
	// 이후 접속이 종료되어도 남음(서버종료시 삭제)
	map<wstring, Account> accountMap;
	SRWLOCK accountLocker;
	// 룸
	// 대기열
	queue<Client*> readyQ;
	map<INT, Room*> roomMap;
	SRWLOCK roomLocker;

	map<INT, GameRoom*> gameroomMap;
	SRWLOCK gameroomLocker;


	// 잡 관련
	MemoryPool<CJob>* jobPool;
	CircularList<IJob*>* jobQueue;

public:

};

