#pragma once
#include"Renderer.h"
#include"RenderSystem.h"
#include"Mesh.h"
class RenderTarget;
namespace Engine
{

	class DeferredStaticMeshRenderer : public Renderer
	{
	public:
		DeferredStaticMeshRenderer(Engine::GameObject* owner);
		void EnableAlphaTest(float threshold);
		void DisableAlphaTest();
		bool IsAlphaTest();
		void EnableRimLight(Vector3 const& color);
		void DisableRimLight();

		void SetMesh(Engine::Mesh* mesh);
		Engine::IComponent* Clone() { return nullptr; }
	public:
		virtual void Render() override;
		bool NeedShadow = true;

	private:
		void RenderShadowMap();
		void RenderGBuffer();
	private:
		bool alphaTest;
		float threshold;
		bool rimLightEnable;
		Vector3 rimLightColor;
	private:
		RenderTarget* albedoRenderTarget;
		RenderTarget* normalRenderTarget;
		RenderTarget* sharpnessRenderTarget;
		RenderTarget* rimLightRenderTarget;
		ID3DXEffect* renderingShader;
		ID3DXEffect* shadowMapShader;
		Engine::Mesh* mesh;

	};
}