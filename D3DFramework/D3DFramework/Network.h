#pragma once

struct NetUser
{
	INT number = -1;
	BYTE champ = 0;
	BYTE spell1 = 0;
	BYTE spell2 = 0;
	bool isMine = false;
};

class Network
{
private:
	Network();
	~Network();

public:
	static Network* GetInstance();
	static void Destroy();
	static void Initialize();
	static void Release();

	static void Connect();

	static bool NetProc(WPARAM wParam, LPARAM lParam);

	static bool SendPacket(CPacket* pPacket);
	bool SendProc();

	bool RecvProc();
	void PacketProc(CPacket* pPacket);


	static void SetNickname(const wstring& nick);


	void err_quit(const WCHAR* msg);
	void err_quit(int errcode);
	void err_display(const WCHAR* msg);
	void err_display(int errcode);
private:
	SOCKET sock = INVALID_SOCKET;
	SOCKADDR_IN serveraddr;
	int addrlen = sizeof(serveraddr);
	WCHAR serverIPtext[64] = L"192.168.0.34";
	CRingBuffer recvQ;
	CRingBuffer sendQ;
	bool sendFlag = false;

public:
	queue<CPacket*> packQ;
public:
	bool isConnected = false;
	wstring nick;
	INT number = -1;
	map<INT, NetUser> users;

};

