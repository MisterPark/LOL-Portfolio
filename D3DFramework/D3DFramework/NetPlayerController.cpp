#include "stdafx.h"
#include "NetPlayerController.h"
#include "Collider.h"
#include "NavMeshAgent.h"
#include "NavNode.h"
#include "Unit.h"

NetPlayerController::NetPlayerController(GameObject* owner)
    :IComponent(owner)
{
    net = Network::GetInstance();
    unit = (Unit*)owner;
    agent = (NavMeshAgent*)owner->GetComponent<NavMeshAgent>();
}

NetPlayerController::NetPlayerController(const NetPlayerController& rhs)
    :IComponent(rhs)
{
}

NetPlayerController::~NetPlayerController()
{
    net = nullptr;
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
    if (InputManager::GetKeyDown('D'))
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
        SetTargetMode(false);

        Ray ray = Camera::main->ScreenPointToRay(InputManager::GetMousePosition());
        RaycastHit hit;

        int mask = LayerMask::GetMask(Layer::Ground);
        if (Physics::Raycast(ray, &hit, INFINITY, mask))
        {
            // TODO : 여기부터 ★★★★★★★★
            // ReqMove 해야함
            // 응답은 GameScene에서 받을것

            Vector3 direction = hit.point - transform->position;
            Vector3::Normalize(&direction);

            // 이동
            Ray ray2;
            RaycastHit hit2;
            ray2.origin = transform->position;
            ray2.origin.y += 0.1f;
            ray2.direction = direction;
            float dist = Vector3(hit.point - ray2.origin).Length();
            int mask2 = LayerMask::GetMask(Layer::Wall);
            if (Physics::Raycast(ray2, &hit2, dist, mask2))
            {
                // 직선상에 벽이 있을 경우
                Debug::Print("직선상에 벽이있음\n");
                //agent->SetDestination(_dest);
                ReqMove(hit.point);
            }
            else
            {
                // 직선상에 벽이 없을 경우
                //agent->SetDestination(_dest, true);
                ReqMove(hit.point, true);
            }
            
            
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

void NetPlayerController::ReqMove(Vector3 _dest, bool _noSearch)
{
    list<Vector3> path;
    int pathCount = 0;

    CPacket* pack = new CPacket();
    pack->Clear();
    *pack << (WORD)GAME_REQ_MOVE << net->number;

    if (_noSearch)
    {
        pathCount = 1;
        *pack << pathCount << _dest.x << _dest.y << _dest.z;

    }
    else
    {
        bool res = agent->Search(_dest, &path);
        if (res)
        {
            pathCount = path.size();
            *pack << pathCount;
            
            for (auto iter : path)
            {
                *pack << iter.x << iter.y << iter.z;
            }

            
        }
        else
        {
            pathCount = 1;
            *pack << pathCount << _dest.x << _dest.y << _dest.z;
        }
    }
    Network::SendPacket(pack);
    delete pack;
    Debug::PrintLine("[Debug] ReqMove 요청 / 경유지 : %d", pathCount);
    
}
