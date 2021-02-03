#include "stdafx.h"
#include "TurretBreak.h"
#include "Animation.h"
#include "Unit.h"

TurretBreak::TurretBreak()
{
	anim1 = (Animation*)AddComponent<Animation>(L"Animation");
	//anim2 = (Animation*)AddComponent<Animation>(L"Animation");
	//anim3 = (Animation*)AddComponent<Animation>(L"Animation");
	mesh1 = RenderManager::CloneDynamicMesh(L"sruap_orderturret1_break1");
	//mesh2 = RenderManager::CloneDynamicMesh(L"sruap_orderturret1_break2");
	//mesh3 = RenderManager::CloneDynamicMesh(L"sruap_orderturret1_break3");
	AddComponent(L"DynamicMesh", mesh1);
	//AddComponent(L"DynamicMesh", mesh2);
	//AddComponent(L"DynamicMesh", mesh3);
	anim1->AttachToDynamicMesh(mesh1);
	//anim2->AttachToDynamicMesh(mesh2);
	//anim3->AttachToDynamicMesh(mesh3);
	anim1->SetState((int)UnitState::DEATH);
	//anim2->SetState((int)UnitState::DEATH);
	//anim3->SetState((int)UnitState::DEATH);

	
	anim1->SetLoop((int)UnitState::DEATH, true);
	anim1->animsets[0].index = anim1->animsets[3].index;
	anim1->animsets[0].isLoop = anim1->animsets[3].isLoop;
	anim1->animsets[0].period = anim1->animsets[3].period;
	anim1->animsets[0].speed = anim1->animsets[3].speed;
	//anim2->SetLoop((int)UnitState::DEATH, true);
	//anim3->SetLoop((int)UnitState::DEATH, true);
}

TurretBreak::~TurretBreak()
{
}

void TurretBreak::Initialize()
{
}

void TurretBreak::Release()
{
}

void TurretBreak::Update()
{
	if (InputManager::GetKey('N'))
	{
		transform->scale.x += 0.1f;
		transform->scale.y += 0.1f;
		transform->scale.z += 0.1f;
	}
	if (InputManager::GetKey('M'))
	{
		transform->scale.x -= 0.1f;
		transform->scale.y -= 0.1f;
		transform->scale.z -= 0.1f;
	}
	if (anim1->IsFrameEnd())
	{
		//anim1->Stop();
		//anim2->Stop();
		//anim3->Stop();
	}
	GameObject::Update();
}

void TurretBreak::PostUpdate()
{
	GameObject::PostUpdate();
}
