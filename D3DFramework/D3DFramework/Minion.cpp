#include "stdafx.h"
#include "Minion.h"
#include "MinionFloatingBar.h"

Minion::Minion()
{
	bar = (MinionFloatingBar*)ObjectManager::GetInstance()->CreateObject<MinionFloatingBar>(Layer::UI);
	bar->SetTarget(this);
}

Minion::~Minion()
{
	bar = nullptr;
}
