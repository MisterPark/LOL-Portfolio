#pragma once
#include"Renderer.h"
#include<d3dx9.h>
#include<unordered_map>
#include"Vector3.h"
#include"Matrix.h"
#include"Texture.h"

namespace Engine
{
	class ForwardRenderer : public Renderer
	{
	public:
		ForwardRenderer(GameObject* const owner, std::wstring const & path);
		~ForwardRenderer();
		void SetValue(const char* parameter, float value);
		void SetValue(const char* parameter, Vector3 const& value);
		void SetValue(const char* parameter, D3DXVECTOR4 const& value);
		void SetValue(const char* parameter, Matrix const& value);
		void SetValue(const char* parameter, IDirect3DTexture9* const value);
		void SetDiffuseTextureParam(const char* parameter);
		void SetPass(int pass);
		void SetMesh(Mesh* mesh);
		void SetColormapTex(const std::wstring& _tag);
		Vector2 GetUVOffset();
		void SetUVOffset(Vector2 _uvOffset);
		virtual void Render() override;
		virtual IComponent* Clone() override;
	private:
		ID3DXEffect* effect;
		int pass;
		std::string diffuseTextureHandle;
		Mesh* mesh;
		Texture* colormapTex = nullptr;
		Vector2 uvOffset = { 0.f, 0.f };
	};
}