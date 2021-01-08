#include "stdafx.h"
#include "Label.h"

Label::Label()
{
	pDevice = RenderManager::GetDevice();
	pSprite = RenderManager::GetSprite();
	MakeFont();
}

Label::Label(int fontSize)
{
	pDevice = RenderManager::GetDevice();
	pSprite = RenderManager::GetSprite();
	MakeFont(fontSize);
}

Label::~Label()
{
	if (pFont)
	{
		pFont->Release();
	}
}

void Label::Initialize()
{
}

void Label::Release()
{
}

void Label::Update()
{
	UI::Update();
}

void Label::Render()
{
	if (pFont == nullptr) return;

	//RenderManager::DrawFont(text, transform->position, transform->scale, foreColor);

	Matrix matWorld, matPos, matScale;
	Vector3 pos;
	pos = transform->position;
	pFont->DrawTextW(nullptr, text.c_str(), lstrlen(text.c_str()), &rcDraw, DT_CALCRECT, foreColor);
	switch (align)
	{
	case Label::Align::Left:
		break;
	case Label::Align::Center:
		pos.x -= (rcDraw.right - rcDraw.left) * 0.5f;
		break;
	case Label::Align::Right:
		pos.x -= (rcDraw.right - rcDraw.left);
		break;
	default:
		break;
	}
	

	D3DXMatrixScaling(&matScale, transform->scale.x, transform->scale.y, 1.f);
	D3DXMatrixTranslation(&matPos, pos.x, pos.y, 0.f);
	matWorld = matScale * matPos;

	RenderManager::LockDevice();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pSprite->SetTransform(&matWorld);
	pFont->DrawTextW(pSprite, text.c_str(), lstrlen(text.c_str()), nullptr, 0, foreColor);
	pSprite->End();
	RenderManager::UnlockDevice();
}

void Label::MakeFont(int fontSize)
{

	D3DXFONT_DESCW fontInfo;
	ZeroMemory(&fontInfo, sizeof(D3DXFONT_DESCW));
	fontInfo.Height = fontSize;
	fontInfo.Width = 0;
	fontInfo.Weight = FW_THIN;
	fontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(fontInfo.FaceName, L"À¸¶äµ¸¿ò");


	auto device = RenderManager::GetDevice();
	RenderManager::LockDevice();

	if (FAILED(D3DXCreateFontIndirect(device, &fontInfo, &pFont)))
	{
		MessageBoxW(g_hwnd, L"ÆùÆ® »ý¼º ½ÇÆÐ", nullptr, MB_OK);
	}

	RenderManager::UnlockDevice();
}
