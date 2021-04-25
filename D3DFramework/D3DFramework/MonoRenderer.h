#pragma once
#include"Renderer.h"
#include<d3dx9.h>
namespace Engine
{
	class MonoRenderer : public Renderer
	{
	public:
		MonoRenderer(GameObject* owner);
		void Render() override;
		void SetMesh(Mesh* mesh);
		IComponent* Clone() override;

	public:
		ID3DXEffect* monoShader;
		RenderTarget* normalRenderTarget;
		Mesh* mesh;
	};
}