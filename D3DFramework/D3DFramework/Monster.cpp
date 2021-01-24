#include "stdafx.h"
#include "Monster.h"
#include "Plane.h"
#include "Rectangle.h"
#include "MinionFloatingBar.h"

Monster::Monster()
{
	bar = (MinionFloatingBar*)ObjectManager::GetInstance()->CreateObject<MinionFloatingBar>(Layer::UI);
	bar->SetTarget(this);
	
}

Monster::~Monster()
{
	bar = nullptr;
}

void Monster::Initialize()
{
	Unit::Initialize();
}

void Monster::Release()
{
	Unit::Release();
}

void Monster::Update()
{
	Unit::Update();
	
}