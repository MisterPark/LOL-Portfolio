#include "stdafx.h"
#include "DamageObject_MissFortune_E.h"
#include "Unit.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "Buff_MissFortuneESlow.h"
#include "Stat.h"

DamageObject_MissFortune_E::DamageObject_MissFortune_E()
{
}

DamageObject_MissFortune_E::~DamageObject_MissFortune_E()
{

}

void DamageObject_MissFortune_E::Initialize()
{

}

void DamageObject_MissFortune_E::Release()
{
}

void DamageObject_MissFortune_E::Update()
{
	DamageObject::Update();
}

void DamageObject_MissFortune_E::OnCollisionAddAttack(float damage, Collider* target)
{
	Buff_MissFortuneESlow* slowBuff = new Buff_MissFortuneESlow(host, 0.3f, -slowValue);
	Unit* targetUnit = dynamic_cast<Unit*>(target->gameObject);
	if (targetUnit == nullptr)
		return;
	targetUnit->stat->AddBuff(slowBuff);
}
