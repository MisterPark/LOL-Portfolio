#include "stdafx.h"
#include "Buff.h"


Buff::Buff(Unit* _host, float _duration)
{
	this->host = _host;
	this->duration = _duration;
}

Buff::~Buff()
{
	host = nullptr;
}

void Buff::Update()
{
}

void Buff::AddModifier(StatType _type, float _value, bool _isPercent)
{
	Buff::Node node;
	node.type = _type;
	node.value = _value;
	node.isPercent = _isPercent;
	modifiers.push_back(node);
}
