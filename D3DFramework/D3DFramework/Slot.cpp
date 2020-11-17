#include "stdafx.h"
#include "Slot.h"
#include "Item.h"

Slot::Slot()
{
//	textureKey = TextureKey::UI_SLOT;
}

Slot::~Slot()
{
}

Item* Slot::GetItem()
{
    return item;
}

Item* Slot::SetItem(Item* inItem)
{
    Item* old = item;

    item = inItem;

    return old;
}

void Slot::Update()
{
	UI::Update();
}

void Slot::Render()
{
    RenderManager::DrawUI(textureKey, transform->position, 0);

    if (item)
    {
        RenderManager::DrawUI(item->anim->GetCurrentSprite(), Vector3(transform->position.x + 3, transform->position.y + 3, 0), 0);
		WCHAR wstr[8] = {};
		wsprintf(wstr, L"%d", item->count);
		RenderManager::DrawFont(wstr,
			Vector3(transform->position.x + 3, transform->position.y + 3, 0),
			Vector3(0.5f, 0.5f, 0.5f),
			D3DCOLOR_ARGB(255, 0, 0, 0));
	}
}

void Slot::OnHover()
{
	UI::OnHover();

	
}

void Slot::OnLeave()
{
	UI::OnLeave();

}

void Slot::OnClick()
{
	UI::OnClick();

	
}

void Slot::OnRButtonDown()
{
	UI::OnRButtonDown();

	Use();
}

void Slot::Use()
{
	if (item != nullptr)
	{
		item->Use();
		if (item->count < 1)
		{
			delete item;
			item = nullptr;

		}
	}
}

void Slot::Initialize()
{
}

void Slot::Release()
{
}

void Slot::UpdateUI()
{
	Texture* texture = RenderManager::GetTexture(textureKey);
	if (texture != nullptr)
	{
		width = transform->scale.x * texture->GetSpriteWidth();
		height = transform->scale.y * texture->GetSpriteHeight();
	}
	else
	{
		width = transform->scale.x * 32;
		height = transform->scale.y * 32;
	}
}
