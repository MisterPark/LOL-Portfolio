﻿#include "stdafx.h"
#include "PlayerController.h"
#include "Collider.h"
#include "NavMeshAgent.h"
#include "NavNode.h"
#include "Unit.h"
#include "Indicator.h"
#include "PlayerInfoPanel.h"
#include "TargetingSkill.h"
#include "Inventory.h"
#include "Skill_Attack.h"
#include "Skill_RangeAttack.h"
#include "MonoRenderer.h"
#include "ArrowPointer.h"

PlayerController::PlayerController(GameObject* owner)
    :IComponent(owner)
{
    unit = (Unit*)owner;
    agent = (NavMeshAgent*)owner->GetComponent<NavMeshAgent>();

    MonoRenderer* monoRenderer = new MonoRenderer(unit);
    unit->AddComponent(L"monoRenderer", monoRenderer);
    ArrowPointer* arrow = ArrowPointer::GetInstance();
    SceneManager::GetCurrentScene()->AddObject(arrow);
}

PlayerController::PlayerController(const PlayerController& rhs)
    :IComponent(rhs)
{
}

PlayerController::~PlayerController()
{
    unit = nullptr;
    agent = nullptr;
    ArrowPointer* arrow = ArrowPointer::GetInstance();
    SceneManager::GetCurrentScene()->RemoveObject(arrow);
}

void PlayerController::Update()
{
    if (enable == false) return;
    if (gameObject == nullptr)return;

    if (Input::GetKeyDown('A'))
    {
        unit->Attack();
    }
    if (Input::GetKeyDown('S'))
    {
        agent->Stop();
        unit->SetAttackTarget(nullptr);
    }

    if (Input::GetKey(VK_CONTROL))
    {
        if (Input::GetKeyDown('Q'))
        {
            unit->SkillLevelUp(SkillIndex::Q);
        }
        if (Input::GetKeyDown('W'))
        {
            unit->SkillLevelUp(SkillIndex::W);
        }
        if (Input::GetKeyDown('E'))
        {
            unit->SkillLevelUp(SkillIndex::E);
        }
        if (Input::GetKeyDown('R'))
        {
            unit->SkillLevelUp(SkillIndex::R);
        }
    }
    else
    {
        if (Input::GetKeyDown('Q'))
        {
            unit->Spell1();
        }
        if (Input::GetKeyDown('W'))
        {
            unit->Spell2();
        }
        if (Input::GetKeyDown('E'))
        {
            unit->Spell3();
        }
        if (Input::GetKeyDown('R'))
        {
            unit->Spell4();
        }
        if (Input::GetKeyDown('D'))
        {
            unit->Spell5();
        }
        if (Input::GetKeyDown('F'))
        {
            unit->Spell6();
        }
    }

    if (Input::GetKeyDown('1'))
    {
        if (unit->inventory.GetItem(0))
            unit->inventory.GetItem(0)->skillList.front()->Use();
    }
    if (Input::GetKeyDown('2'))
    {
        if (unit->inventory.GetItem(1))
            unit->inventory.GetItem(1)->skillList.front()->Use();
    }
    if (Input::GetKeyDown('3'))
    {
        if (unit->inventory.GetItem(2))
            unit->inventory.GetItem(2)->skillList.front()->Use();
    }
    if (Input::GetKeyDown('4'))
    {
        if (unit->inventory.GetItem(3))
            unit->inventory.GetItem(3)->skillList.front()->Use();
    }
    if (Input::GetKeyDown('5'))
    {
        if (unit->inventory.GetItem(4))
            unit->inventory.GetItem(4)->skillList.front()->Use();
    }
    if (Input::GetKeyDown('6'))
    {
        if (unit->inventory.GetItem(5))
            unit->inventory.GetItem(5)->skillList.front()->Use();
    }
    if (Input::GetKeyDown('7'))
    {
        if (unit->inventory.GetItem(6))
            unit->inventory.GetItem(6)->skillList.front()->Use();
    }
    

    if (Input::GetMouseWheelUp())
    {
        Camera* cam = Camera::GetInstance();
        cam->Move(cam->transform->look ,10.f);
    }
    else if (Input::GetMouseWheelDown())
    {
        Camera* cam = Camera::GetInstance();
        cam->Move(-cam->transform->look ,10.f);
    }

    if (Input::GetMouseLButtonDown())
    {
        Ray ray = Camera::main->ScreenPointToRay(Input::GetMousePosition());
        RaycastHit hit;
        int groundMask = LayerMask::GetMask(Layer::Ground);
        
        RaycastHit info;
        int unitMask = LayerMask::GetMask(Layer::Unit, Layer::Building);

        bool targetCheck = false;
        if (Physics::Raycast(ray, &info, INFINITY, unitMask))
        {
            if (targetMode)
            {
                Unit* target = (Unit*)info.collider->gameObject;
                /*if (target->team != unit->team && !target->IsDead())
                {
                    unit->SetAttackTarget(target);
                    unit->SetAttackPoint(target->transform->position);
                }*/
                if (!target->IsDead())
                {
                    if (unit->nextSkillReady != nullptr && unit->nextSkillReady->TargetingSuccess(target)) {
                        targetCheck = true;
                        unit->SetAttackTarget(target);
                        unit->SetAttackPoint(target->transform->position);
                    }
                }
                   
            }
        }
        if (!targetCheck && unit->nextSkillReady != nullptr && !((TargetingSkill*)unit->nextSkillReady)->GetGroundClick()) {
            // 스킬쓰고 타겟팅했을때 어택땅이되서 방지
        }
        else if (!targetCheck && Physics::Raycast(ray, &hit, INFINITY, groundMask))
        {
            printf("%.2f,%.2f,%.2f\n", hit.point.x, hit.point.y, hit.point.z);
            if (targetMode)
            {
                Unit* target = nullptr;
                if(((Unit*)gameObject)->skillList[(int)SkillIndex::Attack] == unit->nextSkillReady)
                    target = unit->GetNearestEnemy(hit.point, 5.f);
                if (target != nullptr)
                {
                    unit->GetSkillAttack()->Cancle();
                    unit->SetAttackTarget(target);
                    targetCheck = true;
                }
                else
                {
                    unit->SetAttackTarget(nullptr);
                    agent->SetStoppingDistance(0.1f);
                    unit->SetDestination(hit.point);
                    unit->SetAttackPoint(Vector3{ hit.point.x, hit.point.y, hit.point.z });
                    if(((TargetingSkill*)unit->nextSkillReady)->GetGroundClick())
                        targetCheck = true;
                    
                }
            }
        }

        if (targetCheck) {
            SetTargetMode(false);
            unit->TakeNextSkill();
        }
        
    }
    else if (Input::GetMouseRButtonDown())
    {
        if (!EventSystem::IsPointerOverGameObject()) {

            Ray ray = Camera::main->ScreenPointToRay(Input::GetMousePosition());
            RaycastHit hit;

            int mask = LayerMask::GetMask(Layer::Ground);
            if (Physics::Raycast(ray, &hit, INFINITY, mask))
            {
                Skill_Attack* attack = unit->GetSkillAttack();
                if (attack != nullptr)
                {
                    attack->Cancle();
                }

                unit->SetAttackTarget(nullptr);
                agent->SetStoppingDistance(0.1f);
                unit->SetDestination(hit.point);

                ArrowPointer::GetInstance()->transform->position = hit.point;
                ArrowPointer::GetInstance()->Show();
            }

            SetTargetMode(false);
        }
    }

    auto monoRenderer = dynamic_cast<MonoRenderer*>(unit->GetComponent(L"monoRenderer"));
    if (monoRenderer) monoRenderer->enable = unit->IsDead();

    // 자동공격
    if (unit->IsDead() == false)
    {
        Unit* attackTarget = unit->GetAttackTarget();
        Skill* nextSkill = unit->nextSkillReady;

        if (attackTarget == nullptr)
        {
            float attackRange = unit->stat->GetValue(StatType::Range);
            Unit* attackTarget = unit->GetNearestEnemy(transform->position, attackRange);
        }
        
        if (attackTarget != nullptr)
        {
            if (attackTarget->IsDead())
            {
                unit->SetAttackTarget(nullptr);

            }
            else
            {
                unit->GetSkillAttack()->Start();
            }
           
        }
    }
    
}

IComponent* PlayerController::Clone()
{
    return new PlayerController(*this);
}

void PlayerController::SetTargetMode(bool _mode)
{
    targetMode = _mode;
    if (targetMode)
    {
        Cursor::SetMode(CursorMode::SingleTarget);
        //unit->attackIndicator->visible = true;
    }
    else
    {
        Cursor::SetMode(CursorMode::Normal);
        //unit->attackIndicator->visible = false;
    }
}

void PlayerController::SetTargetingSkill(TargetingSkill* _targetingSkill)
{
    this->targetingSkill = _targetingSkill;
}
