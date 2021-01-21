#include "stdafx.h"
#include <iostream>
#include "CGameServer.h"

CGameServer server;
HWND g_hwnd;

int main()
{
	_wsetlocale(LC_ALL, L"korean");
	
	g_hwnd = CreateWindowA("STATIC", "dummy", NULL, 0, 0, 100, 100, NULL, NULL, NULL, NULL);
	
	for (;;)
	{
		//if (GetAsyncKeyState(VK_ESCAPE))
		//{
		//	printf("서버 종료\n");
		//	server.Shutdown();
		//	break;
		//}

		//server.Monitor();
		Sleep(10);
	}

	return 0;
}