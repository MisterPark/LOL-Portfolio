#include "stdafx.h"
#include "Stat.h"
#include "Unit.h"
#include "Buff.h"

Stat::Stat(GameObject* owner) :IComponent(owner)
{
    unit = (Unit*)owner;
}

Stat::Stat(const Stat& rhs) : IComponent(rhs)
{
}

Stat::~Stat()
{
    unit = nullptr;
    for (auto& iter : buffList)
    {
        delete iter;
    }
    buffList.clear();
}

IComponent* Stat::Clone()
{
    return new Stat(*this);
}

void Stat::PreUpdate()
{
    float dt = Time::DeltaTime();

    constexpr int count = MaxOfEnum<StatType>();
    memset(additional, 0, sizeof(float) * count);
    for (int i = 0; i < count; i++)
    {
        percent[i] = 1.f;
    }

    auto buff = buffList.begin();
    auto end = buffList.end();
    for (; buff != end;)
    {
        (*buff)->tick += dt;
        if ((*buff)->tick >= (*buff)->duration)
        {
            delete (*buff);
            buff = buffList.erase(buff);
            continue;
        }

        for (auto& node : (*buff)->modifiers)
        {
            if (node.isPercent)
            {
                percent[(int)node.type] *= (1.f - node.value);
            }
            else
            {
                additional[(int)node.type] += node.value;
            }
            
        }

        (*buff)->Update();

        ++buff;
    }

    for (int i = 0; i < count; i++)
    {
        percent[i] = 1.f - percent[i];
    }

}

void Stat::Update()
{
    float dt = Time::DeltaTime();
    // 이동속도
    unit->agent->SetSpeed(GetValue(StatType::MovementSpeed));

    if (unit->IsDead() == false)
    {
        // 체력 리젠
        baseValues[(int)StatType::Health] += baseValues[(int)StatType::HealthRegen] * 0.2f * dt;
        // 마나 리젠
        baseValues[(int)StatType::Health] += baseValues[(int)StatType::HealthRegen] * 0.2f * dt;
    }
    
}

void Stat::PostUpdate()
{
    
    if (baseValues[(int)StatType::Health] < 0)
    {
        baseValues[(int)StatType::Health] = 0;
        if (unit->IsDead() == false)
        {
            unit->Die();
        }
        
    }
    else if (baseValues[(int)StatType::Health] > baseValues[(int)StatType::MaxHealth])
    {
        baseValues[(int)StatType::Health] = baseValues[(int)StatType::MaxHealth];
    }

    if (baseValues[(int)StatType::Mana] < 0)
    {
        baseValues[(int)StatType::Mana] = 0;
    }
    else if (baseValues[(int)StatType::Mana] > baseValues[(int)StatType::MaxMana])
    {
        baseValues[(int)StatType::Mana] = baseValues[(int)StatType::MaxMana];
    }

}

float Stat::operator[](StatType type)
{
    return GetValue(type);
}

void Stat::SetBaseValue(StatType _type, float _value)
{
    baseValues[(int)_type] = _value;
}

float Stat::GetBaseValue(StatType _type)
{
    return baseValues[(int)_type];
}

float Stat::IncreaseBaseValue(StatType _type, float _modifier)
{
    return baseValues[(int)_type] += _modifier;
}

float Stat::DecreaseBaseValue(StatType _type, float _modifier)
{
    return baseValues[(int)_type] -= _modifier;
}

float Stat::GetValue(StatType _type)
{
    return (baseValues[(int)_type] + additional[(int)_type]) * (1 + percent[(int)_type]);
}

void Stat::AddBuff(Buff* buff)
{
    buffList.push_back(buff);
}

void Stat::RemoveBuff(Buff* buff)
{
    buff->tick = buff->duration;
}
