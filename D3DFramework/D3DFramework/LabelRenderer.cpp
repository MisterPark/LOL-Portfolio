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
	if (label == nullptr) return;
	
	Matrix matWorld, matPos, matScale;
	Vector3 pos;
	pos = transform->position;
	label->pFont->DrawTextW(nullptr, label->text.c_str(), lstrlen(label->text.c_str()), &label->rcDraw, DT_CALCRECT, label->foreColor);
	switch (label->align)
	{
	case Label::Align::Left:
		break;
	case Label::Align::Center:
		pos.x -= (label->rcDraw.right - label->rcDraw.left) * 0.5f;
		break;
	case Label::Align::Right:
		pos.x -= (label->rcDraw.right - label->rcDraw.left);
		break;
	default:
		break;
	}
	
	
	D3DXMatrixScaling(&matScale, transform->scale.x, transform->scale.y, 1.f);
	D3DXMatrixTranslation(&matPos, pos.x, pos.y, 0.f);
	matWorld = matScale * matPos;
	
	//RenderManager::LockDevice();
	label->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	label->pSprite->SetTransform(&matWorld);
	label->pFont->DrawTextW(label->pSprite, label->text.c_str(), lstrlen(label->text.c_str()), nullptr, 0, label->foreColor);
	label->pSprite->End();
	//RenderManager::UnlockDevice();
}

void LabelRenderer::SetLabel(Label* label)
{
	this->label = label;
}
