#include "stdafx.h"
#include "MinimapPanel.h"

MinimapPanel* self = nullptr;

MinimapPanel::MinimapPanel()
{
    int screenW = MainGame::GetWidth();
    int screenH = MainGame::GetHeight();
    this->SetLocation(0, 0);

    UI* border = AddChild(L"map11", Vector2(100, 100));
    border->AddChild(L"minimapBorder", Vector2(100, 100));

    Click += TestFunc;
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

void MinimapPanel::TestFunc()
{
    Debug::PrintLine("테스트");
}
