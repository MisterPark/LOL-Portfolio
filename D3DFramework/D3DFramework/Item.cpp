#include "stdafx.h"
#include "Item.h"

void Item::Initialize()
{
	anim = (Animation2D*)AddComponent<Animation2D>(L"Animation2D");
}

void Item::Release()
{
}

void Item::Update()
{
}
