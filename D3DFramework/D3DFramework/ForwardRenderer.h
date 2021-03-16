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
		union Parameter
		{
			float f32;
			float vector4[4];
			float matrix[16];
			int integer;
			IDirect3DTexture9* texture;
		};

	public:
		ForwardRenderer(GameObject* const owner, std::wstring const & path);
		void SetValue(const char* parameter, float value);
		void SetValue(const char* parameter, Vector3 const& value);
		void SetValue(const char* parameter, D3DXVECTOR4 const& value);
		void SetValue(const char* parameter, Matrix const& value);
		void SetValue(const char* parameter, IDirect3DTexture9* const value);
		void SetDiffuseTextureParam(const char* parameter);
		void SetPass(int pass);
		void SetMesh(Mesh* mesh);
		virtual void Render() override;
		virtual IComponent* Clone() override;
	private:
		ID3DXEffect* effect;
		int pass;
		std::unordered_map<std::string, std::pair<type_info const*, Parameter> > parameterTable;
		std::string diffuseTextureHandle;
		Mesh* mesh;
	};
}