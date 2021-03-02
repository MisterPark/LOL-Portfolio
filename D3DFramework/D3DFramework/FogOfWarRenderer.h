#pragma once
#include"Renderer.h"
namespace Engine
{
	class FogOfWarRenderer: public Renderer
	{
	public:
		FogOfWarRenderer(GameObject* owner, float radius);
		void Render() override;
		void SetMapTranform(Matrix const& transform);
		void SetMapSize(float edgeLength);
		void SetRadius(float radius);

		IComponent* Clone() override;
	public:
		float edgeLength;
		Matrix mapSpace;
		float radius;
		RenderTarget* fogOfWarRenderTarget;
		ID3DXEffect* fogOfWarShader;
	};
}