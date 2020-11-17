#include "stdafx.h"
#include "Effect.h"
#include "Rectangle.h"
#include "Plane.h"
#include "Environment.h"

Effect::Effect()
{
}

Effect::Effect(const Vector3 & pos, const Vector3& size, TextureKey start, TextureKey end, float delay, bool plane, bool isBillY, float radianY, bool loop, float lifeTime, bool isMove, float speed, const Vector3 & dir, bool onTerrain, float _offsetY, Character * _target) :
	startKey(start), endKey(end), animSpeed(delay),
	isPlane(plane), isBillboardY(isBillY), isLoop(loop),
	lifeTime(lifeTime), isMove(isMove), direction(dir),
	isOnTerrain(onTerrain), offsetY(_offsetY), target(_target)
{
	transform->position = pos;
	transform->scale = size;
	transform->eulerAngles.y = radianY;
	stat.moveSpeed = speed;
		
	Mesh* mesh;

	if (isPlane) mesh = (Mesh*)AddComponent<PKH::Plane>(L"Mesh");
	else mesh = (Mesh*)AddComponent<PKH::Rectangle>(L"Mesh");

	mesh->SetBlendMode(BlendMode::ALPHA_TEST);

	anim = (Animation2D*)AddComponent<Animation2D>(L"Animation2D");
	
	Initialize();
}

Effect::~Effect()
{
}

void Effect::Initialize()
{
	anim->SetSprite(startKey, endKey);
	anim->SetDelay(animSpeed);
	anim->SetLoop(isLoop);
}

void Effect::Update()
{
	GameObject::Update();

	if (isBillboardY) BillboardYaw();

	if (isMove) Move(direction);

	if (IsDie()) Die();

	if (isOnTerrain) OnTerrain();

	if (target)
	{
		transform->position = target->transform->position;
		transform->position.y += offsetY;
	}
}

void Effect::Render()
{
	GameObject::Render();
}

void Effect::Release()
{
}

bool Effect::IsDie()
{
	if (!isLoop)
	{
		return anim->IsEndFrame();
	}
	else
	{
		lifeTime -= TimeManager::DeltaTime();

		if (lifeTime <= 0.f) return true;
		return false;
	}
}

void Effect::OnTerrain()
{
	GameObject* obj = ObjectManager::GetInstance()->FindObject<Environment>();
	if (obj == nullptr)
	{
		transform->position.y = offsetY;
		return;
	}
	Terrain* mesh = (Terrain*)obj->GetComponent(L"Mesh");
	if (mesh == nullptr)
	{
		transform->position.y = offsetY;
		return;
	}

	float y;
	bool onTerrain = mesh->GetYFromPoint(&y, transform->position.x, transform->position.z);
	if (onTerrain)
		transform->position.y = y + offsetY;
	else
	{
		transform->position.y = offsetY;
	}
}

Effect * Effect::Create(const Vector3 & pos, const Vector3& size, TextureKey start, TextureKey end, float delay, bool plane, bool isBillY, float radianY, bool loop, float lifeTime, bool isMove, float speed, const Vector3 & dir, bool onTerrain, float _offsetY, Character * _target)
{
	Effect* instance = new Effect(pos, size, start, end, delay, plane, isBillY, radianY, loop, lifeTime, isMove, speed, dir, onTerrain, _offsetY, _target);

	return instance;
}