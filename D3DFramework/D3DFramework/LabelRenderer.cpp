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
	if (visible == false) return;
	if (label == nullptr) return;
	
	int screenW = MainGame::GetWidth();
	int screenH = MainGame::GetHeight();

	Matrix matWorld = transform->GetWorldMatrix();
	label->pFont->DrawTextW(nullptr, label->text.c_str(), lstrlen(label->text.c_str()), &label->rcDraw, DT_CALCRECT, label->foreColor);
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

	label->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	label->pSprite->SetTransform(&matWorld);
	label->pFont->DrawTextW(label->pSprite, label->text.c_str(), lstrlen(label->text.c_str()), nullptr, 0, label->foreColor);
	label->pSprite->End();
}

void LabelRenderer::SetLabel(Label* label)
{
	this->label = label;
}
