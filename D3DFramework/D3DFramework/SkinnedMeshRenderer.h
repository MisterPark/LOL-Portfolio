#pragma once
#include"Renderer.h"
#include"DynamicMesh.h"
#include"RenderSystem.h"
#include<vector>
namespace Engine
{

	class SkinnedMeshRenderer :
		public Renderer
	{
	public:
		static Engine::RendererType constexpr RenderingType = Engine::RendererType::Forward;
	public:
		SkinnedMeshRenderer(Engine::GameObject* owner);
		virtual void Render();
		Engine::IComponent* Clone() { return nullptr; }
		void SetMesh(DynamicMesh* mesh);
	private:
		void RenderShadowMap(D3DXMESHCONTAINER_DERIVED* container);
		void RenderGBuffer(D3DXMESHCONTAINER_DERIVED* container);
	private:
		bool culled;
		RenderTarget* albedoRenderTarget;
		RenderTarget* normalRenderTarget;
		RenderTarget* sharpnessRenderTarget;
		RenderTarget* depthRenderTarget;
		ID3DXEffect* renderingShader;
		ID3DXEffect* shadowMapShader;

		DynamicMesh* mesh;
	};
}