#pragma once
#include"Renderer.h"
#include "Mesh.h"
#include <d3dx9.h>
#include "RenderTarget.h"
namespace Engine
{
	//전장의 안개 맵에 높이를 저장하는 렌더러.
	class FogOfWarObstacleRenderer : public Renderer
	{
	public:
		FogOfWarObstacleRenderer(GameObject* owner);
		void Render() override;
		void SetMesh(Engine::Mesh* mesh);
		IComponent* Clone() override;
	public:
		RenderTarget* heightFogOfWarRenderTarget;
		ID3DXEffect* fogOfWarShader;
		Engine::Mesh* mesh;
	};
}