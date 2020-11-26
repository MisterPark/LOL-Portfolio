#include "stdafx.h"
#include "PlayerController.h"
#include "Collider.h"


PlayerController::PlayerController(GameObject* owner)
    :IComponent(owner)
{
}

PlayerController::PlayerController(const PlayerController& rhs)
    :IComponent(rhs)
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Update()
{
    if (gameObject == nullptr)return;
    
    if (InputManager::GetKey('W'))
    {
        gameObject->transform->position.z +=  TimeManager::DeltaTime();
    }
    if (InputManager::GetKey('A'))
    {
        gameObject->transform->position.x -=  TimeManager::DeltaTime();
    }
    if (InputManager::GetKey('S'))
    {
        gameObject->transform->position.z -=  TimeManager::DeltaTime();
    }
    if (InputManager::GetKey('D'))
    {
        gameObject->transform->position.x +=  TimeManager::DeltaTime();
    }

    if (InputManager::GetKey('Q'))
    {
        Camera::GetInstance()->transform->position.x -= TimeManager::DeltaTime();
    }
    if (InputManager::GetKey('E'))
    {
        Camera::GetInstance()->transform->position.x += TimeManager::DeltaTime();
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

    if (InputManager::GetMouseLButton())
    {
        Ray ray = Camera::ScreenPointToRay(InputManager::GetMousePosition());
        RaycastHit hit;
        if (Physics::Raycast(ray, &hit))
        {
            printf("%f\n", hit.distance);
            hit.collider->SetColor(D3DCOLOR_ARGB(255, 255, 0, 0));
        }
    }
}

IComponent* PlayerController::Clone()
{
    return new PlayerController(*this);
}
