#include "stdafx.h"
#include "Buff_Item.h"

Buff_Item::Buff_Item(Unit* _host) : Buff(_host, INFINITY)
{
	buffName = BuffName::Item;
}

Buff_Item::~Buff_Item()
{

}

void Buff_Item::Update()
{
}