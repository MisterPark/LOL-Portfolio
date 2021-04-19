﻿#pragma once
#include "Mesh.h"

namespace Engine
{
	enum class BlendMode { NONE, ALPHA_BLEND, ALPHA_TEST, };
	enum class CullMode { NONE, CW, CCW };
	enum class ZReadMode { ON, OFF };
	enum class ZWriteMode { ON, OFF };
	enum class LightMode { ON, OFF };

	class CustomMesh : public Mesh
	{
	public:
		explicit CustomMesh(GameObject* owner);
		explicit CustomMesh(const CustomMesh& rhs);
		virtual ~CustomMesh();
	protected:
		virtual void CreateCustomMesh() {};
	public:

		virtual void Update() {};
		virtual void RenderSubset(int index) override;
		virtual IDirect3DTexture9* GetSubsetTexture(int index);
		void SetSubsetTexture(const wstring& _textureKey);

		virtual Engine::IComponent* Clone();

	public:
		HRESULT LoadMesh(const WCHAR* pFilePath, const WCHAR* pFileName);
		HRESULT LoadMeshX(const WCHAR* pFilePath, const WCHAR* pFileName);
		HRESULT LoadMeshOBJ(const WCHAR* pFilePath, const WCHAR* pFileName);

		// getter
		
		IDirect3DVertexBuffer9* GetVertexBuffer();
		// Mesh을(를) 통해 상속됨
		virtual Vector3* GetVertices() override;
		virtual DWORD* GetIndices() override;
		virtual ULONG GetVertexCount() override;
		virtual ULONG GetVertexSize() override;
		virtual ULONG GetFaceCount() override;

		// setter
		void SetColor(D3DCOLOR color);
		void SetTexture(const wstring& id);
		void SetVertexPos(UINT index, const Vector3& pos);
		void SetUV(UINT index, float u, float v);

		void SetBlendMode(BlendMode _mode);
		void SetCullMode(CullMode _mode);
		void SetZReadMode(ZReadMode _mode);
		void SetZWriteMode(ZWriteMode _mode);
		void SetLightMode(LightMode _mode);

	protected:
		IDirect3DVertexBuffer9* vertexBuffer = nullptr;
		IDirect3DIndexBuffer9* triangles = nullptr;
		UINT vertexCount;
		UINT vertexSize;
		UINT triangleCount;
		BlendMode blendMode = BlendMode::NONE;
		CullMode cullMode = CullMode::NONE;
		ZReadMode zReadMode = ZReadMode::ON;
		ZWriteMode zWriteMode = ZWriteMode::ON;
		LightMode lightMode = LightMode::OFF;
		D3DMATERIAL9 material;

		Vector3* pVertices = nullptr;
		DWORD* pIndices = nullptr;
	public:
		wstring textureKey;

		

		

	};
}


