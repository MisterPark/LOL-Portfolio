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

		void EnableRimLight(Vector3 const& color);
		void DisableRimLight();
	private:
		void RenderShadowMap(D3DXMESHCONTAINER_DERIVED* container);
		void RenderGBuffer(D3DXMESHCONTAINER_DERIVED* container);
	private:
		bool rimLightEnable;
		Vector3 rimLightColor;

		bool culled;
		RenderTarget* albedoRenderTarget;
		RenderTarget* normalRenderTarget;
		RenderTarget* sharpnessRenderTarget;
		RenderTarget* rimLightRenderTarget;

		ID3DXEffect* renderingShader;
		ID3DXEffect* shadowMapShader;

		DynamicMesh* mesh;
	};
}