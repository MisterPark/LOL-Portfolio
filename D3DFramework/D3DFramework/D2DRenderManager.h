#pragma once
#include "Texture.h"

namespace PKH
{

	class D2DRenderManager
	{
	private:
		D2DRenderManager();
		~D2DRenderManager();

	public:
		static D2DRenderManager* GetInstance();
		static void Destroy();

		static HRESULT Initialize();
		static void Release();

		static void Clear();
		static void Present(HWND renderTarget = nullptr);

		static LPDIRECT3DDEVICE9 GetDevice();
		static LPD3DXSPRITE GetSprite();
		static Texture* GetTexture(TextureKey _key);
		static LPD3DXLINE GetLine();


		//================== 2D ======================
		static HRESULT LoadSprite(TextureKey spriteKey, const wstring& filePath, DWORD row=1, DWORD col=1);
		static void DrawSprite(TextureKey spriteKey, Vector3 pos, int index);
		static void DrawSprite(TextureKey spriteKey, Transform transform, int index);
		static void DrawUI(TextureKey spriteKey, Transform transform, int index);
		static void DrawUI(TextureKey spriteKey, Vector3 pos, int index);
		static void DrawCharacter(TextureKey spriteKey, Transform transform, DWORD row = 0, DWORD col = 0);

		static void DrawImage(TextureKey spriteKey, Transform transform);
		static void DrawImage(TextureKey spriteKey, float x, float y, float verticalPer);

		static void DrawFont(const string& text);
		static void DrawFont(const wstring& text);
		static void DrawFont(const wstring& text, float x, float y, D3DXCOLOR color);
		static void DrawFont(const wstring& text, float x, float y, D3DXCOLOR color, RECT* outRect);
		static void DrawFont(LPD3DXFONT font, const wstring& text, float x, float y, D3DXCOLOR color);
		static void DrawFont(LPD3DXFONT font, const wstring& text, float x, float y, D3DXCOLOR color, RECT* outRect);

		static void DrawLine(float sx, float sy, float ex, float ey);
		static void DrawLine(float sx, float sy, float ex, float ey, D3DXCOLOR color);
		//=========================================

		//=================== SR ==================

		static HRESULT LoadTexture(TextureKey key, const wstring& filePath);
		static HRESULT LoadCubeTexture(TextureKey key, const wstring& filePath);
		static void DrawTexture(TextureKey key);

		//=========================================


	private:
		// 실질적으로 장치를 다룰 객체. 
		LPDIRECT3DDEVICE9 pDevice = nullptr;
		LPDIRECT3D9 pSDK = nullptr;
		LPD3DXSPRITE pSprite = nullptr;
		LPD3DXFONT	pFont = nullptr;
		LPD3DXLINE pLine = nullptr;



		map<TextureKey, Texture*> textureMap;
	};


}
