#pragma once
// 게임서버 33333
#define dfSERVER_PORT 1222
#define dfROOM_MAX_USER_COUNT 10

enum LoginResult
{
	SUCCEED,
	ID_DOES_NOT_EXIST,
	PASSWORD_DOES_NOT_MATCH,
	ID_ALREADY_LOGGED_IN,
	SPECIAL_CHARACTER,
};

enum PROTOCOL
{
	//=================================
	// ★ 게임 서버 ★
	//=================================
	GAME_SERVER = 1000,
	//---------------------------------
	// 닉네임 중복체크 요청(게임서버 <- 클라이언트)
	//
	//	WORD	type
	//	WCHAR	nickName[20]	// NULL포함
	//---------------------------------
	GAME_REQ_NICK,
	//---------------------------------
	// 닉네임 중복체크 응답(게임서버 -> 클라이언트)
	//
	//	WORD	type
	//	WCHAR	nickName[20]	// NULL포함
	//	BYTE	status
	//---------------------------------
	GAME_RES_NICK,
	//---------------------------------
	// 로그인 요청(게임서버 <- 클라이언트)
	//
	//	WORD	type
	//	WCHAR	nickName[20]	// NULL포함
	//---------------------------------
	GAME_REQ_LOGIN,
	//---------------------------------
	// 로그인 응답(게임서버 -> 클라이언트)
	//
	// WORD	type
	// WCHAR	nickName[20]	// NULL포함
	// INT64	sessionID
	// BYTE	status	//0:실패 1:성공
	//---------------------------------
	GAME_RES_LOGIN,
	//---------------------------------
	// 게임 참가 요청(게임서버 <- 클라이언트)
	//
	//	WORD	type
	//---------------------------------
	GAME_REQ_JOIN_GAME,
	//---------------------------------
	// 게임 참가 응답(게임서버 -> 클라이언트)
	//
	//	WORD	type
	//	
	//	UINT	userCount
	//	{
	//		WCHAR	nickName[20] // NULL포함
	//		UINT	number
	//	}
	//	
	//---------------------------------
	GAME_RES_JOIN_GAME,
	//---------------------------------
	// 챔피언 선택 요청(게임서버 <- 클라이언트)
	//
	//	WORD	type
	//	BYTE	champ
	//---------------------------------
	GAME_REQ_SELECT_CHAMP,
	//---------------------------------
	// 챔피언 선택 응답(게임서버 -> 클라이언트)
	//
	//	WORD	type
	//	UINT	userNum
	//	BYTE	champ
	//---------------------------------
	GAME_RES_SELECT_CHAMP,
	//---------------------------------
	// 준비 요청(게임서버 <- 클라이언트)
	//
	//	WORD	type
	//---------------------------------
	GAME_REQ_READY,
	//---------------------------------
	// 준비 응답(게임서버 -> 클라이언트)
	//
	//	WORD	type
	//---------------------------------
	GAME_RES_READY,
	//---------------------------------
	// 캐릭터 생성 응답(게임서버 -> 클라이언트)
	//
	// WORD	type
	// INT64	accountNo
	// WCHAR	nickName[20]	// NULL포함
	// float	x
	// float	y
	// float	z
	//---------------------------------
	GAME_RES_CREATE_PLAYER,
	//---------------------------------
	// 캐릭터 삭제 응답(게임서버 -> 클라이언트)
	//
	// WORD	type
	// INT64	accountNo
	//---------------------------------
	GAME_RES_DELETE_PLAYER,
	//---------------------------------
	// 캐릭터 이동 요청(게임서버 <- 클라이언트)
	//
	// WORD	type
	// INT64	accountNo
	// float	x
	// float	y
	// float	z
	//---------------------------------
	GAME_REQ_MOVE_MY_PLAYER,
	//---------------------------------
	// 캐릭터 이동 응답(게임서버 -> 클라이언트)
	//
	// WORD	type
	// INT64	accountNo
	// float	x
	// float	y
	// float	z
	//---------------------------------
	GAME_RES_MOVE_PLAYER,
	//---------------------------------
	// 따라가기 요청(게임서버 <- 클라이언트)
	//
	// WORD	type
	// INT64	accountNo
	// INT64	targetNo
	//---------------------------------
	GAME_REQ_FOLLOW_TARGET,
	//---------------------------------
	// 따라가기 응답(게임서버 -> 클라이언트)
	//
	// WORD	type
	// INT64	accountNo
	// INT64	targetNo
	//---------------------------------
	GAME_RES_FOLLOW_TARGET,
	//---------------------------------
	// 공격 요청(게임서버 <- 클라이언트)
	//
	// WORD	type
	// INT64	accountNo
	// INT64	targetNo
	//---------------------------------
	GAME_REQ_ATTACK,
	//---------------------------------
	// 데미지 응답(게임서버 -> 클라이언트)
	//
	// WORD	type
	// INT64	targetNo
	// int		hp
	//---------------------------------
	GAME_RES_DAMAGE,


	//=================================
	// ★ 랜로그인 서버 ★
	//=================================
	LAN_LOGIN_SERVER = 10000,
	//---------------------------------
	// 서버용 로그인 ( 랜로그인서버 <- 랜로그인클라 )
	//
	//	WORD	Type
	//	WORD	ServerType	// 프로토콜 내 서버타입
	//
	//---------------------------------
	LAN_LOGIN_REQ_SERVER_LOGIN,
	//---------------------------------
	// 클라이언트 생성 요청 ( 랜로그인서버 -> 랜로그인 클라 )
	//
	//	WORD	Type
	//
	//	INT64	AccountNo
	//	CHAR	SessionKey[64]
	//	INT64	Parameter
	//
	//---------------------------------
	LAN_LOGIN_REQ_NEW_CLIENT,
	//---------------------------------
	// 클라이언트 생성 응답 ( 랜로그인서버 <- 클라이언트 )
	//
	//	WORD	Type
	//	WORD	serverType
	//	INT64	AccountNo
	//	INT64	Parameter
	//---------------------------------
	LAN_LOGIN_RES_NEW_CLIENT,
	//---------------------------------
	// 계정 로그아웃 요청 ( 랜로그인서버 <- 게임랜로그인클라 )
	//
	// WORD	Type
	// INT64	AccountNo
	//---------------------------------
	LAN_LOGIN_REQ_ACCOUNT_LOGOUT,

	//=================================
	// ★ 랜게임로직 서버 ★
	//=================================
	LAN_GAMELOGIC_SERVER = 20000,
	//---------------------------------
	// 서버용 로그인 ( 랜로그인서버 <- 랜로그인클라 )
	//
	//	WORD	Type
	//	WORD	ServerType	// 프로토콜 내 서버타입
	//
	//---------------------------------
	LAN_GAMELOGIC_REQ_SERVER_LOGIN,
	LAN_GAMELOGIC_REQ_CREATE_PLAYER,
	LAN_GAMELOGIC_REQ_DELETE_PLAYER,
};