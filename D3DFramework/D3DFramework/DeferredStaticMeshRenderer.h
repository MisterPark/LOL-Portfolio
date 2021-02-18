#pragma once
#include"Renderer.h"
#include"RenderSystem.h"
#include"Mesh.h"
class RenderTarget;
namespace KST
{

	class DeferredStaticMeshRenderer : public Renderer
	{
	public:
		DeferredStaticMeshRenderer(PKH::GameObject* owner);
		void EnableAlphaTest(float threshold);
		void DisableAlphaTest();
		bool IsAlphaTest();
		void SetMesh(PKH::Mesh* mesh);
		PKH::IComponent* Clone() { return nullptr; }
	public:
		virtual void Render() override;
		bool NeedShadow = true;

	private:
		void RenderShadowMap();
		void RenderGBuffer();
	private:
		bool alphaTest;
		float threshold;
	private:
		RenderTarget* albedoRenderTarget;
		RenderTarget* normalRenderTarget;
		RenderTarget* sharpnessRenderTarget;
		RenderTarget* depthRenderTarget;
		ID3DXEffect* renderingShader;
		ID3DXEffect* shadowMapShader;
		PKH::Mesh* mesh;

	};
}