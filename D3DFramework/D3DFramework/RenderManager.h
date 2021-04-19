#pragma once
#include "Texture.h"
#include "Mesh.h"
#include "StaticMesh.h"
#include "DynamicMesh.h"
#include "TerrainMesh.h"
#include "NavMesh.h"
#include "RenderTarget.h"
namespace Engine
{

	class RenderManager
	{
	private:
		RenderManager();
		~RenderManager();

	public:
		static RenderManager* GetInstance();
		static void Destroy();

		static HRESULT Initialize(int screenW, int screenH);
		static void Release();

		static void Clear();
		static void Present(HWND renderTarget = nullptr);

		static LPDIRECT3DDEVICE9 GetDevice();
		static LPD3DXSPRITE GetSprite();
		static Texture* GetTexture(const wstring& _key);
		static LPD3DXLINE GetLine();
		static TextureID GetTextureID(const wstring& _key);
		static wstring GetTextureKey(TextureID id);

		//================== 2D ======================
		static HRESULT LoadSprite(const wstring& filePath, const wstring& fileName, DWORD row=1, DWORD col=1);
		static void DrawSprite(const wstring& spriteKey, Vector3 pos, int index);
		static void DrawSprite(const wstring& spriteKey, const Transform& transform, int index);
		static void DrawUI(const wstring& spriteKey, const Transform& transform, int index=0);
		static void DrawUI(const wstring& spriteKey, Vector3 pos, int index = 0);
		static void DrawUI(const wstring& spriteKey, Vector3 pos, Vector3 scale, int index=0);
		static void DrawUI(const wstring& spriteKey, Vector3 pos, Vector3 scale, int index, float verticalPer);
		static void DrawUIHorizontal(const wstring& spriteKey, Vector3 pos, Vector3 scale, int index, float horizontalPer);
		static void DrawUIVertical(const wstring& spriteKey, Vector3 pos, Vector3 scale, int index, float verticalPer);
		static void DrawCharacter(const wstring& spriteKey, const Transform& transform, DWORD row = 0, DWORD col = 0);

		static void DrawImage(const wstring& spriteKey, const Transform& transform);
		static void DrawImage(const wstring& spriteKey, float x, float y, float verticalPer);

		static void DrawFont(const string& text);
		static void DrawFont(const wstring& text);
		static void DrawFont(const wstring& text, float x, float y, D3DXCOLOR color);
		static void DrawFont(const wstring& text, float x, float y, D3DXCOLOR color, RECT* outRect);
		static void DrawFont(const wstring& text, Vector3 pos, Vector3 scale, D3DXCOLOR color);
		static void DrawFont(LPD3DXFONT font, const wstring& text, float x, float y, D3DXCOLOR color);
		static void DrawFont(LPD3DXFONT font, const wstring& text, float x, float y, D3DXCOLOR color, RECT* outRect);

		static void DrawLine(float sx, float sy, float ex, float ey);
		static void DrawLine(float sx, float sy, float ex, float ey, D3DXCOLOR color);
		static void DrawLine(Vector3 start, Vector3 end, D3DCOLOR color);
		//=========================================

		//=================== SR ==================

		static HRESULT LoadTexture( const wstring& filePath, const wstring& fileName);
		static HRESULT LoadCubeTexture(const wstring& filePath, const wstring& fileName);
		static void SetTexture(const wstring& id);

		//=========================================

		//=================== Device 관련 ==================
		static void LockDevice();
		static void UnlockDevice();

		static HRESULT SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix);
		//static CreateVertexBuffer()

		//==================================================

		//======================= 3D =======================
		static HRESULT LoadStaticMesh(const WCHAR* lpszFilePath);
		static HRESULT LoadDynamicMesh(const WCHAR* lpszFilePath);
		static HRESULT LoadTerrainMesh(const WCHAR* lpszFilePath);
		static HRESULT LoadNavMesh(const WCHAR* lpszFilePath);
		static HRESULT LoadCustomMesh(const WCHAR* lpszFilePath);

		static HRESULT LoadStaticMesh(const WCHAR* pFilePath, const WCHAR* pFileName);
		static StaticMesh* CloneStaticMesh(const wstring& id);

		static HRESULT LoadDynamicMesh(const WCHAR* pFilePath, const WCHAR* pFileName);
		static DynamicMesh* CloneDynamicMesh(const wstring& id);
		static HRESULT LoadTerrainMesh(const WCHAR* pFilePath, const WCHAR* pFileName);
		static TerrainMesh* CloneTerrainMesh(const wstring& id);
		static HRESULT LoadNavMesh(const WCHAR* pFilePath, const WCHAR* pFileName);
		static NavMesh* CloneNavMesh(const wstring& id);
		
		static HRESULT LoadCustomMesh(const WCHAR* pFilePath, const WCHAR* pFileName);
		static CustomMesh* CloneCustomMesh(const wstring& id);
		
		static HRESULT CreateRenderTarget(const WCHAR* renderTargetID, int const width, int const height, D3DFORMAT fmt);
		static RenderTarget* GetRenderTarget(const WCHAR* renderTargetID);
		static ID3DXEffect* LoadEffect(const WCHAR* path);
		//==================================================

	private:
		// 실질적으로 장치를 다룰 객체. 
		LPDIRECT3DDEVICE9 pDevice = nullptr;
		LPDIRECT3D9 pSDK = nullptr;
		LPD3DXSPRITE pSprite = nullptr;
		LPD3DXFONT	pFont = nullptr;
		LPD3DXLINE pLine = nullptr;



		map<wstring, Texture*> textureMap;
		map<TextureID, wstring> textureIDMap;
		map<wstring, StaticMesh*> staticMeshMap;
		map<wstring, DynamicMesh*> dynamicMeshMap;
		map<wstring, TerrainMesh*> terrainMeshMap;
		map<wstring, NavMesh*> navMeshMap;
		map<wstring, CustomMesh*> customMeshMap;
		map<wstring, RenderTarget*> renderTargetMap;
		map<wstring, ID3DXEffect*> effects;
		CRITICAL_SECTION csDevice;
		
	};


}
