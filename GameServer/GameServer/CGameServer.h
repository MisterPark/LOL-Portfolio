#pragma once
#include "CNetwork.h"
#include "CLanLoginClient.h"
#include "CLanGameLogicClient.h"

#define dfMAX_THREAD_GAMESERVER 1

using namespace std;

typedef __int64 SESSION_ID;
typedef __int64 CLIENT_ID;

struct Client
{
	SESSION_ID	sessionID = -1;
	SOCKADDR_IN	sockaddr;
	INT64		accountNo = -1;
	wstring		nickname;
	INT			roomNum = -1; // 방번호
	INT			numInRoom = 0; // 방안에서 번호(0~9)
	BYTE		loginStatus = false;
	float		x = 0;
	float		y = 0;
	float		z = 0;
	int			hp = 100;
	int			damage = 10;
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
	Client* FindClientByAccountNO(INT64 accountNo);

	void PacketProc(SESSION_ID sessionID, CPacket* pPacket);

	void ResTest(Client* pClient);
	void ReqNick(Client* pClient, CPacket* pPacket);
	void ResNick(Client* pClient);
	void ReqLogin(Client* pClient, CPacket* pPacket);
	void ResLogin(Client* pClient);
	void ReqJoinGame(Client* pClient, CPacket* pPacket);
	void ResJoinGame(Client* pClient, Room* room);
	void ReqSelectChamp(Client* pClient, CPacket* pPacket);
	void ResSelectChamp(Client* pClinet, INT userNum, BYTE champ);
	void ReqReady(Client* pClient, CPacket* pPacket);
	void ResReady(Client* pClient);
	void ResCreatePlayer(Client* pClient);
	void ResCreateOtherPlayer(Client* pClient);
	void ResDeletePlayerToClients(INT64 accountNo);
	void ReqMovePlayer(Client* pClient, CPacket* pPacket);
	void ResMovePlayer(Client* pClient);
	void ReqFollowTarget(Client* pClient, CPacket* pPacket);
	void ResFollowTarget(INT64 accountNo, INT64 targetNo);
	void ReqAttack(Client* pClient, CPacket* pPacket);
	void ResDamage(INT64 targetNo, int hp);

public:
	void Monitor();

private:
	
	// 쓰레드 관련
	HANDLE hThread[dfMAX_THREAD_GAMESERVER];
	unsigned ID[dfMAX_THREAD_GAMESERVER];
	bool releaseFlag = false;

	// 클라이언트 관련
	map<SESSION_ID, Client*> clientMap;
	SRWLOCK clientLocker;
	map<wstring, SESSION_ID> nickMap;
	SRWLOCK nickLocker;
	// 룸
	// 대기열
	queue<Client*> readyQ;
	map<long, Room*> roomMap;
	SRWLOCK roomLocker;

	// 잡 관련
	MemoryPool<CJob>* jobPool;
	CircularList<IJob*>* jobQueue;
	// 랜 로그인 클라이언트
	//CLanLoginClient* lanLoginClient;
	// 랜 게임로직 클라이언트
	//CLanGameLogicClient* lanGameLogicClient;

public:

};

