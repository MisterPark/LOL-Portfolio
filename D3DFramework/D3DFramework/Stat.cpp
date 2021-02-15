#include "stdafx.h"
#include "Stat.h"


Stat::Stat()
{

}

Stat::Stat(const Stat& rhs)
{
    this->baseValue = rhs.baseValue;
    for (auto iter : rhs.modifiers)
    {
        modifiers.push_back(iter);
    }
}

Stat::Stat(float val)
{
    this->baseValue = val;
}

Stat::~Stat()
{
}

Stat& Stat::operator=(const float& val)
{
    this->baseValue = val;
    return *this;
}

Stat& Stat::operator+=(const float& modi)
{
    this->baseValue += modi;
    return *this;
}

Stat& Stat::operator+(const float& modi)
{
    Stat stat(*this);
    stat += modi;
    return stat;
}

Stat& Stat::operator-=(const float& modi)
{
    this->baseValue -= modi;
    return *this;
}

Stat& Stat::operator-(const float& modi)
{
    Stat stat(*this);
    stat -= modi;
    return stat;
}

Stat& Stat::operator*=(const float& modi)
{
    this->baseValue *= modi;
    return *this;
}

Stat& Stat::operator*(const float& modi)
{
    Stat stat(*this);
    stat *= modi;
    return stat;
}

Stat& Stat::operator/=(const float& modi)
{
    this->baseValue /= modi;
    return *this;
}

Stat& Stat::operator/(const float& modi)
{
    Stat stat(*this);
    stat /= modi;
    return stat;
}

Stat& Stat::operator=(const Stat& rhs)
{
    this->baseValue = rhs.baseValue;
    return *this;
}

Stat& Stat::operator+(const Stat& rhs)
{
    Stat stat(*this);
    stat.baseValue += rhs.baseValue;
    return stat;
}

Stat& Stat::operator+=(const Stat& rhs)
{
    this->baseValue += rhs.baseValue;
    return *this;
}

Stat& Stat::operator-(const Stat& rhs)
{
    Stat stat(*this);
    stat.baseValue -= rhs.baseValue;
    return stat;
}

Stat& Stat::operator-=(const Stat& rhs)
{
    this->baseValue -= rhs.baseValue;
    return *this;
}

Stat& Stat::operator*(const Stat& rhs)
{
    Stat stat(*this);
    stat.baseValue *= rhs.baseValue;
    return stat;
}

Stat& Stat::operator*=(const Stat& rhs)
{
    this->baseValue *= rhs.baseValue;
    return *this;
}

Stat& Stat::operator/(const Stat& rhs)
{
    Stat stat(*this);
    stat.baseValue /= rhs.baseValue;
    return stat;
}

Stat& Stat::operator/=(const Stat& rhs)
{
    this->baseValue /= rhs.baseValue;
    return *this;
}

bool Stat::operator==(const Stat& rhs)
{
    return (this->baseValue == rhs.baseValue);
}

bool Stat::operator!=(const Stat& rhs)
{
    return (this->baseValue != rhs.baseValue);
}

bool Stat::operator>=(const Stat& rhs)
{
    return (this->baseValue >= rhs.baseValue);
}

bool Stat::operator<=(const Stat& rhs)
{
    return (this->baseValue <= rhs.baseValue);
}

bool Stat::operator>(const Stat& rhs)
{
    return (this->baseValue > rhs.baseValue);
}

bool Stat::operator<(const Stat& rhs)
{
    return (this->baseValue < rhs.baseValue);
}

void Stat::AddModifier(float _modifier)
{
    modifiers.push_back(_modifier);
}

void Stat::RemoveModifier(float _modifier)
{
    modifiers.remove(_modifier);
}

float Stat::GetValue()
{
    float finalValue = baseValue;
    for (float modi : modifiers)
    {
        finalValue += modi;
    }
    return finalValue;
}

float Stat::GetBaseValue()
{
    return baseValue;
}
