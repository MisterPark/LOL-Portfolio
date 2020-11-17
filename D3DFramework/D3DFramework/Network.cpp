#include "stdafx.h"
#include "Network.h"

Network* pNetwork = nullptr;

Network::Network()
{
}

Network::~Network()
{
}

Network* Network::GetInstance()
{
    if (pNetwork == nullptr)
    {
        pNetwork = new Network;
    }
    return pNetwork;
}

void Network::Destroy()
{
    if (pNetwork)
    {
        delete pNetwork;
        pNetwork = nullptr;
    }
}

void Network::Initialize()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		pNetwork->err_quit(L"WSAStartup() Error");
	}

	pNetwork->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (pNetwork->sock == INVALID_SOCKET)
	{
		pNetwork->err_quit(L"socket err");
	}
	int retval = WSAAsyncSelect(pNetwork->sock, g_hwnd, UM_NETWORK, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
	if (retval == SOCKET_ERROR)
	{
		pNetwork->err_quit(L"WSAAsyncSelect err");
	}
	memset(&pNetwork->serveraddr, 0, sizeof(serveraddr));
	pNetwork->serveraddr.sin_family = AF_INET;
	WSAStringToAddressW(pNetwork->serverIPtext, AF_INET, NULL, (SOCKADDR*)&pNetwork->serveraddr, &pNetwork->addrlen);
	pNetwork->serveraddr.sin_port = htons(SERVER_PORT);
}

void Network::Release()
{
	closesocket(pNetwork->sock);
	WSACleanup();
}

void Network::Connect()
{
	int retval = connect(pNetwork->sock, (SOCKADDR*)&pNetwork->serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			pNetwork->err_quit(L"connect err");
		}
		else
		{
			//우드블럭 처리 code 10035
			//err_display(WSAGetLastError());
		}
	}

}

bool Network::NetProc(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam))
	{
		pNetwork->err_quit(WSAGETSELECTERROR(lParam));
	}
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_CONNECT:
		// 연결 성공 처리
		return true;
	case FD_READ:
		if (!pNetwork->RecvProc())
		{
			MessageBox(NULL, L"받기 실패", NULL, MB_OK);
			return false;
		}
		return true;
	case FD_WRITE:
		pNetwork->sendFlag = true;
		if (!pNetwork->SendProc())
		{
			return false;
		}
		return true;
	case FD_CLOSE:
		closesocket(pNetwork->sock);
		return false;
		break;
	}
	return true;
}

bool Network::SendPacket(PACKET_HEADER* pHeader, CPacket* pPacket)
{
	if (pNetwork->sock == INVALID_SOCKET) { return false; }
	if (!pNetwork->sendFlag) { return false; }

	PACKET_HEADER header = *pHeader;
	CPacket* pack = pPacket;
	ENDCODE endcode = dfNETWORK_PACKET_END;
	int retval = 0;

	//차후 직렬화 버퍼를 사용하여 해결할 것임
	retval = pNetwork->sendQ.Enqueue((char*)&header, sizeof(header));
	if (retval != sizeof(header)) { pNetwork->err_quit(L"센드큐 꽉참"); }
	retval = pNetwork->sendQ.Enqueue(pack->GetReadPtr(), header.bySize);
	if (retval != header.bySize) { pNetwork->err_quit(L"센드큐 꽉참"); }
	retval = pNetwork->sendQ.Enqueue((char*)&endcode, sizeof(endcode));
	if (retval != sizeof(endcode)) { pNetwork->err_quit(L"센드큐 꽉참"); }

	pNetwork->SendProc();
	return true;
}

bool Network::SendProc()
{
	int retval;

	if (!sendFlag) { return true; }

	while (sendQ.GetUseSize() > 0)
	{
		retval = send(sock, sendQ.GetFrontBufferPtr(), sendQ.GetDeqSize(), 0);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				sendFlag = false;
				return true;
			}
			else
			{
				return false;
			}
		}

		sendQ.MoveFront(retval);
	}

	return true;
}

bool Network::RecvProc()
{
	st_NETWORK_PACKET_HEADER header;
	CPacket pack;
	ENDCODE endcode;
	int retval = 0;

	retval = recv(sock, recvQ.GetRearBufferPtr(), recvQ.GetEnqSize(), 0);
	if (retval == SOCKET_ERROR)
	{
		err_quit(L"recv err");
	}
	else if (retval == 0)
	{
		MessageBoxW(NULL, L"리시브 0", NULL, MB_OK);
		return true;
	}

	recvQ.MoveRear(retval);

	for(;;)
	{
		// 헤더 이상 받았는가
		if (recvQ.GetUseSize() < sizeof(header) + 1) { break; }
		// 헤더 뽑아보기
		retval = recvQ.Peek((char*)&header, sizeof(header));
		if (retval != sizeof(header))
		{
			err_quit(L"recvQ peek err");
		}
		// 매직넘버 확인
		if (header.byCode != dfNETWORK_PACKET_CODE) { err_quit(L"잘못된 패킷헤더 recv"); }
		// 전체 패킷이 받아졌는가
		if ((unsigned int)recvQ.GetUseSize() < (sizeof(header) + header.bySize + sizeof(endcode))) { break; }
		// 헤더 제외하고
		recvQ.MoveFront(sizeof(header));
		// 직렬화에 디큐
		retval = recvQ.Dequeue(pack.GetWritePtr(), header.bySize);
		if (retval != header.bySize) { err_quit(L"디큐 에러"); }
		// 직렬화 쓰기위치 이동
		pack.MoveWritePos(header.bySize);
		// 엔드코드 디큐
		retval = recvQ.Dequeue((char*)&endcode, sizeof(endcode));
		if (retval != sizeof(endcode)) { err_quit(L"디큐 에러"); }
		if (endcode != dfNETWORK_PACKET_END) { err_quit(L"잘못된 엔드코드 recv"); }

		PacketProc(header.byType, &pack);
	}


	return true;
}

void Network::PacketProc(BYTE type, CPacket* pPacket)
{
}


void Network::err_quit(const WCHAR* msg)
{
	int errcode = WSAGetLastError();
	LPVOID lpMsgBuf;
	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpMsgBuf, 0, NULL);
	MessageBoxW(NULL, (LPCWSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	PostQuitMessage(0);
}

void Network::err_quit(int errcode)
{
	WCHAR msg[32];
	swprintf_s(msg, L"소켓 에러 code : %d", errcode);
	LPVOID lpMsgBuf;
	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpMsgBuf, 0, NULL);
	MessageBoxW(NULL, (LPCWSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	PostQuitMessage(0);
}

void Network::err_display(const WCHAR* msg)
{
	int errcode = WSAGetLastError();
	LPVOID lpMsgBuf;
	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpMsgBuf, 0, NULL);
	MessageBoxW(NULL, (LPCWSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
}

void Network::err_display(int errcode)
{
	WCHAR msg[32];
	swprintf_s(msg, L"소켓 에러 code : %d", errcode);
	LPVOID lpMsgBuf;
	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpMsgBuf, 0, NULL);
	MessageBoxW(NULL, (LPCWSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
}
