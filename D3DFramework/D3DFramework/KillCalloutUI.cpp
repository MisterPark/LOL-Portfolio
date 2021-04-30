#include "stdafx.h"
#include "KillCalloutUI.h"

KillCalloutUI::KillCalloutUI(const std::wstring& _faceL, const std::wstring& _faceR, const Team _team)
{
    background = AddChild(L"background", new UI(L"killcallout_back"));
    auto renderer = dynamic_cast<UIRenderer*>(background->GetComponent(L"renderer"));
    renderer->SetPass(3);
    switch (_team)
    {
    case Team::RED:  renderer->SetMultipleColor(255, 231, 72, 47); // Red
        break;
    case Team::BLUE: renderer->SetMultipleColor(255, 86, 144, 206); // Blue
        break;
    default:         renderer->SetMultipleColor(255, 231, 158, 49); // Yellow
        break;
    }
    
    icon = AddChild(L"icon", new UI(L"killcallout_icon"));
    Vector2 iconSize = icon->GetSize();
    icon->SetLocation(111 - (iconSize.x * 0.5f), 32 - (iconSize.y * 0.5f));

    faceL = AddChild(L"faceL", new UI(_faceL));
    faceL->transform->scale = { 0.32f, 0.32f, 1.f };
    Vector2 faceLSize = faceL->GetSize();
    faceL->SetLocation(74 - (faceLSize.x * 0.5f), 32 - (faceLSize.y * 0.5f));

    faceR = AddChild(L"faceR", new UI(_faceR));
    faceR->transform->scale = { 0.32f, 0.32f, 1.f };
    Vector2 faceRSize = faceR->GetSize();
    faceR->SetLocation(148 - (faceRSize.x * 0.5f), 32 - (faceRSize.y * 0.5f));
}

KillCalloutUI::~KillCalloutUI()
{
}

void KillCalloutUI::Update()
{
    UI::Update();

    if (!IsVisible()) return;

    tick += Time::DeltaTime();

    alpha += 2 * Time::DeltaTime();
    if (alpha > 1.f) alpha = 1.f;

    SetAlpha(alpha);
}

Vector2 KillCalloutUI::GetSize()
{
    return background->GetSize();
}

void KillCalloutUI::SetAlpha(float _alpha)
{
    for (auto child : children)
    {
        auto renderer = dynamic_cast<UIRenderer*>(child.second->GetComponent(L"renderer"));
        if (renderer == nullptr) continue;

        renderer->SetAlpha(_alpha);
    }
}

bool KillCalloutUI::IsEnd()
{
    return tick > duration;
}
