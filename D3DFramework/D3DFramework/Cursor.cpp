#include "stdafx.h"
#include "Cursor.h"
#include "Rectangle.h"
#include "UIRenderer.h"

Engine::Cursor* pCursor = nullptr;

Engine::Cursor::Cursor()
{
    ShowCursor(FALSE);
    
    SetTexture(L"hover_precise");
    SetSizeByTexture();
    transform->scale = { 0.8f,0.8f,1.f };
    dontDestroy = true;
}

Engine::Cursor::~Cursor()
{
    ShowCursor(TRUE);
}

Cursor* Engine::Cursor::GetInstance()
{
    if (pCursor == nullptr)
    {
        pCursor = new Cursor();
    }
    return pCursor;
}

void Engine::Cursor::Destroy()
{
    if (pCursor)
    {
        delete pCursor;
        pCursor = nullptr;
    }
}

Vector3 Engine::Cursor::GetMousePos()
{
    Vector3 pos;
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(g_hwnd, &pt);
    pos.x = (float)pt.x;
    pos.y = (float)pt.y;
    return pos;
}

void Engine::Cursor::Show()
{
    if (pCursor->isVisible) return;

    pCursor->isVisible = true;
    
}

void Engine::Cursor::Show(bool on)
{
    pCursor->isVisible = on;
}

void Engine::Cursor::Hide()
{
    if (pCursor->isVisible == false) return;

    pCursor->isVisible = false;
    
}

void Engine::Cursor::Update()
{
    if (isEnable == false)return;
    Vector3 mousePos = GetMousePos();

    transform->position = mousePos;

    BringToTop();

    UI::Update();

    //Billboard();
}
//
//void Engine::Cursor::Render()
//{
//    if (isVisible == false)return;
//
//    switch (mode)
//    {
//    case Engine::CursorMode::Normal:
//        RenderManager::DrawUI(L"hover_precise", *transform, 0);
//        break;
//    case Engine::CursorMode::SingleTarget:
//        RenderManager::DrawSprite(L"singletarget", *transform, 0);
//        break;
//    default:
//        break;
//    }
//    
//}

void Engine::Cursor::Initialize()
{
}

void Engine::Cursor::Release()
{
}

bool Engine::Cursor::IsVisible()
{
    return pCursor->isVisible;
}

void Engine::Cursor::SetRenderCenter(bool isCenter)
{
    pCursor->isRenderCenter = isCenter;
}

void Engine::Cursor::SetMode(CursorMode _mode)
{
    pCursor->mode = _mode;

    switch (_mode)
    {
    case Engine::CursorMode::Normal:
        pCursor->SetTexture(L"hover_precise");
        pCursor->SetSizeByTexture();
        break;
    case Engine::CursorMode::SingleTarget:
        pCursor->SetTexture(L"singletarget");
        pCursor->SetSizeByTexture();
        break;
    default:
        break;
    }
}

void Engine::Cursor::ChangeMode()
{
    switch (pCursor->mode)
    {
    case Engine::CursorMode::Normal:
        SetMode(CursorMode::SingleTarget);
        break;
    case Engine::CursorMode::SingleTarget:
        SetMode(CursorMode::Normal);
        break;
    default:
        break;
    }
}
