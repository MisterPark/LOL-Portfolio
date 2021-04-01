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

std::wstring Label::GetText()
{
	return text;
}

std::wstring Label::GetDrawText()
{
	return drawText;
}

void Label::SetText(const wstring& _text)
{
	text = _text.c_str();
	AdjustTextByWidthLimit();
}

void Label::SetText(int _value)
{
	WCHAR wstr[16] = {};
	swprintf_s(wstr, L"%d", _value);
	text = wstr;
	AdjustTextByWidthLimit();
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
	AdjustTextByWidthLimit();
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

D3DCOLOR Label::GetColor() { return foreColor; }
D3DCOLOR Label::GetShadowColor() { return shadowColor; }
D3DCOLOR Label::GetOutlineColor() { return outlineColor; }

void Label::SetColor(D3DCOLOR _color)
{
	foreColor = _color;
}

void Label::SetColor(unsigned char _a, unsigned char _r, unsigned char _g, unsigned char _b)
{
	foreColor = D3DCOLOR_ARGB(_a, _r, _g, _b);
}

void Label::SetShadowColor(unsigned char _a, unsigned char _r, unsigned char _g, unsigned char _b)
{
	shadowColor = D3DCOLOR_ARGB(_a, _r, _g, _b);
}

void Label::SetOutlineColor(unsigned char _a, unsigned char _r, unsigned char _g, unsigned char _b)
{
	outlineColor = D3DCOLOR_ARGB(_a, _r, _g, _b);
}

void Label::SetWidthLimit(int _limit)
{
	widthLimit = _limit;
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

void Label::AdjustTextByWidthLimit()
{
	auto renderer = GetComponent<LabelRenderer>();
	if (renderer == nullptr) return;
	if (widthLimit <= 0) {
		drawText = text;
		return;
	}

	std::wstring textTemp;
	std::wstring textRest = text;
	std::wstring textFinal;
	RECT rcCalc;

	while (textRest.size() > 0)
	{
		// 글자 전체를 widthLimit로 한 번 계산
		pFont->DrawTextW(nullptr, textRest.c_str(), lstrlen(textRest.c_str()), &rcCalc, DT_CALCRECT, GetColor());
		if ((rcCalc.right - rcCalc.left) <= widthLimit) {
			textFinal += textRest;
			break;
		}

		// 안되면 한 글자 한 글자 계산
		int count = 0;
		for (size_t i = 1; i < textRest.size(); ++i)
		{
			count = (int)i;

			// \n일 때
			if (textRest[i - 1] == '\n') {
				// 자름
				textFinal = textFinal + textRest.substr(0, count);
				textRest = textRest.substr(count, textRest.size() - count);
				break;
			}

			// default
			textTemp = textRest.substr(0, i);
			pFont->DrawTextW(nullptr, textTemp.c_str(), lstrlen(textTemp.c_str()), &rcCalc, DT_CALCRECT, GetColor());
			if ((rcCalc.right - rcCalc.left) > widthLimit) {
				if (i > 1) count--;
				// 자르고 \n 붙임
				textFinal = textFinal + textRest.substr(0, count) + L"\n";
				textRest = textRest.substr(count, textRest.size() - count);
				break;
			}
		}

	}

	drawText = textFinal;
}
