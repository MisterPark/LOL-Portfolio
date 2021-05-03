#include "stdafx.h"
#include "Scuttleracer.h"
#include "ScuttleracerAI.h"

Scuttleracer::Scuttleracer()
{
	transform->scale = { 0.012f, 0.012f, 0.012f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"scuttleracer");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	anim->SetLoop((int)State::IDLE1, true);
	stat->SetBaseValue(StatType::Experience, 70.f);
	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);
}

Scuttleracer::~Scuttleracer()
{
}

void Scuttleracer::SetAI(ScuttlePos _scuttlePos)
{
	stat->SetBaseValue(StatType::MovementSpeed, 2.f);
	ScuttleracerAI* ai = (ScuttleracerAI*)AddComponent<ScuttleracerAI>(L"ScuttleracerAI");
	if (_scuttlePos == ScuttlePos::North) {
		ai->wayPoint.emplace_back(Vector3{ 9.63f, 66.91f, -7.1f });
		ai->wayPoint.emplace_back(Vector3{ 15.06f, 66.91f, -9.49f });
		ai->wayPoint.emplace_back(Vector3{ 19.92f, 66.91f, -14.5f });
		ai->wayPoint.emplace_back(Vector3{ 15.06f, 66.91f, -9.49f });
		ai->nextPoint = Vector3{ 9.63f, 66.91f, -7.1f };
	}
	else if (_scuttlePos == ScuttlePos::South) {
		ai->wayPoint.emplace_back(Vector3{ -17.74f, 66.91f, 13.85f });
		ai->wayPoint.emplace_back(Vector3{ -24.36f, 66.91f, 17.82f });
		ai->wayPoint.emplace_back(Vector3{ -28.6f, 66.91f, 23.82f });
		ai->wayPoint.emplace_back(Vector3{ -24.36f, 66.91f, 17.82f });
		ai->nextPoint = Vector3{ -17.74f, 66.91f, 13.85f };
	}
}
