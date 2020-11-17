#include "stdafx.h"
#include "UI_Title.h"

UI_Title::UI_Title()
{
	Initialize();
	//textureKey = TextureKey::UI_TITLE_SCREEN;
}

UI_Title::~UI_Title()
{
	Release();
}

void UI_Title::Initialize()
{
	//transform->scale = { (float)dfCLIENT_WIDTH / dfCLIENT_HEIGHT,1,1 };

}

void UI_Title::Release()
{
}

void UI_Title::OnHover()
{
	UI::OnHover();
}

void UI_Title::OnLeave()
{
	UI::OnLeave();
}

void UI_Title::OnLButtonDown()
{
	UI::OnLButtonDown();
}

void UI_Title::OnLButtonUp()
{
	UI::OnLButtonUp();
}

void UI_Title::OnClick()
{
	UI::OnClick();
}

void UI_Title::SetTexture(TextureKey _key)
{
	textureKey = _key;
}


void UI_Title::UpdateUI()
{
}
