#include "stdafx.h"
#include "EventSystem.h"
#include "GameObject.h"
#include "UI.h"
#include "Unit.h"
#include "Collider.h"

EventSystem* self = nullptr;
bool EventSystem::isPointerOverGameObject = false;

EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{
}

EventSystem* EventSystem::GetInstance()
{
    if (self == nullptr)
    {
        self = new EventSystem();
    }
    return self;
}

void EventSystem::Destroy()
{
    if (self)
    {
        delete self;
        self = nullptr;
    }
}

void EventSystem::Clear()
{
    EventSystem::isPointerOverGameObject = false;
}

void EventSystem::Update()
{
    CheckPointerOverGameObject();

    auto& objList = UI::uiList;
    for (auto& obj : objList)
    {
        obj->UpdateEvent();
    }
}

bool EventSystem::IsPointerOverGameObject()
{
    Vector3 cursorPos = Cursor::GetMousePos();
    auto& uiList = UI::uiList;
    for (auto& ui : uiList)
    {
        if (dynamic_cast<Cursor*>(ui)) continue;
        if (ui->IsVisible() == false) continue;
        if (ui->Intersect(cursorPos) == false) continue;

        return true;
    }
    return false;
}

void Engine::EventSystem::CheckPointerOverGameObject()
{
	GameObject* target = nullptr;
	Ray ray = Camera::main->ScreenPointToRay(Input::GetMousePosition());
	RaycastHit info;
	int unitMask = LayerMask::GetMask(Layer::Unit, Layer::Building);
	if (Physics::Raycast(ray, &info, INFINITY, unitMask))
	{
		target = info.collider->gameObject;
	}

	auto& unitList = Unit::unitList;
	for (auto& unit : unitList)
	{
		if (target == nullptr || target != unit)
		{
			if (unit->IsLeave()) continue;
            unit->OnLeave();
		}
		else
		{
			if (unit->IsHover()) continue;
            unit->OnHover();
		}
	}
}
