#include "stdafx.h"
#include "MinimapPanel.h"

MinimapPanel* self = nullptr;

MinimapPanel::MinimapPanel()
{
    SetTexture(L"minimapBorder");
    int screenW = MainGame::GetWidth();
    int screenH = MainGame::GetHeight();
    this->SetSize(100, 100);
    this->SetLocation(screenW - width-10, screenH - height-10);
}

MinimapPanel::~MinimapPanel()
{
}

MinimapPanel* MinimapPanel::GetInstance()
{
    if (self == nullptr)
    {
        self = new MinimapPanel();
    }
    return self;
}

void MinimapPanel::Destroy()
{
    if (self)
    {
        delete self;
        self = nullptr;
    }
}
