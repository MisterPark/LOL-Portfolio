#include "stdafx.h"
#include "Effect_Baron_Buff.h"

Effect_Baron_Buff::Effect_Baron_Buff()
{
	CustomMesh* mesh = (CustomMesh*)GetComponent(L"Mesh");
	mesh->SetTexture(L"baron_buff");
}

Effect_Baron_Buff::~Effect_Baron_Buff()
{
}

void Effect_Baron_Buff::Update()
{
	GameObject::Update();
}
