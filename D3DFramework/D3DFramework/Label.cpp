#include "stdafx.h"
#include "Label.h"
#include "LabelRenderer.h"

Label::Label()
{
	pDevice = RenderManager::GetDevice();
	pSprite = RenderManager::GetSprite();
	MakeFont();

	SetTexture(L"Empty");
	LabelRenderer* renderer = new LabelRenderer(this);
	AddComponent(L"LabelRenderer", renderer);

}

Label::Label(int fontSize)
{
	pDevice = RenderManager::GetDevice();
	pSprite = RenderManager::GetSprite();
	MakeFont(fontSize);

	SetTexture(L"Empty");
	LabelRenderer* renderer = new LabelRenderer(this);
	AddComponent(L"LabelRenderer", renderer);
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

void Label::SetText(const wstring& _text)
{
	text = _text.c_str();
}

void Label::SetText(int _value)
{
	WCHAR wstr[16] = {};
	swprintf_s(wstr, L"%d", _value);
	text = wstr;
}

void Label::MakeFont(int fontSize)
{

	D3DXFONT_DESCW fontInfo;
	ZeroMemory(&fontInfo, sizeof(D3DXFONT_DESCW));
	fontInfo.Height = fontSize;
	fontInfo.Width = 0;
	fontInfo.Weight = FW_THIN;
	fontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(fontInfo.FaceName, L"으뜸돋움");


	auto device = RenderManager::GetDevice();
	RenderManager::LockDevice();

	if (FAILED(D3DXCreateFontIndirect(device, &fontInfo, &pFont)))
	{
		MessageBoxW(g_hwnd, L"폰트 생성 실패", nullptr, MB_OK);
	}

	RenderManager::UnlockDevice();
}
