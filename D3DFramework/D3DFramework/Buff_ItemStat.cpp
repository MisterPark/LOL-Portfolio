#include "stdafx.h"
#include "Buff_ItemStat.h"

Buff_ItemStat::Buff_ItemStat(Unit* _host) : Buff(_host, INFINITY)
{
	buffName = BuffName::ItemStat;
}

Buff_ItemStat::~Buff_ItemStat()
{

}

void Buff_ItemStat::Update()
{
}