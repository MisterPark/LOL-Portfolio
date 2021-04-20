#include "stdafx.h"
#include "EndofgamePanel.h"
#include "Button.h"

EndofgamePanel* self = nullptr;

EndofgamePanel::EndofgamePanel()
{
    int screenW = MainGame::GetWidth();
    int screenH = MainGame::GetHeight();

    auto victoryBackTex = RenderManager::GetTexture(L"eog_base");
    auto defeatBackTex = RenderManager::GetTexture(L"eog_defeat_base");
    auto btnContinueTex = RenderManager::GetTexture(L"eog_btn_default");

    victoryBack = AddChild<UI>(L"victoryBack", new UI(L"eog_base", Vector2((screenW * 0.5f) - (victoryBackTex->GetSpriteWidth() * 0.5f), (screenH * 0.4f) - (victoryBackTex->GetSpriteHeight() * 0.5f))));
    victoryFont = victoryBack->AddChild<UI>(L"victoryFont", new UI(L"eog_victory", Vector2(0, 0)));
    defeatBack = AddChild<UI>(L"defeatBack", new UI(L"eog_defeat_base", Vector2((screenW * 0.5f) - (defeatBackTex->GetSpriteWidth() * 0.5f), (screenH * 0.4f) - (defeatBackTex->GetSpriteHeight() * 0.5f))));
    defeatFont = defeatBack->AddChild<UI>(L"defeatFont", new UI(L"eog_defeat", Vector2(0, 0)));

    btnContinue = AddChild<Button>(L"btnContinue", new Button(L"eog_btn_default", Vector2((screenW * 0.5f) - (btnContinueTex->GetSpriteWidth() * 0.5f), (screenH * 0.6f) - (btnContinueTex->GetSpriteHeight() * 0.5f))));
    btnContinue->SetText(L"계속");
    btnContinue->SetLabelSize(15);
    btnContinue->SetLabelPosition(Vector2(btnContinueTex->GetSpriteWidth() * 0.5f, btnContinueTex->GetSpriteHeight() * 0.5f));
    btnContinue->SetLabelAlign(Label::Align::Center);
    btnContinue->SetLabelVAlign(Label::VAlign::Middle);
    btnContinue->SetLabelColor(D3DCOLOR_ARGB(255, 253, 221, 211));
    btnContinue->SetTextureHover(L"eog_btn_hover");
    btnContinue->SetTexturePressed(L"eog_btn_pressed");
    btnContinue->SetTextureDisable(L"eog_btn_disabled");
    //btnContinue->Click += Engine::Handler(this, &씬전환함수);

}

EndofgamePanel::~EndofgamePanel()
{
}

EndofgamePanel* EndofgamePanel::GetInstance()
{
    if (self == nullptr)
    {
        self = new EndofgamePanel();
    }
    return self;
}

void EndofgamePanel::DestroyInstance()
{
    if (self)
    {
        delete self;
        self = nullptr;
    }
}

void EndofgamePanel::ShowVictory()
{
    victoryBack->Show();
    //victoryFont->Show();
    defeatBack->Hide();
    //defeatFont->Hide();
    btnContinue->Show();
}

void EndofgamePanel::ShowDefeat()
{
    victoryBack->Hide();
    //victoryFont->Hide();
    defeatBack->Show();
    //defeatFont->Show();
    btnContinue->Show();
}
