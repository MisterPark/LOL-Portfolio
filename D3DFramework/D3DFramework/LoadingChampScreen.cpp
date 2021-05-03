#include "stdafx.h"
#include "LoadingChampScreen.h"
#include "LoadingBorder.h"
#include "LoadingChampPanel.h"
#include "LoadingPanel.h"
#include "UI_Spell.h"
#include "Label.h"

LoadingChampScreen::LoadingChampScreen()
{
	champ = new LoadingChampPanel;
	mask = new LoadingPanel;
	border = new LoadingBorder;
	spell1 = new UI_Spell;
	spell2 = new UI_Spell;
	champName = new Label(20);
	nickName = new Label(20);
	progressLabel = new Label(20);
	champName->SetColor(255, 250, 250, 250);
	nickName->SetColor(255, 250, 250, 250);
	progressLabel->SetColor(255, 0, 250, 0);

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
//
//void LoadingChampScreen::Render()
//{
//	GameObject::Render();
//	champ->Render();
//	mask->Render();
//	spell1->Render();
//	spell2->Render();
//	border->Render();
//	champName->Render();
//	nickName->Render();
//	progressLabel->Render();
//}

void LoadingChampScreen::SetChampion(ChampionType type)
{
	switch (type)
	{
	case ChampionType::Garen:
		champName->SetText(L"가렌");
		champ->SetTexture(L"garenloadscreen");
		break;
	case ChampionType::Darius:
		champName->SetText(L"다리우스");
		champ->SetTexture(L"dariusloadscreen");
		break;
	case ChampionType::Diana:
		champName->SetText(L"다이애나");
		champ->SetTexture(L"dianaloadscreen");
		break;
	case ChampionType::Leona:
		champName->SetText(L"레오나");
		champ->SetTexture(L"leonaloadscreen");
		break;
	case ChampionType::Leesin:
		champName->SetText(L"리 신");
		champ->SetTexture(L"leesinloadscreen");
		break;
	case ChampionType::Missfortune:
		champName->SetText(L"미스포츈");
		champ->SetTexture(L"missfortuneloadscreen");
		break;
	case ChampionType::Blitzcrank:
		champName->SetText(L"블리츠크랭크");
		champ->SetTexture(L"blitzcrankloadscreen");
		break;
	case ChampionType::Ahri:
		champName->SetText(L"아리");
		champ->SetTexture(L"ahriloadscreen");
		break;
	case ChampionType::Jax:
		champName->SetText(L"잭스");
		champ->SetTexture(L"jaxloadscreen");
		break;
	case ChampionType::Jinx:
		champName->SetText(L"징크스");
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
