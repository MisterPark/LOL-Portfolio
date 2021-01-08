#pragma once

class Client;

class GameRoom
{
public:
	GameRoom();
	~GameRoom();

	void StartGame();

	static unsigned WINAPI GameLogicThread(LPVOID arg);
	void UpdateGameLogic();



	void LockUser();
	void UnlockUser();
public:
	INT number = -1;
	map<INT, Client*> users;
	SRWLOCK userLocker;

private:
	HANDLE hGameLogicThread = INVALID_HANDLE_VALUE;
	unsigned threadID = 0;
	bool isStarted = false;
	bool releaseFlag = false;
};

