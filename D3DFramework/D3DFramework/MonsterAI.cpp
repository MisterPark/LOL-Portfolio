#include "stdafx.h"
#include "MonsterAI.h"
#include "Unit.h"

// 몬스터AI를 가지고 있는 유닛 리스트
list<Unit*> monsterList;

MonsterAI::MonsterAI(GameObject* owner)
    :IComponent(owner)
{
    unit = (Unit*)owner;
    monsterList.push_back(unit);
}

MonsterAI::MonsterAI(const MonsterAI& rhs)
    :IComponent(rhs)
{
}

MonsterAI::~MonsterAI()
{
    monsterList.remove(unit);
    unit = nullptr;
    target = nullptr;
}

void MonsterAI::Update()
{
    if (unit->IsDead())
    {
        target = nullptr;
        return;
    }

    if (target == nullptr)
    {
        target = unit->GetLastAttacker();

        if (target != nullptr)
        {
            // 맞은 몬스터로 부터 반경 2 안에 있는 모든 몬스터가 공격자를 타겟으로 지정
            for (auto iter : monsterList)
            {
                Vector3 to = iter->transform->position - unit->transform->position;
                float dist = to.Length();
                if (dist <= 3.f)
                {
                    MonsterAI* ai = (MonsterAI*)iter->GetComponent<MonsterAI>();
                    ai->SetTarget(target);
                }
            }
        }
        
    }
    
    if (target != nullptr)
    {
        if (target->IsDead())
        {
            target = nullptr;
        }
        unit->SetAttackTarget(target);
        unit->SetNextSkill(unit->skillList[(int)SkillIndex::Attack]);
    }
}

IComponent* MonsterAI::Clone()
{
    return new MonsterAI(*this);
}

void MonsterAI::SetTarget(Unit* _target)
{
    target = _target;
}
