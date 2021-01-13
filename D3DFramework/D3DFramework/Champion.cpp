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
	Unit::Initialize();

}

void Champion::Release()
{
	Unit::Release();
}

void Champion::Update()
{
	Unit::Update();
}
