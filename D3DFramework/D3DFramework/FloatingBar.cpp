#include "stdafx.h"
#include "FloatingBar.h"
#include "Label.h"
FloatingBar::FloatingBar()
{

	offset = { 0,1.8f,-0.5f };
	offset2 = { -42,-9,0 };
	offsetMP = { -42,5,0 };

	scaleHP = { 0.97f,1.f,1.f };
	scaleMP = { 0.97f,0.3f,1.f };
	//mesh = (PKH::Rectangle*)AddComponent<PKH::Rectangle>(L"Mesh");
	//mesh->SetTexture(L"border_float (1)");
	//mesh->SetBlendMode(BlendMode::ALPHA_TEST);

	//Texture* tex = RenderManager::GetTexture(L"border_float (1)");
	//int w = tex->GetSpriteWidth();
	//int h = tex->GetSpriteHeight();
	//float scaleY = (float)h / w;
	//transform->scale = { 1,scaleY,1 };

	SetTexture(L"border_float (1)");
	textureKeyHP = L"bar_float (2)";
	textureKeyMP = L"bar_float (5)";
	////SetSizeByTexture();
	//SetSize(1000, 100);
	//mesh->SetBlendMode(BlendMode::ALPHA_BLEND);

	nicknameLabel = new Label();
	nicknameLabel->foreColor = D3DCOLOR_ARGB(255, 254, 254, 254);
	nicknameLabel->align = Label::Align::Center;

}

FloatingBar::~FloatingBar()
{
	Safe_Delete(&nicknameLabel);
	target = nullptr;

}

void FloatingBar::Initialize()
{
}

void FloatingBar::Release()
{
}

void FloatingBar::Update()
{
	if (target->IsDestroy())
	{
		target = nullptr;
	}

	if (target != nullptr)
	{
		isVisible = !target->IsDead();

		Vector3 worldPos = target->transform->position + offset;
		worldPos = Camera::main->WorldToScreenPoint(worldPos);
		transform->position = worldPos;
		nicknameLabel->transform->position = worldPos + Vector3(0, -35, 0);
	}
	
	nicknameLabel->Update();
	//UI::Update();
	GameObject::Update();

	//Billboard();

	
}

void FloatingBar::SetTarget(Unit* target)
{
	this->target = target;
}

void FloatingBar::SetTexture(const wstring& _textureKey)
{
	textureKey = _textureKey;
}

void FloatingBar::SetTextureHP(const wstring& _textureKey)
{
	textureKeyHP = _textureKey;
}

void FloatingBar::SetTextureMP(const wstring& _textureKey)
{
	textureKeyMP = _textureKey;
}

void FloatingBar::SetNickname(const wstring& _nick)
{
	nicknameLabel->text = _nick;
}
