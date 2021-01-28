#include "stdafx.h"
#include "PlayerController.h"
#include "Collider.h"
#include "NavMeshAgent.h"
#include "NavNode.h"
#include "Unit.h"
#include "Indicator.h"

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

    
    if (InputManager::GetKeyDown('W'))
    {
        
    }
    if (InputManager::GetKeyDown('A'))
    {
        SetTargetMode(!targetMode);
    }
    if (InputManager::GetKeyDown('S'))
    {
        
    }
    if (InputManager::GetKeyDown('D'))
    {
        
    }

    if (InputManager::GetKeyDown('Q'))
    {
        
    }
    if (InputManager::GetKeyDown('E'))
    {
        
    }
    
    if (InputManager::GetKeyDown('L'))
    {
        ObjectManager::SetVisibleCollider(!ObjectManager::IsVisibleCollider());
    }


    if (InputManager::GetMouseWheelUp())
    {
        Camera* cam = Camera::GetInstance();
        cam->Move(cam->transform->look ,10.f);
    }
    else if (InputManager::GetMouseWheelDown())
    {
        Camera* cam = Camera::GetInstance();
        cam->Move(-cam->transform->look ,10.f);
    }

    if (InputManager::GetMouseLButtonDown())
    {
        Ray ray = Camera::main->ScreenPointToRay(InputManager::GetMousePosition());
        RaycastHit hit;
        int groundMask = LayerMask::GetMask(Layer::Ground);
        if (Physics::Raycast(ray, &hit, INFINITY, groundMask))
        {
            printf("%.2f,%.2f,%.2f\n", hit.point.x, hit.point.y, hit.point.z);

        }
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

        SetTargetMode(false);
        
    }
    else if (InputManager::GetMouseRButtonDown())
    {
        Ray ray = Camera::main->ScreenPointToRay(InputManager::GetMousePosition());
        RaycastHit hit;

        int mask = LayerMask::GetMask(Layer::Ground);
        if (Physics::Raycast(ray, &hit, INFINITY, mask))
        {
            
            unit->SetAttackTarget(nullptr);
            agent->SetStoppingDistance(0.05f);
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
        unit->attackIndicator->isVisible = true;
    }
    else
    {
        Cursor::SetMode(CursorMode::Normal);
        unit->attackIndicator->isVisible = false;
    }
}
