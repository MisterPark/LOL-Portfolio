#pragma once
#include"Renderer.h"
#include<d3dx9.h>
namespace Engine
{
	class DistortionRenderer : public Renderer
	{
	public:
		DistortionRenderer(GameObject* owner);
		void Render() override;
		void SetMesh(Mesh* mesh);
		void SetOpacity(float op);
		IComponent* Clone() override;
	public:
		RenderTarget* normalRenderTarget;
		ID3DXEffect* distortionShader;
		Texture* noiseTexture;
		float opacity;
		Mesh* mesh;
	};
}