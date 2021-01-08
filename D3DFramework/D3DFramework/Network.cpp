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
		pNetwork->isConnected = true;
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
			MessageBox(NULL, L"보내기 실패", NULL, MB_OK);
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

bool Network::SendPacket(CPacket* pPacket)
{
	if (pNetwork->sock == INVALID_SOCKET) { return false; }
	if (!pNetwork->sendFlag) { return false; }

	pPacket->Encryption();
	pNetwork->sendQ.Enqueue(pPacket->GetBufferPtr(), pPacket->GetUseSize());

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
	NetHeader header;
	CPacket* pack;
	int retval = 0;
	int size = 0;

	retval = recv(sock, recvQ.GetRearBufferPtr(), recvQ.GetEnqSize(), 0);
	if (retval == SOCKET_ERROR)
	{
		err_quit(L"recv err");
	}
	else if (retval == 0)
	{
		//MessageBoxW(NULL, L"리시브 0", NULL, MB_OK);
		return true;
	}

	recvQ.MoveRear(retval);

	for(;;)
	{
		size = recvQ.GetUseSize();
		if (size < sizeof(NetHeader)) break;
		recvQ.Peek((char*)&header, sizeof(NetHeader));
		if (size < sizeof(NetHeader) + header.len) break;
		recvQ.MoveFront(sizeof(NetHeader));

		pack = new CPacket();
		pack->Clear();

		recvQ.Dequeue(pack->GetBufferPtr(), header.len);
		pack->MoveWritePos(header.len);
		if (!pack->Decryption(header))
		{
			err_quit(L"패킷 복호화 실패");
			break;
		}

		// 큐에 넣고 활성화된 씬에서 pop하는걸로
		packQ.push(pack);
		//PacketProc(&pack);
	}


	return true;
}

void Network::PacketProc(CPacket* pPacket)
{
	WORD type;
	*pPacket >> type;
	switch (type)
	{
	default:
		Debug::Print("[Warning] 정의되지 않은 패킷 타입 감지\n");
		break;
	}
}

void Network::SetNickname(const wstring& nick)
{
	pNetwork->nick = nick;
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
