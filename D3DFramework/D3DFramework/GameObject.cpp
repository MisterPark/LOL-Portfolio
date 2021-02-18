#include "stdafx.h"
#include "GameObject.h"
#include "IComponent.h"
#include "transform.h"
#include "StaticMesh.h"
#include "Collider.h"

using namespace PKH;

PKH::GameObject::GameObject()
{
	transform = (Transform*)AddComponent<Transform>(L"Transform");
}

PKH::GameObject::~GameObject()
{
	ReleaseComponents();

	for (auto& iter : children)
	{
		//Safe_Delete(&iter.second);
		delete iter.second;
	}
	children.clear();
}

void PKH::GameObject::Update()
{
	for (auto& comp : components)
	{
		comp.second->Update();
	}

	for (auto iter : children)
	{
		iter.second->Update();
	}
}

void PKH::GameObject::PostUpdate()
{
	for (auto& comp : components)
	{
		comp.second->PostUpdate();
	}

	for (auto iter : children)
	{
		iter.second->PostUpdate();
	}
}



void PKH::GameObject::Destroy()
{
	if (dontDestroy) return;
	destroyFlag = true;
}

void PKH::GameObject::OnCollisionEnter(Collider* target)
{


}

void PKH::GameObject::Move(Vector3 _direction)
{
	Vector3::Normalize(&_direction);
	transform->position.x += _direction.x * TimeManager::DeltaTime();
	transform->position.y += _direction.y * TimeManager::DeltaTime();
	transform->position.z += _direction.z * TimeManager::DeltaTime();
}

void PKH::GameObject::Move(Vector3 _direction, float _speed)
{
	Vector3::Normalize(&_direction);
	transform->position.x += _direction.x * _speed * TimeManager::DeltaTime();
	transform->position.y += _direction.y * _speed * TimeManager::DeltaTime();
	transform->position.z += _direction.z * _speed * TimeManager::DeltaTime();
}

void PKH::GameObject::MoveToTarget(Vector3 _target)
{
	Vector3 dir = _target - transform->position;
	Vector3::Normalize(&dir);
	transform->position.x += dir.x * TimeManager::DeltaTime();
	transform->position.y += dir.y * TimeManager::DeltaTime();
	transform->position.z += dir.z * TimeManager::DeltaTime();
}

void PKH::GameObject::MoveToTarget(Vector3 _target, float _speed)
{
	Vector3 dir = _target - transform->position;
	Vector3::Normalize(&dir);
	transform->position.x += dir.x * _speed * TimeManager::DeltaTime();
	transform->position.y += dir.y * _speed * TimeManager::DeltaTime();
	transform->position.z += dir.z * _speed * TimeManager::DeltaTime();
}

void PKH::GameObject::FollowTarget(const GameObject* _target)
{
	MoveToTarget(_target->transform->position);
}

void PKH::GameObject::FollowTarget(const Transform& _targetTransform)
{
	MoveToTarget(_targetTransform.position);
}

void PKH::GameObject::FollowTarget(const Vector3& _targetPos)
{
	MoveToTarget(_targetPos);
}

void PKH::GameObject::FaceTarget(const GameObject* _target)
{
	transform->LookAt(_target->transform->position);
}

void PKH::GameObject::FaceTarget(const Transform& _targetTransform)
{
	transform->LookAt(_targetTransform.position);
}

void PKH::GameObject::FaceTarget(const Vector3& _targetPos)
{
	transform->LookAt(_targetPos);
}

void PKH::GameObject::Billboard()
{
	D3DXMATRIX matScale, matView;
	D3DXMatrixIdentity(&matView);
	matView = Camera::main->GetViewMatrix();

	memset(&matView._41, 0, sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matView, 0, &matView);

	D3DXVECTOR3 BillPos = transform->position;
	D3DXMatrixScaling(&matScale, transform->scale.x, transform->scale.y, transform->scale.z);

	//이동 부분
	memcpy(&matView._41, &BillPos, sizeof(D3DXVECTOR3));
	//이동부분을 반영해줍니다. 다시 좌표의 위치로 이동시켜주는 처리입니다.

	//RenderManager::SetTransform(D3DTS_WORLD, &matView);
	transform->localMatrix = matScale*matView;
}

void PKH::GameObject::BillboardYaw()
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


void PKH::GameObject::SetPosition(Vector3 _vPos)
{
	transform->position = _vPos;
}

void PKH::GameObject::Show()
{
	isVisible = true;
}

void PKH::GameObject::Hide()
{
	isVisible = false;
}

IComponent* PKH::GameObject::AddComponent(const wstring& _key, IComponent* _component)
{
	if (_component == nullptr) return nullptr;
	_component->gameObject = this;
	_component->transform = this->transform;
	components[_key] = _component;
	return _component;
}

void PKH::GameObject::ReleaseComponents()
{
	auto iter = components.begin();
	auto end = components.end();
	for (; iter != end;++iter)
	{
		delete iter->second;
	}
	components.clear();
}

void PKH::GameObject::RemoveComponent(IComponent* _target)
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
}

void PKH::GameObject::RemoveComponent(const wstring& _key)
{
	components.erase(_key);
}

IComponent* PKH::GameObject::GetComponent(const wstring& _key)
{
	auto f = components.find(_key);
	if (f == components.end()) return nullptr;
	return f->second;
}

bool PKH::GameObject::IsDestroy()
{
	return destroyFlag;
}

bool PKH::GameObject::SetLayer(Layer _layer)
{
	if (this->layer == _layer) return false;

	this->layer = _layer;
	ObjectManager::RemoveObject(this);
	ObjectManager::AddObject(this, _layer);
	for (auto iter : components)
	{
		IComponent* comp = iter.second;
		Collider* collider = dynamic_cast<Collider*>(comp);
		if (collider == nullptr) continue;

		collider->SetLayer(_layer);
	}

	return true;
}

void PKH::GameObject::SetParent(GameObject* _parent)
{
	this->parent = _parent;
}
