#include "stdafx.h"
#include "Cursor.h"

PKH::Cursor* pCursor = nullptr;

PKH::Cursor::Cursor()
{
    isVisible = false;
}

PKH::Cursor::~Cursor()
{
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
    pos.x = pt.x;
    pos.y = pt.y;
    return pos;
}

void PKH::Cursor::Show()
{
    if (pCursor->isShow) return;

    ShowCursor(TRUE);
}

void PKH::Cursor::Hide()
{
    if (pCursor->isShow == false) return;

    ShowCursor(FALSE);
}

void PKH::Cursor::Update()
{
    if (isEnable == false)return;
    transform->position = GetMousePos();
}

void PKH::Cursor::Render()
{
    if (isVisible == false)return;
    D2DRenderManager::DrawSprite(TextureKey::CURSOR_TARGET, *transform, 0);
}
