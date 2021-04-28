#include "stdafx.h"
#include "MinimapPanel.h"
#include "MiniMapRenderer.h"
#include "Champion.h"
#include "UIRenderer.h"

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

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            champFace[i].push_back(nullptr);
            champFace[i][j] = minimap->AddChild<UI>(L"champFace", new UI(L"empty_circle", Vector2(0, 0)));
            champFace[i][j]->transform->scale = { 0.5f, 0.5f, 1.f };
            champFace[i][j]->Hide();
        }
    }

    UI* tower = AddChild<UI>(L"tower", new UI(L"icon_ui_tower_minimap", Vector2(0, 0)));
    auto towerRenderer = dynamic_cast<UIRenderer*>(tower->GetComponent(L"renderer"));
    towerRenderer->SetMultipleColor(255, 231, 72, 47); // Red
    //towerRenderer->SetMultipleColor(255, 86, 144, 206); // Blue
    towerRenderer->SetPass(3);
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

void MinimapPanel::Update()
{
    Panel::Update();

    Vector2 size = champFace[0][0]->GetSize();
    for (int i = 0; i < 2; ++i)
    {
        int champnum = champ[i].size();
        for (int j = 0; j < champnum; ++j)
        {
            champFace[i][j]->Show();
            champFace[i][j]->SetTexture(champ[i][j]->faceCircleTexkey);
            champFace[i][j]->SetLocation(Vector2(0, 0));
        }
        for (int j = champnum; j < 5; ++j)
        {
            champFace[i][j]->Hide();
        }
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

void MinimapPanel::AddChampion(Champion* _champ)
{
    Team _team = _champ->GetTeam();
    int _teamidx = _team == Team::BLUE ? 0 : 1;

    if (champ[_teamidx].size() >= 5) return;
    champ[_teamidx].push_back(_champ);
}
