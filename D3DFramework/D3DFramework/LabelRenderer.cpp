#include "stdafx.h"
#include "LabelRenderer.h"
#include "Label.h"

LabelRenderer::LabelRenderer(GameObject* owner)
	:UIRenderer(owner)
{
	label = (Label*)owner;
}

void LabelRenderer::Render()
{
	if (gameObject->visible == false) return;
	if (visible == false) return;
	if (label == nullptr) return;

	int screenW = MainGame::GetWidth();
	int screenH = MainGame::GetHeight();

	Matrix matWorld = transform->GetWorldMatrix();

	std::wstring text = label->GetDrawText();

	label->pFont->DrawTextW(nullptr, text.c_str(), lstrlen(text.c_str()), &label->rcDraw, DT_CALCRECT, label->GetColor());
	switch (label->align)
	{
	case Label::Align::Left:
		break;
	case Label::Align::Center:
		matWorld._41 -= (label->rcDraw.right - label->rcDraw.left) * 0.5f;
		break;
	case Label::Align::Right:
		matWorld._41 -= (label->rcDraw.right - label->rcDraw.left);
		break;
	default:
		break;
	}

	switch (label->valign)
	{
	case Label::VAlign::Top:
		break;
	case Label::VAlign::Middle:
		matWorld._42 -= (label->rcDraw.bottom - label->rcDraw.top) * 0.5f;
		break;
	case Label::VAlign::Bottom:
		matWorld._42 -= (label->rcDraw.bottom - label->rcDraw.top);
		break;
	default:
		break;
	}

	label->pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// Shadow
	if (label->shadow)
	{
		Matrix matWorldShadow = matWorld;
		matWorldShadow._41 += 2;
		matWorldShadow._42 += 2;

		label->pSprite->SetTransform(&matWorldShadow);
		label->pFont->DrawTextW(label->pSprite, text.c_str(), lstrlen(text.c_str()), nullptr, 0, label->GetShadowColor());
	}

	// Outline
	if (label->outline)
	{
		Matrix matWorldOutline[4] = { matWorld, matWorld, matWorld, matWorld };

		matWorldOutline[0]._41 -= 1;
		matWorldOutline[1]._41 += 1;
		matWorldOutline[2]._42 -= 1;
		matWorldOutline[3]._42 += 1;

		for (int i = 0; i < 4; ++i)
		{
			label->pSprite->SetTransform(&matWorldOutline[i]);
			label->pFont->DrawTextW(label->pSprite, text.c_str(), lstrlen(text.c_str()), nullptr, 0, label->GetOutlineColor());
		}
	}

	// Normal
	label->pSprite->SetTransform(&matWorld);
	label->pFont->DrawTextW(label->pSprite, text.c_str(), lstrlen(text.c_str()), nullptr, 0, label->GetColor());

	label->pSprite->End();
}

void LabelRenderer::SetLabel(Label* label)
{
	this->label = label;
}
