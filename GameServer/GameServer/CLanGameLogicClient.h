#pragma once
#include "CLanClient.h"


class CLanGameLogicClient : public CLanClient
{
public:
	CLanGameLogicClient(const char* ip, WORD port);
	virtual ~CLanGameLogicClient();

	virtual void OnEnter();
	virtual void OnLeave();
	virtual void OnRecv(CPacket* packet);
	virtual void OnSend();
	virtual void OnError();

private:

};

