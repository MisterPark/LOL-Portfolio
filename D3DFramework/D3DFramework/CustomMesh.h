#pragma once
#include "Mesh.h"

namespace PKH
{
	enum class BlendMode
	{
		NONE,
		ALPHA_BLEND,
		ALPHA_TEST,
	};

	enum class ZReadMode
	{
		ON,
		OFF
	};
	enum class ZWriteMode
	{
		ON,
		OFF
	};

	enum class LightMode
	{
		ON,
		OFF
	};

	class CustomMesh : public Mesh
	{
	public:
		explicit CustomMesh(GameObject* owner);
		explicit CustomMesh(const CustomMesh& rhs);
		virtual ~CustomMesh();
	protected:
		virtual void CreateCustomMesh() = 0;
	public:

		virtual void Update() {};
		virtual void Render();

		virtual PKH::IComponent* Clone() = 0;

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
		void SetTexture(TextureKey key);
		void SetVertexPos(UINT index, const Vector3& pos);
		void SetUV(UINT index, float u, float v);
		void SetBlendMode(BlendMode _mode);
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
		ZReadMode zReadMode = ZReadMode::ON;
		ZWriteMode zWriteMode = ZWriteMode::ON;
		LightMode lightMode = LightMode::OFF;
		D3DMATERIAL9 material;

		Vector3* pVertices = nullptr;
		DWORD* pIndices = nullptr;
	public:
		TextureKey textureKey = TextureKey::NONE;

		

		

	};
}


