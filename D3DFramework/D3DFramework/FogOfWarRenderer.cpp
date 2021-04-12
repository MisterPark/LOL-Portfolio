#include "stdafx.h"
#include "FogOfWarRenderer.h"
#include "FogOfWarRenderSystem.h"
Engine::FogOfWarRenderer::FogOfWarRenderer(GameObject* owner, float radius):
	Renderer{owner, RendererType::EarlyForward},
	radius{radius}
{
	D3DXMatrixIdentity(&mapSpace);
}

void Engine::FogOfWarRenderer::Render()
{
	if (visible == false) return;
	//내 오브젝트의 월드 트렌스폼을 구한다.
	Matrix mTransform{ this->transform->GetWorldMatrix() };
	Vector3 vPosition{ reinterpret_cast<Vector3 const&>(mTransform.m[3]) };
	FogOfWarRenderSystem::AddSight({ radius, radius - 1.f, vPosition });

}

void Engine::FogOfWarRenderer::SetMapTranform(Matrix const& transform)
{
	D3DXMatrixInverse(&mapSpace, nullptr, &transform);
}

void Engine::FogOfWarRenderer::SetMapSize(float edgeLength)
{
	this->edgeLength = edgeLength;
}

void Engine::FogOfWarRenderer::SetRadius(float radius)
{
	this->radius = radius;
}

IComponent* Engine::FogOfWarRenderer::Clone()
{
	return nullptr;
}
