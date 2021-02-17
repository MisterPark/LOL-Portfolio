#include "stdafx.h"
#include "Cursor.h"
#include "Rectangle.h"

PKH::Cursor* pCursor = nullptr;

PKH::Cursor::Cursor()
{
    ShowCursor(FALSE);
    
    SetTexture(L"hover_precise");
    SetSizeByTexture();
    transform->scale = { 0.8f,0.8f,1.f };
    type = UIType::CURSOR;
}

PKH::Cursor::~Cursor()
{
    ShowCursor(TRUE);
}

Cursor* PKH::Cursor::GetInstance()
{
    if (pCursor == nullptr)
    {
        pCursor = new Cursor();
    }
    return pCursor;
}

void PKH::Cursor::Destroy()
{
    if (pCursor)
    {
        delete pCursor;
        pCursor = nullptr;
    }
}

Vector3 PKH::Cursor::GetMousePos()
{
    Vector3 pos;
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(g_hwnd, &pt);
    pos.x = (float)pt.x;
    pos.y = (float)pt.y;
    return pos;
}

void PKH::Cursor::Show()
{
    if (pCursor->isVisible) return;

    pCursor->isVisible = true;
    
}

void PKH::Cursor::Show(bool on)
{
    pCursor->isVisible = on;
}

void PKH::Cursor::Hide()
{
    if (pCursor->isVisible == false) return;

    pCursor->isVisible = false;
    
}

void PKH::Cursor::Update()
{
    if (isEnable == false)return;
    Vector3 mousePos = GetMousePos();

    transform->position = mousePos;
    GameObject::Update();

    //Billboard();
}
//
//void PKH::Cursor::Render()
//{
//    if (isVisible == false)return;
//
//    switch (mode)
//    {
//    case PKH::CursorMode::Normal:
//        RenderManager::DrawUI(L"hover_precise", *transform, 0);
//        break;
//    case PKH::CursorMode::SingleTarget:
//        RenderManager::DrawSprite(L"singletarget", *transform, 0);
//        break;
//    default:
//        break;
//    }
//    
//}

void PKH::Cursor::Initialize()
{
}

void PKH::Cursor::Release()
{
}

bool PKH::Cursor::IsVisible()
{
    return pCursor->isVisible;
}

void PKH::Cursor::SetRenderCenter(bool isCenter)
{
    pCursor->isRenderCenter = isCenter;
}

void PKH::Cursor::SetMode(CursorMode _mode)
{
    pCursor->mode = _mode;

    switch (_mode)
    {
    case PKH::CursorMode::Normal:
        pCursor->SetTexture(L"hover_precise");
        pCursor->SetSizeByTexture();
        break;
    case PKH::CursorMode::SingleTarget:
        pCursor->SetTexture(L"singletarget");
        pCursor->SetSizeByTexture();
        break;
    default:
        break;
    }
}

void PKH::Cursor::ChangeMode()
{
    switch (pCursor->mode)
    {
    case PKH::CursorMode::Normal:
        SetMode(CursorMode::SingleTarget);
        break;
    case PKH::CursorMode::SingleTarget:
        SetMode(CursorMode::Normal);
        break;
    default:
        break;
    }
}
