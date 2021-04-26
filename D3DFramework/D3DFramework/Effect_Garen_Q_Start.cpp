#include "stdafx.h"
#include "Effect_Garen_Q_Start.h"

Effect_Garen_Q_Start::Effect_Garen_Q_Start()
{
	CustomMesh* mesh = (CustomMesh*)GetComponent(L"Mesh");
	mesh->SetTexture(L"garen_base_q_cas_bubble_2");
	offset = { 0.f,1.f,0.f };
	
	auto renderer = dynamic_cast<ForwardRenderer*>(GetComponent(L"renderer"));
	if (renderer == nullptr) return;
	renderer->SetPass(0);

	alpha = 0.7f;
	renderer->SetAlpha(alpha);

}

Effect_Garen_Q_Start::~Effect_Garen_Q_Start()
{
}

void Effect_Garen_Q_Start::PostUpdate()
{
	StickToTarget();
	EffectObject::PostUpdate();
}

void Effect_Garen_Q_Start::Update()
{
	EffectObject::Update();
	
	Billboard();

	auto renderer = dynamic_cast<ForwardRenderer*>(GetComponent(L"renderer"));
	if (renderer == nullptr) return;

	alpha -= 1 * Time::DeltaTime();
	renderer->SetAlpha(alpha);
}
