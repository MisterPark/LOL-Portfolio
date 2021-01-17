#include "stdafx.h"
#include "Champion.h"
#include "FloatingBar.h"

Champion::Champion()
{
	bar = (FloatingBar*)ObjectManager::GetInstance()->CreateObject<FloatingBar>(Layer::UI);
	bar->SetTarget(this);
}

Champion::~Champion()
{
	bar = nullptr;
}

void Champion::Initialize()
{
	EnemyUnit::Initialize();

}

void Champion::Release()
{
	EnemyUnit::Release();
}

void Champion::Update()
{
	EnemyUnit::Update();
}
