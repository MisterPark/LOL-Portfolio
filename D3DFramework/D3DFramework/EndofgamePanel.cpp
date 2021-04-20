#include "stdafx.h"
#include "EndofgamePanel.h"
#include "Button.h"
#include "Animation2D.h"

EndofgamePanel* self = nullptr;

EndofgamePanel::EndofgamePanel()
{
    int screenW = MainGame::GetWidth();
    int screenH = MainGame::GetHeight();

    auto victoryBackTex = RenderManager::GetTexture(L"eog_base");
    auto defeatBackTex = RenderManager::GetTexture(L"eog_defeat_base");
    auto btnContinueTex = RenderManager::GetTexture(L"eog_btn_default");

    victoryBack = AddChild<UI>(L"victoryBack", new UI(L"eog_base", Vector2((screenW * 0.5f) - (victoryBackTex->GetSpriteWidth() * 0.5f), (screenH * 0.4f) - (victoryBackTex->GetSpriteHeight() * 0.5f))));
    defeatBack = AddChild<UI>(L"defeatBack", new UI(L"eog_defeat_base", Vector2((screenW * 0.5f) - (defeatBackTex->GetSpriteWidth() * 0.5f), (screenH * 0.4f) - (defeatBackTex->GetSpriteHeight() * 0.5f))));


    backeffect.push_back(AddChild<UI>(L"backeffect1", new UI(L"eog_fb_color_01_01", Vector2(507, 24))));
    backeffect[0]->transform->scale = { 1.32f, 1.32f, 1.f };
    backeffect[0]->GetComponent<UIRenderer>()->SetGradientMap(L"eog_gradientmap", 4, 1);
    Animation2D* ani0 = dynamic_cast<Animation2D*>(backeffect[0]->AddComponent(L"Animation2D", new Animation2D(backeffect[0])));
    ani0->SetMesh(backeffect[0]->mesh);
    ani0->SetSprite(RenderManager::GetTextureID(L"eog_fb_color_01_01"), RenderManager::GetTextureID(L"eog_fb_color_01_17"));
    ani0->SetDelay(0.1f);
    ani0->SetLoop(false);

    backeffect.push_back(AddChild<UI>(L"backeffect2", new UI(L"eog_fb_color_02_01", Vector2(507, 24))));
    backeffect[1]->transform->scale = { 1.32f, 1.32f, 1.f };
    backeffect[1]->GetComponent<UIRenderer>()->SetGradientMap(L"eog_gradientmap", 4, 1);
    Animation2D* ani1 = dynamic_cast<Animation2D*>(backeffect[1]->AddComponent(L"Animation2D", new Animation2D(backeffect[1])));
    ani1->SetMesh(backeffect[1]->mesh);
    ani1->SetSprite(RenderManager::GetTextureID(L"eog_fb_color_02_01"), RenderManager::GetTextureID(L"eog_fb_color_02_17"));
    ani1->SetDelay(0.1f);
    ani1->SetLoop(false);

    backeffect.push_back(AddChild<UI>(L"backeffect3", new UI(L"eog_fb_color_03_01", Vector2(507, 24))));
    backeffect[2]->transform->scale = { 1.32f, 1.32f, 1.f };
    backeffect[2]->GetComponent<UIRenderer>()->SetGradientMap(L"eog_gradientmap", 4, 1);
    Animation2D* ani2 = dynamic_cast<Animation2D*>(backeffect[2]->AddComponent(L"Animation2D", new Animation2D(backeffect[2])));
    ani2->SetMesh(backeffect[2]->mesh);
    ani2->SetSprite(RenderManager::GetTextureID(L"eog_fb_color_03_01"), RenderManager::GetTextureID(L"eog_fb_color_03_12"));
    ani2->SetDelay(0.1f);
    ani2->SetLoop(true);

    victoryFont = victoryBack->AddChild<UI>(L"victoryFont", new UI(L"eog_victory", Vector2(0, 0)));
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

void EndofgamePanel::Update()
{
    UI::Update();

    switch (effectidx) {
    case 0:
        if (backeffect[effectidx]->GetComponent<Animation2D>()->IsEndFrame()) {
            backeffect[effectidx]->Show(false);
            effectidx++;
            backeffect[effectidx]->Show(true);
            backeffect[effectidx]->GetComponent<Animation2D>()->Initialize();
        }
        break;

    case 1:
        if (backeffect[effectidx]->GetComponent<Animation2D>()->IsEndFrame()) {
            backeffect[effectidx]->Show(false);
            effectidx++;
            backeffect[effectidx]->Show(true);
            backeffect[effectidx]->GetComponent<Animation2D>()->Initialize();
            if(isVictory) victoryBack->Show(true);
            else          defeatBack->Show(true);
            btnContinue->Show(true);
        }
        break;

    case 2:
        break;
    }
}

void EndofgamePanel::ShowVictory()
{
    isVictory = true;

    effectidx = 0;

    victoryBack->Show(false);
    defeatBack->Show(false);
    btnContinue->Show(false);
    backeffect[0]->GetComponent<UIRenderer>()->SetGradientMapIndex(1);
    backeffect[1]->GetComponent<UIRenderer>()->SetGradientMapIndex(1);
    backeffect[2]->GetComponent<UIRenderer>()->SetGradientMapIndex(1);

    backeffect[0]->Show(true);
    backeffect[1]->Show(false);
    backeffect[2]->Show(false);

    backeffect[0]->Initialize();
}

void EndofgamePanel::ShowDefeat()
{
    isVictory = false;

    effectidx = 0;

    victoryBack->Show(false);
    defeatBack->Show(false);
    btnContinue->Show(false);
    backeffect[0]->GetComponent<UIRenderer>()->SetGradientMapIndex(2);
    backeffect[1]->GetComponent<UIRenderer>()->SetGradientMapIndex(2);
    backeffect[2]->GetComponent<UIRenderer>()->SetGradientMapIndex(2);

    backeffect[0]->Show(true);
    backeffect[1]->Show(false);
    backeffect[2]->Show(false);

    backeffect[0]->Initialize();
}
