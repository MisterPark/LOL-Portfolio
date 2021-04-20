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
    pCursor->visible = true;
}

void Engine::Cursor::Show(bool on)
{
    pCursor->visible = on;
}

void Engine::Cursor::Hide()
{
    pCursor->visible = false;
    
}

void Engine::Cursor::Update()
{
    if (enable == false)return;
    Vector3 mousePos = GetMousePos();

    transform->position = mousePos;
	transform->position.x -= pCursor->GetTexture()->GetSpriteWidth() * 0.5f;
	transform->position.y -= pCursor->GetTexture()->GetSpriteHeight() * 0.5f;

    BringToTop();

    UI::Update();

    //Billboard();
}
//
//void Engine::Cursor::Render()
//{
//    if (visible == false)return;
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
    return pCursor->visible;
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
