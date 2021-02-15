#pragma once
#include"Material.h"
class RenderTarget;
namespace KST
{
	class StandardMaterial : public Material
	{
	public:
		StandardMaterial();
		virtual void Render() override;
		virtual void SetSubset(int index) override;
		virtual void SetMesh(PKH::Mesh* mesh) override;
		void EnableAlphaTest(float threshold);
		void DisableAlphaTest();

	private:
		void RenderShadowMap();
		void RenderGBuffer();
	private:
		ID3DXEffect* renderingShader;
		ID3DXEffect* deferredShader;
		RenderTarget* albedoRenderTarget;
		RenderTarget* normalRenderTarget;
		RenderTarget* sharpnessRenderTarget;
		RenderTarget* depthRenderTarget;
		bool alphaTest;
		int subsetIndex;
		PKH::Mesh* mesh;
		float threshold;

	};
}