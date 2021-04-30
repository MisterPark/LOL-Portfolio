#include "stdafx.h"
#include "KillCalloutPanel.h"
#include "KillCalloutUI.h"

KillCalloutPanel* self = nullptr;

KillCalloutPanel::KillCalloutPanel()
{
    int screenW = MainGame::GetWidth();
    int screenH = MainGame::GetHeight();
}

KillCalloutPanel::~KillCalloutPanel()
{
}

KillCalloutPanel* KillCalloutPanel::GetInstance()
{
    if (self == nullptr)
    {
        self = new KillCalloutPanel();
    }
    return self;
}

void KillCalloutPanel::DestroyInstance()
{
    if (self)
    {
        delete self;
        self = nullptr;
    }
}

void KillCalloutPanel::Update()
{
    UI::Update();

    int screenW = MainGame::GetWidth();
    int screenH = MainGame::GetHeight();

    if (!IsVisible()) return;

    size_t size = killList.size();
    if (size == 0) return;

    int idx = 0;
    Vector2 uiSize = (*killList.begin())->GetSize();
    Vector2 startPos = { screenW - uiSize.x, screenH * 0.2f };
    Vector2 lastPos = startPos;

    auto iter = killList.begin();
    while(iter != killList.end()) {
        lastPos.y = startPos.y + (idx * (uiSize.y + 15));
        auto ui = (*iter);
        if (ui->IsEnd()) {
            KillCalloutUI* child = RemoveChild(ui);
            if (child != nullptr)
                delete child;
            iter = killList.erase(iter);
            continue;
        }
        else {
            Vector2 pos = (*iter)->GetLocation();

            pos.x = pos.x + ((lastPos.x - pos.x) * 0.5f);
            pos.y = pos.y + ((lastPos.y - pos.y) * 0.5f);
            ui->SetLocation(pos);
        }
        ++iter;
        ++idx;
    }
}

void KillCalloutPanel::AddKillCallout(const std::wstring _faceL, const std::wstring _faceR, Team _team)
{
    int screenW = MainGame::GetWidth();
    int screenH = MainGame::GetHeight();

    auto ui = AddChild<KillCalloutUI>(L"killcalloutUI", new KillCalloutUI(_faceL, _faceR, _team));
    Vector2 uiSize = ui->GetSize();

    size_t size = killList.size();

    Vector2 pos = { screenW - uiSize.x, screenH * 0.2f }; // StartPos

    pos.x -= 50;
    pos.y += size * (uiSize.y + 15);

    ui->SetLocation(pos);

    killList.push_back(ui);
}
