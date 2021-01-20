#include "stdafx.h"
#include "NetPlayerController.h"
#include "Collider.h"
#include "NavMeshAgent.h"
#include "NavNode.h"
#include "Unit.h"

NetPlayerController::NetPlayerController(GameObject* owner)
    :IComponent(owner)
{
    unit = (Unit*)owner;
    agent = (NavMeshAgent*)owner->GetComponent<NavMeshAgent>();
}

NetPlayerController::NetPlayerController(const NetPlayerController& rhs)
    :IComponent(rhs)
{
}

NetPlayerController::~NetPlayerController()
{
    unit = nullptr;
    agent = nullptr;
}

void NetPlayerController::Update()
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
    if (InputManager::GetKey('D'))
    {

    }

    if (InputManager::GetKeyDown('Q'))
    {

    }
    if (InputManager::GetKeyDown('E'))
    {

    }



    if (InputManager::GetMouseWheelUp())
    {
        Camera* cam = Camera::GetInstance();
        cam->Move(cam->transform->look, 10.f);
    }
    else if (InputManager::GetMouseWheelDown())
    {
        Camera* cam = Camera::GetInstance();
        cam->Move(-cam->transform->look, 10.f);
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
        int unitMask = LayerMask::GetMask(Layer::EnemyUnit);
        if (Physics::Raycast(ray, &info, INFINITY, unitMask))
        {
            if (targetMode)
            {
                SetTargetMode(false);
                unit->Attack((Unit*)info.collider->gameObject);
            }
        }
        else
        {
            SetTargetMode(false);
        }



    }
    else if (InputManager::GetMouseRButtonDown())
    {

        Ray ray = Camera::main->ScreenPointToRay(InputManager::GetMousePosition());
        RaycastHit hit;

        int mask = LayerMask::GetMask(Layer::Ground);
        if (Physics::Raycast(ray, &hit, INFINITY, mask))
        {
            // TODO : 여기부터 ★★★★★★★★
            // ReqMove 해야함
            // 응답은 GameScene에서 받을것
            SetTargetMode(false);
            unit->SetAttackTarget(nullptr);
            agent->SetStoppingDistance(0.03f);
            unit->SetDestination(hit.point);
        }

    }
}

IComponent* NetPlayerController::Clone()
{
    return new NetPlayerController(*this);
}

void NetPlayerController::SetTargetMode(bool _mode)
{
    targetMode = _mode;
    if (targetMode)
    {
        Cursor::SetMode(CursorMode::SingleTarget);
    }
    else
    {
        Cursor::SetMode(CursorMode::Normal);
    }
}
