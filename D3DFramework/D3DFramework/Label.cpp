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

void Label::SetText(LPCTSTR pszStr, ...)
{
	va_list args;
	va_start(args, pszStr);

	int len = _vsctprintf(pszStr, args) + 1; // for '\0'

	TCHAR* pBuf = (TCHAR*)malloc(sizeof(TCHAR) * len);

	if (pBuf)
	{
		_vstprintf_s(pBuf, len, pszStr, args);
		text = pBuf;
		free(pBuf);
	}

	va_end(args);
}

void Label::SetFontSize(int _fontsize)
{
	if (pFont == nullptr) {
		MakeFont(_fontsize);
		return;
	}

	D3DXFONT_DESC fontInfo;
	pFont->GetDesc(&fontInfo);
	pFont->Release();

	fontInfo.Height = _fontsize;

	auto device = RenderManager::GetDevice();
	if (FAILED(D3DXCreateFontIndirect(device, &fontInfo, &pFont)))
	{
		MessageBoxW(g_hwnd, L"폰트 생성 실패", nullptr, MB_OK);
	}
}

void Label::MakeFont(int fontSize)
{

	D3DXFONT_DESC fontInfo;
	ZeroMemory(&fontInfo, sizeof(D3DXFONT_DESC));
	fontInfo.Height = fontSize;
	fontInfo.Width = 0;
	fontInfo.Weight = FW_THIN;
	fontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(fontInfo.FaceName, L"으뜸돋움");

	auto device = RenderManager::GetDevice();
	if (FAILED(D3DXCreateFontIndirect(device, &fontInfo, &pFont)))
	{
		MessageBoxW(g_hwnd, L"폰트 생성 실패", nullptr, MB_OK);
	}
}
