#include "stdafx.h"
#include "PlayerController.h"
#include "Collider.h"
#include "NavMeshAgent.h"
#include "NavNode.h"
#include "Unit.h"

PlayerController::PlayerController(GameObject* owner)
    :IComponent(owner)
{
    agent = (NavMeshAgent*)owner->GetComponent<NavMeshAgent>();
}

PlayerController::PlayerController(const PlayerController& rhs)
    :IComponent(rhs)
{
}

PlayerController::~PlayerController()
{
    agent = nullptr;
}

void PlayerController::Update()
{
    if (gameObject == nullptr)return;

    
    if (InputManager::GetKey('W'))
    {
        //gameObject->transform->position.z += 10.f* TimeManager::DeltaTime();
        transform->position += transform->look * 10.f * TimeManager::DeltaTime();
    }
    if (InputManager::GetKey('A'))
    {
        //gameObject->transform->position.x -= 10.f * TimeManager::DeltaTime();
        gameObject->transform->eulerAngles.y -= D3DXToRadian(10);// *TimeManager::DeltaTime();
    }
    if (InputManager::GetKey('S'))
    {
        gameObject->transform->position.z -= 10.f * TimeManager::DeltaTime();
    }
    if (InputManager::GetKey('D'))
    {
        //gameObject->transform->position.x += 10.f * TimeManager::DeltaTime();
        gameObject->transform->eulerAngles.y += D3DXToRadian(10);// *TimeManager::DeltaTime();
    }

    if (InputManager::GetKey('Q'))
    {
        Camera::GetInstance()->transform->position.x -= TimeManager::DeltaTime();
    }
    if (InputManager::GetKey('E'))
    {
        Camera::GetInstance()->transform->position.x += TimeManager::DeltaTime();
    }
    // TODO : (DEBUG CODE) 나중에 삭제해야함
    //if (InputManager::GetKeyDown('L'))
    //{
    //    NavNodeManager::LinkNode();
    //}
    //if (InputManager::GetKeyDown('K'))
    //{
    //    NavNodeManager::LinkAll();
    //}
    //if (InputManager::GetKey(VK_F5))
    //{
    //    NavNodeManager::Save();
    //}
    //if (InputManager::GetKey(VK_F6))
    //{
    //    NavNodeManager::LoadDebug();
    //}
    //if (InputManager::GetKeyDown(VK_DELETE))
    //{
    //    NavNodeManager::DeleteSelectedNodes();
    //}
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

            if (InputManager::GetKey(VK_CONTROL))
            {
                GameObject* obj = ObjectManager::GetInstance()->CreateObject<NavNode>(Layer::Node);
                obj->transform->position = hit.point;
                NavNodeManager::AddNode((NavNode*)obj);
            }
        }

        // TODO : (DEBUG CODE) 네비메쉬 길찾기 끝나면 지울것
        //RaycastHit info;
        //int mask = LayerMask::GetMask(Layer::Node);
        //if (Physics::Raycast(ray, &info, INFINITY, mask))
        //{
        //    
        //    if (InputManager::GetKey(VK_LSHIFT))
        //    {
        //        NavNode* node = (NavNode*)info.collider->gameObject;
        //        NavNodeManager::SelectNode(node);
        //    }
        //    
        //}
        //else
        //{
        //    NavNodeManager::ClearSelectedNodes();
        //}

        
        
        
    }
    else if (InputManager::GetMouseRButtonDown())
    {
        Ray ray = Camera::main->ScreenPointToRay(InputManager::GetMousePosition());
        RaycastHit hit;

        int mask = LayerMask::GetMask(Layer::Ground);
        if (Physics::Raycast(ray, &hit, INFINITY, mask))
        {
            // 회전
            Vector3 direction = hit.point - transform->position;
            Vector3::Normalize(&direction);
            float angle = Vector3::AngleY(Vector3(0,0,1), direction);
            gameObject->transform->eulerAngles.y = angle;
            
            // 이동
            Ray ray2;
            RaycastHit hit2;
            ray2.origin = gameObject->transform->position;
            ray2.origin.y += 0.1f;
            ray2.direction = direction;
            float dist = Vector3(hit.point - ray2.origin).Length();
            int mask2 = LayerMask::GetMask(Layer::Wall);
            if (Physics::Raycast(ray2, &hit2, dist, mask2))
            {
                // 직선상에 벽이 있을 경우
                Debug::Print("직선상에 벽이있음\n");
                agent->SetDestination(hit.point);
            }
            else
            {
                // 직선상에 벽이 없을 경우
                agent->SetDestination(hit.point,true);
            }
        }
        
    }
}

IComponent* PlayerController::Clone()
{
    return new PlayerController(*this);
}
