#pragma once



#define SERVER_PORT 20000

//---------------------------------------------------------------
// 패킷헤더.
//
//---------------------------------------------------------------
/*
	BYTE	byCode;			// 패킷코드 0x89 고정.
	BYTE	bySize;			// 패킷 사이즈.
	BYTE	byType;			// 패킷타입.
	BYTE	byTemp;			// 사용안함.
*/

//---------------------------------------------------------------
// 패킷의 가장 앞에 들어갈 패킷코드.
//---------------------------------------------------------------
#define dfNETWORK_PACKET_CODE	((BYTE)0x89)
//---------------------------------------------------------------
// 패킷의 가장 뒤에 들어갈 패킷코드.
//---------------------------------------------------------------
#define dfNETWORK_PACKET_END	((BYTE)0x79)
//---------------------------------------------------------------
// 패킷의 끝 부분에는 1Byte 의 EndCode 가 포함된다.  0x79
//
//---------------------------------------------------------------

#pragma pack(push,1)
typedef struct st_NETWORK_PACKET_HEADER
{
	BYTE	byCode;			// 패킷코드 0x89 고정.
	BYTE	bySize;			// 패킷 사이즈.
	BYTE	byType;			// 패킷타입.
	BYTE	byTemp;			// 사용안함.
}PACKET_HEADER;

typedef BYTE ENDCODE;
#pragma pack(pop)

enum USER_MESSAGE
{
	UM_NETWORK = (WM_USER + 1),
};

enum class MsgType : unsigned char
{

};