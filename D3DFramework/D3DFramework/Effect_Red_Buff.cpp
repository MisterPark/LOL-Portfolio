#include "stdafx.h"
#include "Effect_Red_Buff.h"
#include "Plane.h"
#include "Unit.h"

Effect_Red_Buff::Effect_Red_Buff()
{
	CustomMesh* mesh = (CustomMesh*)GetComponent(L"Mesh");
	mesh->SetTexture(L"red_buff");
}

Effect_Red_Buff::~Effect_Red_Buff()
{
}

void Effect_Red_Buff::Update()
{
	GameObject::Update();
}
