#pragma once
#include <iostream>
#include <Windows.h>
#include <map>
#include "CRingBuffer.h"
#include "CircularList.h"

#define dfMAX_SESSION_SIZE 5000
#define dfINVALID_INDEX -1

using namespace std;

typedef __int64 SESSION_ID;

typedef struct SESSION
{
	SOCKET sock = INVALID_SOCKET;
	SOCKADDR_IN sockaddr = { 0, };
	OVERLAPPED sendOL = { 0, };
	OVERLAPPED recvOL = { 0, };
	CRingBuffer sendQ;
	CRingBuffer recvQ;
	unsigned long sendFlag = 0;
	int IOCount = 0;
	DWORD sendBytes = 0;
	SESSION_ID sessionID = -1;
	bool isUsed = false;
	int index = -1;
	// 디버그용
	unsigned long sendOn = 0;
}Session;

class SessionList
{
public:
	SessionList(UINT maxSessionSize = dfMAX_SESSION_SIZE);
	~SessionList();

	Session* operator [](unsigned int index);

	Session* CreateSession(SOCKET sock, SOCKADDR_IN sockaddr);
	void	 DeleteSession(Session* target);
	Session* FindSession(SESSION_ID sessionID);
	int GetSessionCount();
private:
	SESSION_ID	SetSessionKey(); // 세션키 생성

private:
	CircularList<int>* indexStack;
	Session* sessionArray = nullptr; // SendThread 순회용
	map<SESSION_ID, Session*> sessionMap;
	SRWLOCK sessionLocker;
	SESSION_ID sessionKey = 0;
	unsigned int maxSize = 0;
};

