#pragma once
#include <Windows.h>
#include <iostream>

enum CHILD_ID
{
	EDIT1,
	BUTTON1,
	BUTTON2
};

enum class LobbyResult
{
	NONE,
	OK,
	CANCEL,
	DO,
};

class LobbyWindow
{
private:
	LobbyWindow();
	~LobbyWindow();
public:
	bool Create();
	static LobbyWindow* GetInstance();
	static void Destroy();

	static void Show();
	static void Hide();

	bool Run(void);
	LRESULT WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

private:
	bool tryToConnect = false;
	HWND hLobbyWnd;
	WCHAR title[64] = L"닉네임을 적어주세요.";

	HWND hEdit;
	HWND hButton1;
	HWND hButton2;

public:
	WCHAR serverIPtext[64];
	LobbyResult result = LobbyResult::NONE;
};

