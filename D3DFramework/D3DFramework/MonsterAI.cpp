#include "stdafx.h"
#include "MonsterAI.h"
#include "Unit.h"

// ����AI�� ������ �ִ� ���� ����Ʈ
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
    if (target == nullptr)
    {
        target = unit->GetLastAttacker();

        if (target != nullptr)
        {
            // ���� ���ͷ� ���� �ݰ� 2 �ȿ� �ִ� ��� ���Ͱ� �����ڸ� Ÿ������ ����
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
        unit->SetAttackTarget(target);
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
