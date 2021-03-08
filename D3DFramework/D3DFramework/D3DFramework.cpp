// D3DFramework.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "framework.h"
#include "D3DFramework.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hwnd;
HINSTANCE g_hInstance;
int screenWidth = dfCLIENT_WIDTH;
int screenHeight = dfCLIENT_HEIGHT;


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    int num;
    LPWSTR* argv = CommandLineToArgvW(lpCmdLine, &num);
    if (argv == NULL) return 1;

    for (int i = 0; i < num; i++)
    {
        wprintf(L"%ws \n", argv[i]);
    }
    wstring nick = argv[0];
    
	FileManager::GetInstance();

	TextParser::GetInstance();
	TextParser::Parse("setting.ini");

    Network::GetInstance();
	Network::SetIP(TextParser::GetIP());
    Network::SetNickname(nick);
    

    LocalFree(argv);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_D3DFRAMEWORK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_D3DFRAMEWORK));

    MSG msg;
    msg.message = WM_NULL;


    MainGame::GetInstance();
	MainGame::Initialize(screenWidth, screenHeight);

    Network::Initialize();
    //Network::Connect();

    

    // 기본 메시지 루프입니다:
    while (msg.message != WM_QUIT)
    {
        if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            MainGame::Update();
        }
        
    }


    MainGame::Release();
    MainGame::Destroy();

    TextParser::DestroyInstance();

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT rc{ 0, 0, screenWidth, screenHeight };
   constexpr int WIDOW_STYLE = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
   AdjustWindowRect(&rc, WIDOW_STYLE, false);
   HWND hWnd = CreateWindowExW(0, szWindowClass, szTitle, WIDOW_STYLE,
       CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }

   g_hwnd = hWnd;
   g_hInstance = hInstance;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
           
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_LBUTTONDOWN:
        Input::GetInstance()->mouse[(int)Keys::LBUTTON_DOWN] = true;
        Input::GetInstance()->mouse[(int)Keys::LBUTTON] = true;
        break;
    case WM_RBUTTONDOWN:
        Input::GetInstance()->mouse[(int)Keys::RBUTTON_DOWN] = true;
        Input::GetInstance()->mouse[(int)Keys::RBUTTON] = true;
        break;
    case WM_LBUTTONUP:
        Input::GetInstance()->mouse[(int)Keys::LBUTTON_UP] = true;
        Input::GetInstance()->mouse[(int)Keys::LBUTTON] = false;
        break;
    case WM_RBUTTONUP:
        Input::GetInstance()->mouse[(int)Keys::RBUTTON_UP] = true;
        Input::GetInstance()->mouse[(int)Keys::RBUTTON] = false;
        break;
    case WM_LBUTTONDBLCLK:
        Input::GetInstance()->mouse[(int)Keys::LBUTTON_DOUBLE] = true;
        break;
    case WM_RBUTTONDBLCLK:
        Input::GetInstance()->mouse[(int)Keys::RBUTTON_DOUBLE] = true;
        break;
	case WM_MOUSEWHEEL:
		if ((SHORT)HIWORD(wParam) > 0)
		{
			Input::GetInstance()->mouse[(int)Keys::WHEEL_UP] = true;
		}
		else
		{
			Input::GetInstance()->mouse[(int)Keys::WHEEL_DOWN] = true;
		}
        break;
    

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			MainGame::Shutdown();
			break;
		}
        if (wParam < 0)break;
        if (wParam > 256)break;
        Input::GetInstance()->keyDowns[wParam] = true;
        Input::GetInstance()->keys[wParam] = true;
		break;
    case WM_KEYUP:
        if (wParam < 0)break;
        if (wParam > 256)break;
        Input::GetInstance()->keyUps[wParam] = true;
        Input::GetInstance()->keys[wParam] = false;
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case UM_NETWORK:
        if (!Network::NetProc(wParam, lParam))
        {
            MessageBoxW(NULL, L"서버로 부터 연결 종료", L"Network Message", MB_OK);
            DestroyWindow(g_hwnd);
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}