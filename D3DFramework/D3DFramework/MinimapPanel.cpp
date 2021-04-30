#include "stdafx.h"
#include "MinimapPanel.h"
#include "MiniMapRenderer.h"
#include "Champion.h"
#include "UIRenderer.h"
#include "TestScene.h"
#include "Minion.h"

MinimapPanel* self = nullptr;

MinimapPanel::MinimapPanel()
{
    int screenW = MainGame::GetWidth();
    int screenH = MainGame::GetHeight();
    
    border = CreateChild(L"minimapBorder", Vector2(0, 0));
    Vector2 borderSize = border->GetSize();
    this->SetLocation(screenW - borderSize.x, screenH - borderSize.y);

    minimap = CreateChild(L"map11", Vector2(20, 12));
    MinimapRenderer* minimapRenderer = new MinimapRenderer(minimap);
    minimapRenderer->SetMesh((Mesh*) minimap->GetComponent(L"Mesh") );
    delete  minimap->GetComponent(L"renderer");
    minimap->RemoveComponent(L"renderer");
    minimap->AddComponent(L"renderer", minimapRenderer);
    minimap->transform->scale = { 0.5625f,0.5625f, 1.f };

    minimap->Click += Engine::Handler(this, &MinimapPanel::Minimap_MouseClick);
    minimap->Click += Engine::Handler(Static_Minimap_MouseClick);

    UIRenderer* renderer = nullptr;
    for (int i = (INT)UnitID::Champ9 + 1; i < (INT)UnitID::END; ++i)
    {
        mapicon.emplace(i, nullptr);

        switch (i)
        {
        case (INT)UnitID::TurretBlueBot1:
        case (INT)UnitID::TurretBlueBot2:
        case (INT)UnitID::TurretBlueBot3:
        case (INT)UnitID::TurretBlueMid1:
        case (INT)UnitID::TurretBlueMid2:
        case (INT)UnitID::TurretBlueMid3:
        case (INT)UnitID::TurretBlueTop1:
        case (INT)UnitID::TurretBlueTop2:
        case (INT)UnitID::TurretBlueTop3:
        case (INT)UnitID::TurretBlueTwin1:
        case (INT)UnitID::TurretBlueTwin2:
        case (INT)UnitID::TurretRedBot1:
        case (INT)UnitID::TurretRedBot2:
        case (INT)UnitID::TurretRedBot3:
        case (INT)UnitID::TurretRedMid1:
        case (INT)UnitID::TurretRedMid2:
        case (INT)UnitID::TurretRedMid3:
        case (INT)UnitID::TurretRedTop1:
        case (INT)UnitID::TurretRedTop2:
        case (INT)UnitID::TurretRedTop3:
        case (INT)UnitID::TurretRedTwin1:
        case (INT)UnitID::TurretRedTwin2:
            mapicon[i] = minimap->AddChild<UI>(L"tower", new UI(L"icon_ui_tower_minimap", Vector2(0, 0)));
            mapicon[i]->transform->scale = { 1.3f, 1.3f, 1.f };
            renderer = dynamic_cast<UIRenderer*>(mapicon[i]->GetComponent(L"renderer"));
            renderer->SetPass(3);

            break;

        case (INT)UnitID::InhibitorBlueBot:
        case (INT)UnitID::InhibitorBlueMid:
        case (INT)UnitID::InhibitorBlueTop:
        case (INT)UnitID::InhibitorRedBot:
        case (INT)UnitID::InhibitorRedMid:
        case (INT)UnitID::InhibitorRedTop:
            mapicon[i] = minimap->AddChild<UI>(L"inhibitor", new UI(L"icon_ui_inhibitor_minimap_v2", Vector2(0, 0)));
            mapicon[i]->transform->scale = { 1.3f, 1.3f, 1.f };
            renderer = dynamic_cast<UIRenderer*>(mapicon[i]->GetComponent(L"renderer"));
            renderer->SetPass(3);
        
            break;
        
        case (INT)UnitID::NexusBlue:
        case (INT)UnitID::NexusRed:
            mapicon[i] = minimap->AddChild<UI>(L"nexus", new UI(L"icon_ui_nexus_minimap_v2", Vector2(0, 0)));
            mapicon[i]->transform->scale = { 1.3f, 1.3f, 1.f };
            renderer = dynamic_cast<UIRenderer*>(mapicon[i]->GetComponent(L"renderer"));
            renderer->SetPass(3);
        
            break;
        
        case (INT)UnitID::Red1:
        case (INT)UnitID::Red2:
        case (INT)UnitID::Blue1:
        case (INT)UnitID::Blue2:
            mapicon[i] = minimap->AddChild<UI>(L"camp", new UI(L"camp", Vector2(0, 0)));
            mapicon[i]->transform->scale = { 2.0f, 2.0f, 1.f };
            renderer = dynamic_cast<UIRenderer*>(mapicon[i]->GetComponent(L"renderer"));
            break;
        
        case (INT)UnitID::Murkwolf1:
        case (INT)UnitID::Murkwolf2:
        case (INT)UnitID::Gromp1:
        case (INT)UnitID::Gromp2:
        case (INT)UnitID::Razorbeak1:
        case (INT)UnitID::Razorbeak2:
        case (INT)UnitID::Krug1:
        case (INT)UnitID::Krug2:
        case (INT)UnitID::Scuttleracer1:
        case (INT)UnitID::Scuttleracer2:
            mapicon[i] = minimap->AddChild<UI>(L"jungle", new UI(L"lesser_jungle_icon_v2", Vector2(0, 0)));
            mapicon[i]->transform->scale = { 1.3f, 1.3f, 1.f };
            renderer = dynamic_cast<UIRenderer*>(mapicon[i]->GetComponent(L"renderer"));
            break;
        }
    }

    for (int i = (INT)UnitID::Champ0; i < (INT)UnitID::Champ9; ++i)
    {
        mapicon.emplace(i, nullptr);

        mapicon[i] = minimap->AddChild<UI>(L"champFace", new UI(L"empty_circle", Vector2(0, 0)));
        mapicon[i]->transform->scale = { 0.5f, 0.5f, 1.f };
        mapicon[i]->Hide();
    }
    //towerRenderer->SetMultipleColor(255, 231, 72, 47); // Red
    //towerRenderer->SetMultipleColor(255, 86, 144, 206); // Blue
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
    
    // 맵 크기
    //Vector2 lb{ 50, 47 };
    //Vector2 rt{ -42, -45 };
    Vector2 lb{ 42, 11 };
    Vector2 rt{ -11, -42 };

    // minimap
    Vector2 minimapSize = minimap->GetSize();

    // Unit
    auto unitMap = dynamic_cast<TestScene*>(SceneManager::GetCurrentScene())->unitMap;

    for (int i = 0; i < (INT)UnitID::END; ++i)
    {
        if (mapicon[i] == nullptr) {
            continue;
        }

        auto unit = unitMap[i];

        if (unit == nullptr ||
            unit->IsDead()) {
            mapicon[i]->Hide();
            continue;
        }

        mapicon[i]->Show();

        // Champion Face
        auto champion = dynamic_cast<Champion*>(unit);
        if (champion) {
            mapicon[i]->SetTexture(champion->faceCircleTexkey);
        }

        // Position
        Vector3 pos = unit->transform->position;
        pos.x = ((pos.x - lb.x) * -1) / ((rt.x - lb.x) * -1) * minimapSize.x;
        pos.z = ((pos.z - rt.y) * 1) / ((lb.y - rt.y) * 1) * minimapSize.y;
        pos.x -= mapicon[i]->GetSize().x * 0.5f;
        pos.z -= mapicon[i]->GetSize().y * 0.5f;
        mapicon[i]->SetLocation(Vector2(pos.x, pos.z));

        // Team Color
        auto renderer = dynamic_cast<UIRenderer*>(mapicon[i]->GetComponent(L"renderer"));
        auto team = unit->GetTeam();
        switch (team)
        {
        case Team::RED:  renderer->SetMultipleColor(255, 231, 72, 47);
            break;
        case Team::BLUE: renderer->SetMultipleColor(255, 86, 144, 206);
            break;
        default:         renderer->SetMultipleColor(255, 231, 158, 49);
            break;
        }
    }
    
    // Minion
    size_t minionNum = Minion::minionList.size();
    size_t minionUINum = mapiconMinion.size();
    if (minionNum > minionUINum) // 생성
    {
        for (int i = 0; i < minionNum - minionUINum; ++i)
        {
            auto minionUI = minimap->AddChild<UI>(L"minion", new UI(L"minionmapcircle", Vector2(0, 0)));
            minionUI->transform->scale = { 2.f, 2.f, 1.f };

            auto renderer = dynamic_cast<UIRenderer*>(minionUI->GetComponent(L"renderer"));
            renderer->SetPass(3);

            mapiconMinion.push_back(minionUI);
        }
    }
    // 삭제는 굳이X
    list<UI*>::iterator iter = mapiconMinion.begin();
    int i = 0;
    for (auto minion : Minion::minionList)
    {
        (*iter)->Show();

        Vector3 pos = minion->transform->position;
        
        pos.x = ((pos.x - lb.x) * -1) / ((rt.x - lb.x) * -1) * minimapSize.x;
        pos.z = ((pos.z - rt.y) *  1) / ((lb.y - rt.y) *  1) * minimapSize.y;
        pos.x += (*iter)->GetSize().x * 0.5f;
        pos.z += (*iter)->GetSize().y * 0.5f;
        (*iter)->SetLocation(Vector2(pos.x, pos.z));

        // Team Color
        auto renderer = dynamic_cast<UIRenderer*>((*iter)->GetComponent(L"renderer"));
        auto team = minion->GetTeam();
        switch (team)
        {
        case Team::RED:  renderer->SetMultipleColor(255, 231, 72, 47);
            break;
        case Team::BLUE: renderer->SetMultipleColor(255, 86, 144, 206);
            break;
        default:         renderer->SetMultipleColor(255, 231, 158, 49);
            break;
        }

        ++iter;
        ++i;
    }
    for (;iter != mapiconMinion.end(); ++iter)
    {
        (*iter)->Hide();
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
