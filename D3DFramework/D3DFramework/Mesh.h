#pragma once
#include "IComponent.h"

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

	class Mesh : public PKH::IComponent
	{
	public:
		Mesh();
		virtual ~Mesh();

		virtual void Update() {};
		virtual void Render();

		// IComponent을(를) 통해 상속됨
		virtual PKH::IComponent* Clone() override;

		//====
		UINT GetVertexCount();
		IDirect3DVertexBuffer9* GetVertexBuffer();

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
		UINT triangleCount;
		BlendMode blendMode = BlendMode::NONE;
		ZReadMode zReadMode = ZReadMode::ON;
		ZWriteMode zWriteMode = ZWriteMode::ON;
		LightMode lightMode = LightMode::OFF;
		D3DMATERIAL9 material;
	public:
		TextureKey textureKey = TextureKey::NONE;

		
	};
}


