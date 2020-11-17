#include "stdafx.h"
#include "Monster.h"
#include "Plane.h"
#include "Rectangle.h"

Monster::Monster()
{
	Mesh* mesh = (Mesh*)AddComponent<PKH::Rectangle>(L"Mesh2");
	
	mesh->SetTexture(TextureKey::SKY_F);
	
}

Monster::~Monster()
{
}

void Monster::Update()
{
	//FaceTarget(Camera::GetInstance());
	GameObject::Update();

	Billboard();
	
}

void Monster::Render()
{
	
	GameObject::Render();
}

void Monster::Billboard()
{

	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);
	matView = Camera::GetViewMatrix();

	memset(&matView._41, 0, sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matView, 0, &matView);

	D3DXVECTOR3 BillPos = transform->position;


	//이동 부분
	memcpy(&matView._41, &BillPos, sizeof(D3DXVECTOR3));
	//이동부분을 반영해줍니다. 다시 좌표의 위치로 이동시켜주는 처리입니다.

	//D2DRenderManager::GetDevice()->SetTransform(D3DTS_WORLD, &matView);
	transform->world = matView;
	//기존의 이동값은 그대로 반영하고, 회전값에 대해서 뷰행렬을 역행렬로
	//변경한 행렬을 월드행렬로 전달합니다.
}
