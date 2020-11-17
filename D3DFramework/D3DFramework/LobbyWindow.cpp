#include "stdafx.h"
#include "LobbyWindow.h"

LobbyWindow* pLobby = nullptr;

static LRESULT CALLBACK WndProc2(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return pLobby->WndProc(hWnd, Msg, wParam, lParam);
}

LobbyWindow::LobbyWindow()
{
	
}

LobbyWindow::~LobbyWindow()
{
}

bool LobbyWindow::Create()
{
	RECT rc;
	GetWindowRect(g_hwnd, &rc);
	int xPos = rc.left + ((rc.right - rc.left) / 2) - 150;
	int yPos = rc.top + ((rc.bottom - rc.top) / 2) - 100;
	pLobby = this;
	WNDCLASS WndClass;
	WndClass.cbClsExtra = WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(g_hInstance, IDI_APPLICATION);
	WndClass.hInstance = g_hInstance;
	WndClass.lpfnWndProc = ::WndProc2;
	WndClass.lpszClassName = title;
	WndClass.lpszMenuName = NULL;
	WndClass.style = 0;
	RegisterClass(&WndClass);
	hLobbyWnd = CreateWindowEx(WS_EX_CLIENTEDGE, title, title, WS_OVERLAPPEDWINDOW , xPos, yPos, 300, 200, g_hwnd, NULL, g_hInstance, NULL);

	this->hEdit = CreateWindow((LPCWSTR)L"edit", (LPCWSTR)L"Nickname", WS_CHILD | WS_VISIBLE | WS_BORDER,
		10, 10, 150, 25, hLobbyWnd, (HMENU)EDIT1, g_hInstance, NULL);
	this->hButton1 = CreateWindow((LPCWSTR)L"button", (LPCWSTR)L"접속", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		170, 10, 50, 25, hLobbyWnd, (HMENU)BUTTON1, g_hInstance, NULL);
	this->hButton2 = CreateWindow((LPCWSTR)L"button", (LPCWSTR)L"취소", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 10, 50, 25, hLobbyWnd, (HMENU)BUTTON2, g_hInstance, NULL);
	
	if (hLobbyWnd == NULL) { return false; }
	ShowWindow(hLobbyWnd, SW_SHOWDEFAULT);
	UpdateWindow(hLobbyWnd);
	SetFocus(hLobbyWnd);

	return false;
}

LobbyWindow * LobbyWindow::GetInstance()
{
	if (pLobby == nullptr)
	{
		pLobby = new LobbyWindow();
	}
	return pLobby;
}

void LobbyWindow::Destroy()
{
	if (pLobby)
	{
		delete pLobby;
		pLobby = nullptr;
	}
}

void LobbyWindow::Show()
{
	ShowWindow(pLobby->hLobbyWnd,SW_SHOW);
}

void LobbyWindow::Hide()
{
	ShowWindow(pLobby->hLobbyWnd, SW_HIDE);
}

bool LobbyWindow::Run(void)
{
	MSG Msg;
	while (true)
	{
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			if (Msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{

		}
	}
	return tryToConnect;
}

LRESULT LobbyWindow::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		result = LobbyResult::CANCEL;
		//PostQuitMessage(0);
		break;
	case WM_TIMER:
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_COMMAND:
	{
		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
		{
			switch (LOWORD(wParam))
			{
			case BUTTON1:
				result = LobbyResult::OK;
				tryToConnect = true;
				GetWindowTextW(hEdit, serverIPtext, 64);
				//DestroyWindow(hLobbyWnd);
				break;
			case BUTTON2:
				result = LobbyResult::CANCEL;
				tryToConnect = false;
				Hide();
				break;
				
			default:
				break;
			}
		}
		break;

		default:
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}
