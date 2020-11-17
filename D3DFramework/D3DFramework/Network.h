#pragma once
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

	static bool SendPacket(PACKET_HEADER* pHeader, CPacket* pPacket);
	bool SendProc();

	bool RecvProc();
	void PacketProc(BYTE type, CPacket* pPacket);



	void err_quit(const WCHAR* msg);
	void err_quit(int errcode);
	void err_display(const WCHAR* msg);
	void err_display(int errcode);
private:
	SOCKET sock = INVALID_SOCKET;
	SOCKADDR_IN serveraddr;
	int addrlen = sizeof(serveraddr);
	WCHAR serverIPtext[64] = L"192.168.0.48";
	CRingBuffer recvQ;
	CRingBuffer sendQ;
	bool sendFlag = false;

};

