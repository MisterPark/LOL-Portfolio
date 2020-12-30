#include "stdafx.h"
#include "SessionList.h"

SessionList::SessionList(UINT maxSessionSize)
{
	InitializeSRWLock(&sessionLocker);
	maxSize = maxSessionSize;
	sessionArray = new Session[maxSessionSize];
	indexStack = new CircularList<int>(maxSessionSize);
	for (unsigned int i = 0; i < maxSessionSize; i++)
	{
		indexStack->PushBack(i);
	}
}

SessionList::~SessionList()
{
	delete[] sessionArray;
}

Session* SessionList::operator [](unsigned int index)
{
	return &sessionArray[index];
}

Session* SessionList::CreateSession(SOCKET sock, SOCKADDR_IN sockaddr)
{
	AcquireSRWLockExclusive(&sessionLocker);

	int allocIndex;
	if (!indexStack->Pop(&allocIndex))
	{
		// 서버 수용인원 초과
		return nullptr;
	}

	Session* session = &sessionArray[allocIndex];
	session->sock = sock;
	session->sockaddr = sockaddr;
	session->sessionID = SetSessionKey();
	session->recvQ.Clear();
	session->sendQ.Clear();
	session->isUsed = true;
	session->index = allocIndex;

	sessionMap[session->sessionID] = session;

	ReleaseSRWLockExclusive(&sessionLocker);

	return session;
}

void SessionList::DeleteSession(Session* target)
{
	if (target == nullptr) return;
	
	target->isUsed = false;
	
	AcquireSRWLockExclusive(&sessionLocker);
	indexStack->Push(target->index);

	auto iter = sessionMap.find(target->sessionID);
	sessionMap.erase(iter);

	ReleaseSRWLockExclusive(&sessionLocker);

	closesocket(target->sock);
}

Session* SessionList::FindSession(SESSION_ID sessionID)
{
	Session* target = nullptr;
	map<SESSION_ID, Session*>::iterator iter;

	AcquireSRWLockExclusive(&sessionLocker);
	iter = sessionMap.find(sessionID);

	if (iter != sessionMap.end())
	{
		target = (*iter).second;
	}

	ReleaseSRWLockExclusive(&sessionLocker);

	return target;
}

int SessionList::GetSessionCount()
{
	return (int)sessionMap.size();
}

SESSION_ID SessionList::SetSessionKey()
{
	return ++sessionKey;
}