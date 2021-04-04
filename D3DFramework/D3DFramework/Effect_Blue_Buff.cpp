#include "stdafx.h"
#include "Effect_Blue_Buff.h"

Effect_Blue_Buff::Effect_Blue_Buff()
{
	CustomMesh* mesh = (CustomMesh*)GetComponent(L"Mesh");
	mesh->SetTexture(L"blue_buff");
}

Effect_Blue_Buff::~Effect_Blue_Buff()
{
}

void Effect_Blue_Buff::Update()
{
	GameObject::Update();
}
