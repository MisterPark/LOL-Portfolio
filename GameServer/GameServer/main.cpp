#include "stdafx.h"
#include <iostream>
#include "CGameServer.h"

CGameServer server;

int main()
{
	_wsetlocale(LC_ALL, L"korean");

	for (;;)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			printf("서버 종료\n");
			break;
		}

		//server.Monitor();
		Sleep(10);
	}

	return 0;
}