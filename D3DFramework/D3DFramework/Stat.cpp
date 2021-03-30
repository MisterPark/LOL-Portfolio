#include "stdafx.h"
#include "Stat.h"
#include "Unit.h"
#include "Buff.h"
#include "Garen.h"
#include "Slot.h"

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

    //if (dynamic_cast<Garen*>(unit))
    //{
    //    int a = 10;
    //}

    constexpr int count = MaxOfEnum<StatType>();
    memset(additional, 0, sizeof(float) * count);
    for (int i = 0; i < count; i++)
    {
        percent[i] = 1.f;
    }

    // Buff
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
    
    // Item
    
    for (int i = 0; i < INVENTORY_MAX; i++)
    {
        Item* item = unit->inventory.slots[i].item;
        if (item == nullptr)
            continue;

        for (auto itemStat : item->stats)
        {
            StatType statType = itemStat.first;
            float statValue = (float)itemStat.second;

            additional[(int)statType] += statValue;
        }
    }
    
    // Final
    for (int i = 0; i < count; i++)
    {
        percent[i] = 1.f - percent[i];
        finalValues[i] = (baseValues[i] + additional[i]) * (1 + percent[i]);
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
        baseValues[(int)StatType::Health] += finalValues[(int)StatType::HealthRegen] * 0.2f * dt;
        // 마나 리젠
        baseValues[(int)StatType::Mana] += finalValues[(int)StatType::ManaRegen] * 0.2f * dt;
    }
    
}

void Stat::PostUpdate()
{
    // 사망처리 & 체력,마나 클램프
    if (baseValues[(int)StatType::Health] < 0)
    {
        baseValues[(int)StatType::Health] = 0;
        if (unit->IsDead() == false)
        {
            unit->Die();
        }
        
    }
    else if (baseValues[(int)StatType::Health] > finalValues[(int)StatType::MaxHealth])
    {
        baseValues[(int)StatType::Health] = finalValues[(int)StatType::MaxHealth];
    }

    if (baseValues[(int)StatType::Mana] < 0)
    {
        baseValues[(int)StatType::Mana] = 0;
    }
    else if (baseValues[(int)StatType::Mana] > finalValues[(int)StatType::MaxMana])
    {
        baseValues[(int)StatType::Mana] = finalValues[(int)StatType::MaxMana];
    }

    // 레벨업
    if (baseValues[(int)StatType::Experience] > baseValues[(int)StatType::MaxExperience])
    {
        baseValues[(int)StatType::Experience] -= baseValues[(int)StatType::MaxExperience];
        baseValues[(int)StatType::Level] += 1;
    }
}

float Stat::operator[](StatType type)
{
    return GetValue(type);
}

void Stat::SetBaseValue(StatType _type, float _value)
{
    baseValues[(int)_type] = _value;
    finalValues[(int)_type] = _value;
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
    return finalValues[(int)_type];
}

void Stat::AddBuff(Buff* buff)
{
    for (auto iter = buffList.begin(); iter != buffList.end(); iter++)
    {
        if (buff->buffName == (*iter)->buffName) {
            buff->overlapCount = (*iter)->overlapCount;
            if (buff->overlapCount < buff->maxOverlapCount)
                buff->overlapCount++;
            delete (*iter);
            iter = buffList.erase(iter);
            break;
        }

    }

    buffList.push_back(buff);
}

void Stat::RemoveBuff(Buff* buff)
{
    buff->tick = buff->duration;
}
