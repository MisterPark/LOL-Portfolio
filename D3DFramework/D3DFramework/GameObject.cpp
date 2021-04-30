#include "stdafx.h"
#include "GameObject.h"
#include "IComponent.h"
#include "transform.h"
#include "StaticMesh.h"
#include "Collider.h"

using namespace Engine;

list<GameObject*> GameObject::gameObjects;

Engine::GameObject::GameObject()
{
	gameObjects.push_back(this);
	transform = (Transform*)AddComponent<Transform>(L"Transform");
}

Engine::GameObject::~GameObject()
{
	gameObjects.remove(this);
	ReleaseComponents();

	for (auto& iter : children)
	{
		//Safe_Delete(&iter.second);
		if(iter.second) delete iter.second;
	}
	children.clear();

	for (auto* evt : events)
	{
		evt->RemoveTarget(this);
	}
}

void Engine::GameObject::PreUpdate()
{
	for (auto& comp : components)
	{
		if (comp.second == nullptr) continue;
		if (comp.second->enable == false) continue;
		comp.second->PreUpdate();
	}
	for (auto& iter : children)
	{
		if (iter.second == nullptr) continue;
		iter.second->PreUpdate();
	}
}

void Engine::GameObject::Update()
{
	for (auto& comp : components)
	{
		if (comp.second == nullptr) continue;
		if (comp.second->enable == false) continue;
		comp.second->Update();
	}

	for (auto& iter : children)
	{
		if (iter.second == nullptr) continue;
		iter.second->Update();
	}
}

void Engine::GameObject::PostUpdate()
{
	for (auto& comp : components)
	{
		if (comp.second == nullptr) continue;
		if (comp.second->enable == false) continue;
		comp.second->PostUpdate();
	}

	for (auto& iter : children)
	{
		if (iter.second == nullptr) continue;
		iter.second->PostUpdate();
	}
}



void Engine::GameObject::Destroy()
{
	if (dontDestroy) return;
	destroyFlag = true;
}

void Engine::GameObject::OnCollisionEnter(Collider* target)
{


}

void Engine::GameObject::OnHover()
{
	isLeave = false;
	isHover = true;
	MouseEventArg args{};
	Hover.Invoke(this, args);
}

void Engine::GameObject::OnLeave()
{
	isHover = false;
	isLeave = true;
	MouseEventArg args{};
	Leave.Invoke(this, args);
}

void Engine::GameObject::Move(Vector3 _direction)
{
	Vector3::Normalize(&_direction);
	transform->position.x += _direction.x * Time::DeltaTime();
	transform->position.y += _direction.y * Time::DeltaTime();
	transform->position.z += _direction.z * Time::DeltaTime();
}

void Engine::GameObject::Move(Vector3 _direction, float _speed)
{
	Vector3::Normalize(&_direction);
	transform->position.x += _direction.x * _speed * Time::DeltaTime();
	transform->position.y += _direction.y * _speed * Time::DeltaTime();
	transform->position.z += _direction.z * _speed * Time::DeltaTime();
}

void Engine::GameObject::MoveToTarget(Vector3 _target)
{
	Vector3 dir = _target - transform->position;
	Vector3::Normalize(&dir);
	transform->position.x += dir.x * Time::DeltaTime();
	transform->position.y += dir.y * Time::DeltaTime();
	transform->position.z += dir.z * Time::DeltaTime();
}

void Engine::GameObject::MoveToTarget(Vector3 _target, float _speed)
{
	Vector3 dir = _target - transform->position;
	Vector3::Normalize(&dir);
	transform->position.x += dir.x * _speed * Time::DeltaTime();
	transform->position.y += dir.y * _speed * Time::DeltaTime();
	transform->position.z += dir.z * _speed * Time::DeltaTime();
}

void Engine::GameObject::FollowTarget(const GameObject* _target)
{
	MoveToTarget(_target->transform->position);
}

void Engine::GameObject::FollowTarget(const Transform& _targetTransform)
{
	MoveToTarget(_targetTransform.position);
}

void Engine::GameObject::FollowTarget(const Vector3& _targetPos)
{
	MoveToTarget(_targetPos);
}

void Engine::GameObject::FaceTarget(const GameObject* _target)
{
	transform->LookAt(_target->transform->position);
}

void Engine::GameObject::FaceTarget(const Transform& _targetTransform)
{
	transform->LookAt(_targetTransform.position);
}

void Engine::GameObject::FaceTarget(const Vector3& _targetPos)
{
	transform->LookAt(_targetPos);
}

void Engine::GameObject::Billboard()
{
	//D3DXMATRIX matScale, matView;
	//D3DXMatrixIdentity(&matView);
	//matView = Camera::main->GetViewMatrix();

	//memset(&matView._41, 0, sizeof(D3DXVECTOR3));
	//D3DXMatrixInverse(&matView, 0, &matView);

	//D3DXVECTOR3 BillPos = transform->position;
	//D3DXMatrixScaling(&matScale, transform->scale.x, transform->scale.y, transform->scale.z);

	////이동 부분
	//memcpy(&matView._41, &BillPos, sizeof(D3DXVECTOR3));
	////이동부분을 반영해줍니다. 다시 좌표의 위치로 이동시켜주는 처리입니다.

	//RenderManager::SetTransform(D3DTS_WORLD, &matView);
	//transform->localMatrix = matScale*matView;

	//=====================================
	Vector3 camDir = Camera::main->GetOffset();
	Vector3::Normalize(&camDir);
	//camDir = -camDir;
	transform->Rotate(camDir);
}

void Engine::GameObject::BillboardYaw()
{
	D3DXMATRIX matScale, matView, matBill;
	
	matView = Matrix::identity;
	matView = Camera::main->GetViewMatrix();
	memset(&matBill._41, 0, sizeof(D3DXVECTOR3));

	matBill = Matrix::identity;
	// 뷰행렬의 Y축 회전행렬값만 가지고오기
	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	
	//스케일
	D3DXMatrixScaling(&matScale, transform->scale.x, transform->scale.y, transform->scale.z);


	// 이동
	D3DXVECTOR3 BillPos = transform->position;
	memcpy(&matBill._41, &BillPos, sizeof(D3DXVECTOR3));
	transform->localMatrix = matScale * matBill;


}


void Engine::GameObject::SetPosition(Vector3 _vPos)
{
	transform->position = _vPos;
}

void Engine::GameObject::Show()
{
	auto iter = components.begin();
	auto end = components.end();
	for (; iter != end; ++iter)
	{
		auto comp = dynamic_cast<Renderer*>(iter->second);
		if (comp == nullptr) continue;
		comp->visible = true;
	}

	for (auto& child : children)
	{
		if(child.second) child.second->Show();
	}
	visible = true;
}

void Engine::GameObject::Show(bool _visible)
{
	auto iter = components.begin();
	auto end = components.end();
	for (; iter != end; ++iter)
	{
		auto comp = dynamic_cast<Renderer*>(iter->second);
		if (comp == nullptr) continue;
		comp->visible = _visible;
	}

	for (auto& child : children)
	{
		if(child.second) child.second->Show(_visible);
	}
	visible = _visible;
}

void Engine::GameObject::Hide()
{
	auto iter = components.begin();
	auto end = components.end();
	for (; iter != end; ++iter)
	{
		auto comp = dynamic_cast<Renderer*>(iter->second);
		if (comp == nullptr) continue;
		comp->visible = false;
	}

	for (auto& child : children)
	{
		if(child.second) child.second->Hide();
	}
	visible = false;
}

void Engine::GameObject::DeleteChild(const wstring& _tag)
{
	auto find = children.find(_tag.c_str());
	if (find != children.end())
	{
		delete find->second;
		children.erase(find);
	}
}

GameObject* Engine::GameObject::RemoveChild(const wstring& _tag)
{
	auto find = children.find(_tag.c_str());
	if (find != children.end())
	{
		children.erase(find);
		return find->second;
	}
	return nullptr;
}

void Engine::GameObject::AddWeak(Engine::EventBase* evt)
{
	evt->AddWeakRef(this, &GameObject::OnEventDelete);
	events.emplace(evt);
}

void Engine::GameObject::OnEventDelete(Engine::EventBase* evt)
{
	events.erase(evt);
}

void Engine::GameObject::Freeze()
{
	for (auto& comp : components)
	{
		if (dynamic_cast<Transform*>(comp.second)) continue;
		comp.second->enable = false;
	}

	for (auto& child : children)
	{
		child.second->Freeze();
	}
}

IComponent* Engine::GameObject::AddComponent(const wstring& _key, IComponent* _component)
{
	if (_component == nullptr) return nullptr;
	_component->gameObject = this;
	_component->transform = this->transform;
	components[_key] = _component;
	return _component;
}

void Engine::GameObject::ReleaseComponents()
{
	auto iter = components.begin();
	auto end = components.end();
	for (; iter != end;++iter)
	{
		delete iter->second;
	}
	components.clear();
}

IComponent* Engine::GameObject::RemoveComponent(IComponent* _target)
{
	auto iter = components.begin();
	auto end = components.end();
	for (; iter != end;++iter)
	{
		if (iter->second == _target)
		{
			components.erase(iter);
			break;
		}
	}

	return _target;
}

IComponent* Engine::GameObject::RemoveComponent(const wstring& _key)
{
	IComponent* target = nullptr;
	auto end = components.end();
	auto find = components.find(_key);
	if (find == end) return target;
	
	target = find->second;
	components.erase(_key);
	return target;
}

void Engine::GameObject::DeleteComponent(IComponent* _target)
{
	auto iter = components.begin();
	auto end = components.end();
	for (; iter != end; ++iter)
	{
		if (iter->second == _target)
		{
			components.erase(iter);
			break;
		}
	}

	delete _target;
}

void Engine::GameObject::DeleteComponent(const wstring& _key)
{
	auto end = components.end();
	auto find = components.find(_key);
	if (find == end) return;

	delete find->second;
	components.erase(_key);
}

IComponent* Engine::GameObject::GetComponent(const wstring& _key)
{
	auto f = components.find(_key);
	if (f == components.end()) return nullptr;
	return f->second;
}

bool Engine::GameObject::IsDestroy()
{
	return destroyFlag;
}

bool Engine::GameObject::IsRemove()
{
	return removeFlag;
}

void Engine::GameObject::SetRemove(bool _remove)
{
	removeFlag = _remove;
}

bool Engine::GameObject::IsVisible()
{
	return visible;
}

bool Engine::GameObject::IsHover()
{
	return isHover;
}

bool Engine::GameObject::IsLeave()
{
	return isLeave;
}

bool Engine::GameObject::SetLayer(Layer _layer)
{
	//SceneManager::GetCurrentScene()->ChangeLayer(this, layer, _layer);
	this->layer = _layer;
	for (auto& iter : components)
	{
		IComponent* comp = iter.second;
		Collider* collider = dynamic_cast<Collider*>(comp);
		if (collider == nullptr) continue;

		collider->SetLayer(_layer);
	}

	return true;
}

void Engine::GameObject::SetParent(GameObject* _parent)
{
	this->parent = _parent;
}
