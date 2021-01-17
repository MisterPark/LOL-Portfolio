#include "stdafx.h"
#include "Monster.h"
#include "Plane.h"
#include "Rectangle.h"

Monster::Monster()
{
	
	
}

Monster::~Monster()
{
}

void Monster::Initialize()
{
	EnemyUnit::Initialize();
}

void Monster::Release()
{
	EnemyUnit::Release();
}

void Monster::Update()
{
	EnemyUnit::Update();
	
}