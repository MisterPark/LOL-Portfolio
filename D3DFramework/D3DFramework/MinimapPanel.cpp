#include "stdafx.h"
#include "MinimapPanel.h"

MinimapPanel* self = nullptr;

MinimapPanel::MinimapPanel()
{
    int screenW = MainGame::GetWidth();
    int screenH = MainGame::GetHeight();
    
    UI* border = AddChild(L"minimapBorder", Vector2(0, 0));
    Vector2 borderSize = border->GetSize();
    this->SetLocation(screenW - borderSize.x, screenH - borderSize.y);

    UI* minimap = AddChild(L"map11", Vector2(20, 12));
    minimap->transform->scale = { 0.5625f,0.5625f, 1.f };
    

    

    minimap->Click += TestFunc;
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
