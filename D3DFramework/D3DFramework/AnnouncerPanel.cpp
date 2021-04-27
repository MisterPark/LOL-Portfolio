#include "stdafx.h"
#include "AnnouncerPanel.h"
#include "Label.h"
#include "OutlinedSlot.h"
#include <sstream>

AnnouncerPanel* self = nullptr;

AnnouncerPanel::AnnouncerPanel()
{
	int screenW = MainGame::GetWidth();
	int screenH = MainGame::GetHeight();

	label = AddChild<Label>(L"label", new Label(40));
	label->SetLocation(Vector2(screenW * 0.5f, screenH * 0.2f));
	label->SetText(L"소환사의 협곡에 오신 것을 환영합니다");
	label->SetColor(255, 224, 197, 151);
	label->outline = true;
	label->align = Label::Align::Center;
	label->valign = Label::VAlign::Middle;

	auto underlineTex = RenderManager::GetTexture(L"underline_blue");
	underline = AddChild<UI>(L"underline", new UI(L"underline_blue", Vector2((screenW * 0.5f) - (underlineTex->GetSpriteWidth() * 0.5f), (screenH * 0.2f) + 20.f)));

	auto goldringTex = RenderManager::GetTexture(L"goldring");
	typeone_face = AddChild<OutlinedSlot>(L"typeone_face", new OutlinedSlot(L"goldring", Vector2((screenW * 0.5f) - (goldringTex->GetSpriteWidth() * 0.5f), (screenH * 0.2f) - 120.f)));
	typeone_face->SetIcon(L"garen_circle");
	typeone_face->icon->SetLocation(Vector2(24, 14));
	typeone_face->icon->transform->scale = { 0.6f, 0.6f, 1.f };

	typetwoL_face = AddChild<OutlinedSlot>(L"typetwoL_face", new OutlinedSlot(L"goldring", Vector2(0, 0)));
	typetwoL_face->SetIcon(L"garen_circle");
	typetwoL_face->icon->SetLocation(Vector2(24, 14));
	typetwoL_face->icon->transform->scale = { 0.6f, 0.6f, 1.f };

	typetwoR_face = AddChild<OutlinedSlot>(L"typetwoR_face", new OutlinedSlot(L"goldring", Vector2(0, 0)));
	typetwoR_face->SetIcon(L"garen_circle");
	typetwoR_face->icon->SetLocation(Vector2(24, 14));
	typetwoR_face->icon->transform->scale = { 0.6f, 0.6f, 1.f };
}

AnnouncerPanel::~AnnouncerPanel()
{
}

AnnouncerPanel* AnnouncerPanel::GetInstance()
{
	if (self == nullptr)
	{
		self = new AnnouncerPanel();
	}
	return self;
}

void AnnouncerPanel::DestroyInstance()
{
	Safe_Delete(&self);
}

void AnnouncerPanel::Update()
{
	Panel::Update();

	int num = data.size();

	Hide();

	if (num > 0)
	{
		AnnouncerData& currData = data.front();

		// 출력
		// 텍스트
		label->SetText(currData.string);

		// 팀
		if ((INT)currData.team == (INT)Team::RED)
			underline->SetTexture(L"underline_red");
		else
			underline->SetTexture(L"underline_blue");

		label->Show();
		underline->Show();

		if (currData.type == AnnounceType::None)
		{

		}
		else if (currData.type == AnnounceType::One)
		{
			typeone_face->Show(true);

			typeone_face->icon->SetText(currData.face1);
		}
		else if (currData.type == AnnounceType::Two)
		{
			typetwoL_face->Show();
			typetwoR_face->Show();

			typetwoL_face->icon->SetTexture(currData.face1);
			typetwoR_face->icon->SetTexture(currData.face2);

			int screenW = MainGame::GetWidth();
			int screenH = MainGame::GetHeight();
			int labelwidth = label->GetDrawTextWidth();
			auto goldringTex = RenderManager::GetTexture(L"goldring");

			typetwoL_face->SetLocation((screenW * 0.5f) - (goldringTex->GetSpriteWidth() * 0.5f) - ((labelwidth * 0.5f) + 60.f), (screenH * 0.2f) - (goldringTex->GetSpriteHeight() * 0.5f));
			typetwoR_face->SetLocation((screenW * 0.5f) - (goldringTex->GetSpriteWidth() * 0.5f) + ((labelwidth * 0.5f) + 60.f), (screenH * 0.2f) - (goldringTex->GetSpriteHeight() * 0.5f));
		}
		
		// Sound
		if (!currData.soundPlay) {
			currData.soundPlay = true;
			SoundManager::GetInstance()->PlaySoundW(currData.soundKey.c_str(), SoundChannel::ANNOUNCER);
		}

		tick += Time::DeltaTime();

		if (num == 1)
		{
			if (maxHoldTime < tick) {
				data.pop_front();
				tick = 0;
			}
		}
		else if (num > 1)
		{
			if (minHoldTime < tick) {
				data.pop_front();
				tick = 0;
			}
		}
	}
}

void AnnouncerPanel::AddAnnouncer(const std::wstring& _str, Team _team, const std::wstring _soundKey)
{
	AnnouncerData _data{ AnnounceType::None, _str, _soundKey, _team };
	data.push_back(_data);
}

void AnnouncerPanel::AddAnnouncer(const std::wstring& _str, Team _team, const std::wstring _soundKey, const std::wstring& _face1)
{
	AnnouncerData _data{ AnnounceType::One, _str, _soundKey, _team, _face1 };
	data.push_back(_data);
}

void AnnouncerPanel::AddAnnouncer(const std::wstring& _str, Team _team, const std::wstring _soundKey, const std::wstring& _face1, const std::wstring& _face2)
{
	AnnouncerData _data{ AnnounceType::Two, _str, _soundKey, _team, _face1, _face2 };
	data.push_back(_data);
}
