#include "stdafx.h"
#include "LoadingChampScreen.h"
#include "LoadingBorder.h"
#include "LoadingChampPanel.h"
#include "LoadingPanel.h"
#include "UI_Spell.h"
#include "Label.h"

LoadingChampScreen::LoadingChampScreen()
{
	border = new LoadingBorder;
	champ = new LoadingChampPanel;
	mask = new LoadingPanel;
	spell1 = new UI_Spell;
	spell2 = new UI_Spell;
	champName = new Label(20);
	nickName = new Label(20);
	progressLabel = new Label(20);
	champName->foreColor = D3DCOLOR_ARGB(255, 250, 250, 250);
	nickName->foreColor = D3DCOLOR_ARGB(255, 250, 250, 250);
	progressLabel->foreColor = D3DCOLOR_ARGB(255, 0, 250, 0);
}

LoadingChampScreen::~LoadingChampScreen()
{
	delete border;
	delete champ;
	delete mask;
	delete spell1;
	delete spell2;
	delete champName;
	delete nickName;
	delete progressLabel;
}

void LoadingChampScreen::Initialize()
{
}

void LoadingChampScreen::Release()
{
}

void LoadingChampScreen::Update()
{
	GameObject::Update();
	border->Update();
	champ->Update();
	mask->Update();
	spell1->Update();
	spell2->Update();
	champName->Update();
	nickName->Update();
	progressLabel->Update();
}

void LoadingChampScreen::Render()
{
	GameObject::Render();
	champ->Render();
	mask->Render();
	spell1->Render();
	spell2->Render();
	border->Render();
	champName->Render();
	nickName->Render();
	progressLabel->Render();
}

void LoadingChampScreen::SetChampion(ChampionType type)
{
	switch (type)
	{
	case ChampionType::Garen:
		champName->text = L"가렌";
		champ->SetTexture(L"garenloadscreen");
		break;
	case ChampionType::Darius:
		champName->text = L"다리우스";
		champ->SetTexture(L"dariusloadscreen");
		break;
	case ChampionType::Diana:
		champName->text = L"다이애나";
		champ->SetTexture(L"dianaloadscreen");
		break;
	case ChampionType::Leona:
		champName->text = L"레오나";
		champ->SetTexture(L"leonaloadscreen");
		break;
	case ChampionType::Leesin:
		champName->text = L"리 신";
		champ->SetTexture(L"leesinloadscreen");
		break;
	case ChampionType::Missfortune:
		champName->text = L"미스포츈";
		champ->SetTexture(L"missfortuneloadscreen");
		break;
	case ChampionType::Blitzcrank:
		champName->text = L"블리츠크랭크";
		champ->SetTexture(L"blitzcrankloadscreen");
		break;
	case ChampionType::Ahri:
		champName->text = L"아리";
		champ->SetTexture(L"ahriloadscreen");
		break;
	case ChampionType::Amumu:
		champName->text = L"아무무";
		champ->SetTexture(L"amumuloadscreen");
		break;
	case ChampionType::Jinx:
		champName->text = L"징크스";
		champ->SetTexture(L"jinxloadscreen");
		break;
	default:
		break;
	}
}

void LoadingChampScreen::SetSpell1(SpellType type)
{
	switch (type)
	{
	case SpellType::Barrier:
		spell1->SetTexture(L"summoner_barrier");
		break;
	case SpellType::Boost:
		spell1->SetTexture(L"summoner_boost");
		break;
	case SpellType::Exhaust:
		spell1->SetTexture(L"summoner_exhaust");
		break;
	case SpellType::Flash:
		spell1->SetTexture(L"summoner_flash");
		break;
	case SpellType::Haste:
		spell1->SetTexture(L"summoner_haste");
		break;
	case SpellType::Heal:
		spell1->SetTexture(L"summoner_heal");
		break;
	case SpellType::Ignite:
		spell1->SetTexture(L"summoner_ignite");
		break;
	case SpellType::Mana:
		spell1->SetTexture(L"summoner_mana");
		break;
	case SpellType::Smite:
		spell1->SetTexture(L"summoner_smite");
		break;
	case SpellType::Teleport:
		spell1->SetTexture(L"summoner_teleport");
		break;
	default:
		break;
	}
}

void LoadingChampScreen::SetSpell2(SpellType type)
{
	switch (type)
	{
	case SpellType::Barrier:
		spell2->SetTexture(L"summoner_barrier");
		break;
	case SpellType::Boost:
		spell2->SetTexture(L"summoner_boost");
		break;
	case SpellType::Exhaust:
		spell2->SetTexture(L"summoner_exhaust");
		break;
	case SpellType::Flash:
		spell2->SetTexture(L"summoner_flash");
		break;
	case SpellType::Haste:
		spell2->SetTexture(L"summoner_haste");
		break;
	case SpellType::Heal:
		spell2->SetTexture(L"summoner_heal");
		break;
	case SpellType::Ignite:
		spell2->SetTexture(L"summoner_ignite");
		break;
	case SpellType::Mana:
		spell2->SetTexture(L"summoner_mana");
		break;
	case SpellType::Smite:
		spell2->SetTexture(L"summoner_smite");
		break;
	case SpellType::Teleport:
		spell2->SetTexture(L"summoner_teleport");
		break;
	default:
		break;
	}
}
