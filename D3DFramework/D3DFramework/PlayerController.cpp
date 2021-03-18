#include "stdafx.h"
#include "PlayerController.h"
#include "Collider.h"
#include "NavMeshAgent.h"
#include "NavNode.h"
#include "Unit.h"
#include "Indicator.h"
#include "PlayerInfoPanel.h"

PlayerController::PlayerController(GameObject* owner)
    :IComponent(owner)
{
    unit = (Unit*)owner;
    agent = (NavMeshAgent*)owner->GetComponent<NavMeshAgent>();
}

PlayerController::PlayerController(const PlayerController& rhs)
    :IComponent(rhs)
{
}

PlayerController::~PlayerController()
{
    unit = nullptr;
    agent = nullptr;
}

void PlayerController::Update()
{
    if (gameObject == nullptr)return;

    
    if (Input::GetKeyDown('A'))
    {
        SetTargetMode(!targetMode);
    }
    if (Input::GetKeyDown('S'))
    {
        agent->Stop();
        unit->SetAttackTarget(nullptr);
    }
    if (Input::GetKeyDown('D'))
    {

    }

    if (Input::GetKey(VK_CONTROL))
    {
        if (Input::GetKeyDown('Q'))
        {

        }
        if (Input::GetKeyDown('W'))
        {

        }
        if (Input::GetKeyDown('E'))
        {

        }
        if (Input::GetKeyDown('R'))
        {

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
        if (Physics::Raycast(ray, &info, INFINITY, unitMask))
        {
            if (targetMode)
            {
                Unit* target = (Unit*)info.collider->gameObject;
                if (target->team != unit->team && !target->IsDead())
                {
                    unit->Attack(target);
                }
                   
            }
        }
        else if (Physics::Raycast(ray, &hit, INFINITY, groundMask))
        {
            printf("%.2f,%.2f,%.2f\n", hit.point.x, hit.point.y, hit.point.z);
            if (targetMode)
            {
                Unit* target = unit->GetNearestEnemy(hit.point, 5.f);
                if (target != nullptr)
                {
                    unit->Attack(target);
                }
                else
                {
                    unit->SetAttackTarget(nullptr);
                    agent->SetStoppingDistance(0.1f);
                    unit->SetDestination(hit.point);
                }
            }
        }

        SetTargetMode(false);
        
    }
    else if (Input::GetMouseRButtonDown())
    {
        if (UI::IsPointerOverUI()) return;

        Ray ray = Camera::main->ScreenPointToRay(Input::GetMousePosition());
        RaycastHit hit;

        int mask = LayerMask::GetMask(Layer::Ground);
        if (Physics::Raycast(ray, &hit, INFINITY, mask))
        {
            
            unit->SetAttackTarget(nullptr);
            agent->SetStoppingDistance(0.1f);
            unit->SetDestination(hit.point);
        }
        
        SetTargetMode(false);
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
        unit->attackIndicator->visible = true;
    }
    else
    {
        Cursor::SetMode(CursorMode::Normal);
        unit->attackIndicator->visible = false;
    }
}
