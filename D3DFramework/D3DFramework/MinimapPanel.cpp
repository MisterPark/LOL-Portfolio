#include "stdafx.h"
#include "MinimapPanel.h"
#include "MiniMapRenderer.h"
MinimapPanel* self = nullptr;

MinimapPanel::MinimapPanel()
{
    int screenW = MainGame::GetWidth();
    int screenH = MainGame::GetHeight();
    
    UI* border = CreateChild(L"minimapBorder", Vector2(0, 0));
    Vector2 borderSize = border->GetSize();
    this->SetLocation(screenW - borderSize.x, screenH - borderSize.y);

    UI* minimap = CreateChild(L"map11", Vector2(20, 12));
    MinimapRenderer* renderer = new MinimapRenderer(minimap);
    renderer->SetMesh((Mesh*) minimap->GetComponent(L"Mesh") );
    delete  minimap->GetComponent(L"renderer");
    minimap->RemoveComponent(L"renderer");
    minimap->AddComponent(L"renderer", renderer);
    minimap->transform->scale = { 0.5625f,0.5625f, 1.f };

    minimap->Click += Engine::Handler(this, &MinimapPanel::Minimap_MouseClick);
    minimap->Click += Engine::Handler(Static_Minimap_MouseClick);


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

void MinimapPanel::DestroyInstance()
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

void MinimapPanel::Minimap_MouseClick(GameObject* sender, MouseEventArg* arg)
{
    Debug::PrintLine("테스트1");

}

void MinimapPanel::Static_Minimap_MouseClick(GameObject* sender, MouseEventArg* arg)
{
    Debug::PrintLine("테스트2");
}
