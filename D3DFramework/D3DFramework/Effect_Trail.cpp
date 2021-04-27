#include "stdafx.h"
#include "Effect_Trail.h"
#include "TrailMesh.h"

Effect_Trail::Effect_Trail()
{
	//DeleteComponent(L"Mesh");
	//DeleteComponent(L"renderer");

	mesh = (TrailMesh*)AddComponent<TrailMesh>(L"TrailMesh");
	ForwardRenderer* renderer = new ForwardRenderer{ this, L"./forward.fx" };
	renderer->SetMesh(mesh);
	renderer->SetDiffuseTextureParam("g_diffuseTexture");
	renderer->SetPass(1);
	AddComponent(L"renderer2", renderer);
	
	name = L"Trail";
	mesh->SetSubsetTexture(L"garen_base_q_wpn_trail");
	//mesh->SetSubsetTexture(L"red");
}

Effect_Trail::~Effect_Trail()
{
	mesh = nullptr;
}

void Effect_Trail::PostUpdate()
{
	//StickToTarget();
	EffectObject::PostUpdate();
}

void Effect_Trail::SetTrailPos(const Vector3& start, const Vector3& end)
{
	mesh->SetTrailPos(start, end);
}
