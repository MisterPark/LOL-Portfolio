#pragma once
#include "Texture.h"
#include "Mesh.h"
#include "StaticMesh.h"
#include "DynamicMesh.h"

namespace PKH
{

	class RenderManager
	{
	private:
		RenderManager();
		~RenderManager();

	public:
		static RenderManager* GetInstance();
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
		static void DrawSprite(TextureKey spriteKey, const Transform& transform, int index);
		static void DrawUI(TextureKey spriteKey, const Transform& transform, int index);
		static void DrawUI(TextureKey spriteKey, Vector3 pos, int index);
		static void DrawUI(TextureKey spriteKey, Vector3 pos, Vector3 scale, int index);
		static void DrawUI(TextureKey spriteKey, Vector3 pos, Vector3 scale, int index, float verticalPer);
		static void DrawUIHorizontal(TextureKey spriteKey, Vector3 pos, Vector3 scale, int index, float horizontalPer);
		static void DrawCharacter(TextureKey spriteKey, const Transform& transform, DWORD row = 0, DWORD col = 0);

		static void DrawImage(TextureKey spriteKey, const Transform& transform);
		static void DrawImage(TextureKey spriteKey, float x, float y, float verticalPer);

		static void DrawFont(const string& text);
		static void DrawFont(const wstring& text);
		static void DrawFont(const wstring& text, float x, float y, D3DXCOLOR color);
		static void DrawFont(const wstring& text, float x, float y, D3DXCOLOR color, RECT* outRect);
		static void DrawFont(const wstring& text, Vector3 pos, Vector3 scale, D3DXCOLOR color);
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

		//=================== Device 관련 ==================
		static void LockDevice();
		static void UnlockDevice();

		static HRESULT SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix);
		//static CreateVertexBuffer()

		//==================================================

		//======================= 3D =======================

		static HRESULT LoadStaticMesh(const WCHAR* pFilePath, const WCHAR* pFileName);
		static StaticMesh* CloneStaticMesh(const wstring& key);
		static HRESULT LoadDynamicMesh(const WCHAR* pFilePath, const WCHAR* pFileName);
		static DynamicMesh* CloneDynamicMesh(const wstring& key);

		//==================================================

	private:
		// 실질적으로 장치를 다룰 객체. 
		LPDIRECT3DDEVICE9 pDevice = nullptr;
		LPDIRECT3D9 pSDK = nullptr;
		LPD3DXSPRITE pSprite = nullptr;
		LPD3DXFONT	pFont = nullptr;
		LPD3DXLINE pLine = nullptr;



		map<TextureKey, Texture*> textureMap;
		map<wstring, StaticMesh*> staticMeshMap;
		map<wstring, DynamicMesh*> dynamicMeshMap;

		CRITICAL_SECTION csDevice;
		
	};


}
