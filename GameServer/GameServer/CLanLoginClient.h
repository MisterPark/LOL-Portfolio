#pragma once
#include "CLanClient.h"

class CLanLoginClient : public CLanClient
{
public:
	CLanLoginClient(const char* ip, WORD port);
	virtual ~CLanLoginClient();

	virtual void OnEnter();
	virtual void OnLeave();
	virtual void OnRecv(CPacket* packet);
	virtual void OnSend();
	virtual void OnError();

	void ReqCreateNewClient(CPacket* pPacket);
	void ReqAccountLogout(INT64 accountNo);

	bool TokenCheck(INT64 accountNo, CHAR* sessionKey);
	void DeleteToken(INT64 accountNo, CHAR* sessionKey);

private:
	map<INT64, CHAR*> tokenMap;
	SRWLOCK srwToken;
};

