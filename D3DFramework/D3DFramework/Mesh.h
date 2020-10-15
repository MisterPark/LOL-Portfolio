#pragma once
#include "IComponent.h"

namespace PKH
{
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

		void SetColor(D3DCOLOR color);
		void SetTexture(TextureKey key);
		void SetVertexPos(UINT index, const Vector3& pos);
		void SetUV(UINT index, float u, float v);

	protected:
		IDirect3DVertexBuffer9* vb = nullptr;
		IDirect3DIndexBuffer9* triangles = nullptr;
		UINT vertexCount;
		UINT triangleCount;
	public:
		TextureKey textureKey = TextureKey::NONE;

		
	};
}


