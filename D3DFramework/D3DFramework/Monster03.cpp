#include "stdafx.h"
#include "Monster03.h"
#include "Player03.h"
#include "Bullet03.h"
#include "Cube.h"
#include "ObjectManager.h"
#include "CollisionManager03.h"
PKH::Monster03::Monster03()
{
	transform->scale = { 1.f,1.f,1.f};
	hp = 2;
}



PKH::Monster03::~Monster03()
{
}

void PKH::Monster03::Update()
{
	GameObject* player = ObjectManager::GetInstance()->FindObject<Player03>();
	if (player != nullptr)
	{
		if (!isSetting)
		{


			
			if (BossType)
			{
				delay = 0.5f;
				Maxhp = 200;
				hp = Maxhp;
				transform->scale = { 3.f,3.f,3.f };
				movePattern = 0.f;
				mesh = (Mesh*)AddComponent<PKH::Cube>(L"Mesh");
				mesh->SetColor(D3DCOLOR_XRGB(255, MyColor, MyColor));
				
			}
			if (!BossType)
			{
				transform->scale = { 1.f,1.f,1.f };
				if (xType)
				{
					Mesh* mesh = (Mesh*)AddComponent<PKH::Cube>(L"Mesh");
					mesh->SetColor(D3DCOLOR_XRGB(xTypeColor[0], xTypeColor[1], xTypeColor[2]));
					delay = 1.f;
					moveSpeed = 10.f;
					Target = (Vector3{ 0,transform->position.y,transform->position.z }) - transform->position;
				}
				if (yType)
				{
					Mesh* mesh = (Mesh*)AddComponent<PKH::Cube>(L"Mesh");
					mesh->SetColor(D3DCOLOR_XRGB(yTypeColor[0], yTypeColor[1], yTypeColor[2]));
					moveSpeed = 5.f;
					Target = (Vector3{ transform->position.x,0.f,transform->position.z }) - transform->position;
				}
				if (!xType && !yType && !BossType)
				{
					Mesh* mesh = (Mesh*)AddComponent<PKH::Cube>(L"Mesh");
					mesh->SetColor(D3DCOLOR_XRGB(zTypeColor[0], zTypeColor[1], zTypeColor[2]));
					Target = (Vector3{ transform->position.x,transform->position.y,0.f }) - transform->position;
				}
			}
			isSetting = true;
		}
		if (!BossType)
		{
			if (!xType && !yType)
			{
				
				GameObject* player = ObjectManager::GetInstance()->FindObject<Player03>();
				if (player != nullptr)
				{
					Vector3 dir = player->transform->position - transform->position;
					Vector3::Normalize(&dir);

					if (transform->position.x < 0.f)
						MoveToTarget(Target);
					else
						MoveToTarget(Target);

					float rotX = atan2f(dir.z, dir.y);
					float rotY = atan2f(dir.x, dir.z);
					float rotZ = atan2f(dir.y, dir.x);

					//if(transform->rotation.x < rotX)
					transform->eulerAngles.x += rotX * TimeManager::DeltaTime();
					//if (transform->rotation.y < rotY)
					transform->eulerAngles.y += rotY * TimeManager::DeltaTime();
					//if (transform->rotation.z < rotZ)
					transform->eulerAngles.z += rotZ * TimeManager::DeltaTime();

					if (transform->position.z > 2)
					{
						tick += TimeManager::DeltaTime();
						if (tick > delay)
						{
							Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
							b->SetPosition(transform->position);
							CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							tick = 0;
						}
					}
				}

				if (transform->position.z < 1.f)
				{
					Die();
				}

			}

			if (xType)
			{
				
				GameObject* player = ObjectManager::GetInstance()->FindObject<Player03>();
				if (player != nullptr)
				{
					Vector3 dir = player->transform->position - transform->position;
					Vector3::Normalize(&dir);


					MoveToTarget(Target);



					float rotX = atan2f(dir.z, dir.y);
					float rotY = atan2f(dir.x, dir.z);
					float rotZ = atan2f(dir.y, dir.x);

					//if(transform->rotation.x < rotX)
					transform->eulerAngles.x += rotX * TimeManager::DeltaTime();
					//if (transform->rotation.y < rotY)
					transform->eulerAngles.y += rotY * TimeManager::DeltaTime();
					//if (transform->rotation.z < rotZ)
					transform->eulerAngles.z += rotZ * TimeManager::DeltaTime();

					if (transform->position.z > 2)
					{
						tick += TimeManager::DeltaTime();
						if (tick > delay)
						{
							Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
							b->SetPosition(transform->position);

							tick = 0;
						}
					}
				}

				if (transform->position.x > 9.f || transform->position.x < -10.f)
				{
					Die();
				}
			}

			if (yType)
			{
				

				GameObject* player = ObjectManager::GetInstance()->FindObject<Player03>();
				if (player != nullptr)
				{
					Vector3 dir = player->transform->position - transform->position;
					Vector3::Normalize(&dir);


					Vector3 dir2 = player->transform->position - transform->position;
					Vector3::Normalize(&dir2);

					if (transform->position.x < 0.f)
						MoveToTarget(Target);
					else
						MoveToTarget(Target);

					float rotX = atan2f(dir.z, dir.y);
					float rotY = atan2f(dir.x, dir.z);
					float rotZ = atan2f(dir.y, dir.x);

					//if(transform->rotation.x < rotX)
					transform->rotation.x += rotX * TimeManager::DeltaTime();
					//if (transform->rotation.y < rotY)
					transform->rotation.y += rotY * TimeManager::DeltaTime();
					//if (transform->rotation.z < rotZ)
					transform->rotation.z += rotZ * TimeManager::DeltaTime();

					if (transform->position.z > 2)
					{
						tick += TimeManager::DeltaTime();
						if (tick > delay)
						{
							Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
							b->SetPosition(transform->position);
							CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							tick = 0;
						}
					}
				}

				if (transform->position.y < -10.f || transform->position.y > 10.f)
				{
					Die();
				}
			}

			DieTime += TimeManager::DeltaTime();
			if (DieTime > 15)
			{
				Die();
			}

		}

		if (BossType)
		{
			transform->eulerAngles.z += BossRotateSpeed * TimeManager::DeltaTime();
			
			



			if (movePattern)
			{
				transform->position.x += TimeManager::DeltaTime();
			}

			if (transform->position.x > 5)
			{
				moveSpeed *= -1.f;
			}

			tick += TimeManager::DeltaTime();
			if (tick > delay)
			{
				if (bossPatten == 0)
				{
					Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
					b->SetPosition(transform->position);
					b->isBossBullet = true;
					b->BossBullet1 = 1;
					CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
				}
				tick = 0;

				

					if (BossSkill == 10)
					{


						if(bossPatten==0)
						{
							BossSkill = 0;
						}
					}
					if (bossPatten == 1)
					{
						if (BossSkill == 13)
						{
			
							for (int i = -10; i < 10; ++i)
							{
								Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
								b->BossBullet1 = i;
								b->isBossBullet = true;
								b->SetPosition(Vector3{ float(i), transform->position.y ,transform->position.z });
								CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							}

						}

						if (BossSkill == 16)
						{
	
							for (int i = -10; i < 10; ++i)
							{
								Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
								b->BossBullet1 = i;
								b->isBossBullet = true;
								b->SetPosition(Vector3{ transform->position.x, float(i) ,transform->position.z });
								CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							}

						}

						if (BossSkill == 20)
						{
	
							for (int i = -5; i < 5; ++i)
							{
								for (int j = -5; j < 5; ++j)
								{
									Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
									b->BossBullet1 = i;
									b->isBossBullet = true;
									b->SetPosition(Vector3{ float(i), float(j) ,transform->position.z });
									CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
								}
							}
							BossSkill = 10;
						}
					}
					if (bossPatten == 2)
					{
						if (BossSkill == 21)
						{

							for (int i = -10; i < 10; ++i)
							{
								Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
								b->BossBullet1 = i;
								b->isBossBullet = true;
								b->SetPosition(Vector3{ float(i), transform->position.y-4 ,transform->position.z });
								CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							}
						}

						if (BossSkill == 22)
						{

							for (int i = -10; i < 10; ++i)
							{
								Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
								b->BossBullet1 = i;
								b->isBossBullet = true;
								b->SetPosition(Vector3{ float(i), transform->position.y-2 ,transform->position.z });
								CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							}
						}

						if (BossSkill == 23)
						{
		
							for (int i = -10; i < 10; ++i)
							{
								Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
								b->BossBullet1 = i;
								b->isBossBullet = true;
								b->SetPosition(Vector3{ float(i), transform->position.y ,transform->position.z });
								CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							}
						}

						if (BossSkill == 24)
						{
		
							for (int i = -10; i < 10; ++i)
							{
								Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
								b->BossBullet1 = i;
								b->isBossBullet = true;
								b->SetPosition(Vector3{ float(i), transform->position.y+2 ,transform->position.z });
								CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							}
						}

						if (BossSkill == 25)
						{
					
							for (int i = -10; i < 10; ++i)
							{
								Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
								b->BossBullet1 = i;
								b->isBossBullet = true;
								b->SetPosition(Vector3{ float(i), transform->position.y +4,transform->position.z });
								CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							}
						}
						if (BossSkill == 26)
						{
				
							for (int i = -10; i < 10; ++i)
							{
								Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
								b->BossBullet1 = i;
								b->isBossBullet = true;
								b->SetPosition(Vector3{ transform->position.x+4, float(i) ,transform->position.z });
								CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							}

						}
						if (BossSkill == 27)
						{
			
							for (int i = -10; i < 10; ++i)
							{
								Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
								b->BossBullet1 = i;
								b->isBossBullet = true;
								b->SetPosition(Vector3{ transform->position.x+2, float(i) ,transform->position.z });
								CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							}

						}
						if (BossSkill == 28)
						{
				
							for (int i = -10; i < 10; ++i)
							{
								Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
								b->BossBullet1 = i;
								b->isBossBullet = true;
								b->SetPosition(Vector3{ transform->position.x, float(i) ,transform->position.z });
								CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							}

						}
						if (BossSkill == 29)
						{
						
							for (int i = -10; i < 10; ++i)
							{
								Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
								b->BossBullet1 = i;
								b->isBossBullet = true;
								b->SetPosition(Vector3{ transform->position.x-2, float(i) ,transform->position.z });
								CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							}

						}
						if (BossSkill == 30)
						{
				
							for (int i = -10; i < 10; ++i)
							{
								Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
								b->BossBullet1 = i;
								b->isBossBullet = true;
								b->SetPosition(Vector3{ transform->position.x-4, float(i) ,transform->position.z });
								CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
							}

						}

						if (BossSkill == 31)
						{
							
							for (int i = -5; i < 5; ++i)
							{
								for (int j = -5; j < 5; ++j)
								{
									Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
									b->BossBullet1 = i;
									b->isBossBullet = true;
									b->SetPosition(Vector3{ float(i), float(j) ,transform->position.z });
									CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
								}
							}
						}
						if (BossSkill == 31)
						{
						
							for (int i = -5; i < 5; ++i)
							{
								for (int j = -5; j < 5; ++j)
								{
									Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
									b->BossBullet1 = i;
									b->isBossBullet = true;
									b->SetPosition(Vector3{ float(i), float(j) ,transform->position.z });
									CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
								}
							}
						}
						if (BossSkill == 32)
						{
						
							for (int i = -5; i < 5; ++i)
							{
								for (int j = -5; j < 5; ++j)
								{
									Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
									b->BossBullet1 = i;
									b->isBossBullet = true;
									b->SetPosition(Vector3{ float(i), float(j) ,transform->position.z });
									CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
								}
							}
						}
						if (BossSkill == 33)
						{
						
							for (int i = -5; i < 5; ++i)
							{
								for (int j = -5; j < 5; ++j)
								{
									Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
									b->BossBullet1 = i;
									b->isBossBullet = true;
									b->SetPosition(Vector3{ float(i), float(j) ,transform->position.z });
									CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
								}
							}
						}
						if (BossSkill == 34)
						{
						
							for (int i = -5; i < 5; ++i)
							{
								for (int j = -5; j < 5; ++j)
								{
									Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
									b->BossBullet1 = i;
									b->isBossBullet = true;
									b->SetPosition(Vector3{ float(i), float(j) ,transform->position.z });
									CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
								}
							}
						}

						if (BossSkill == 35)
						{
							//Monster03* m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
							//m->SetPosition(Vector3{ transform->position - Vector3{2.f,2.f,0.f} });

							for (int i = -5; i < 5; ++i)
							{
								for (int j = -5; j < 5; ++j)
								{
									Bullet03* b = (Bullet03*)ObjectManager::GetInstance()->CreateObject<Bullet03>();
									b->BossBullet1 = i;
									b->isBossBullet = true;
									b->SetPosition(Vector3{ float(i), float(j) ,transform->position.z });
									CollisionManager03::GetInstance()->RegisterObject(CollisionManager03::MONSTER_BULLET, b);
								}
							}
							BossSkill = 20;
						}
					}

				BossSkill++;
				
			}
			if (hp <= Maxhp / 1.5 && bossPatten==0  )
			{
				bossPatten = 1;
			}

			if (hp <= Maxhp / 3 && bossPatten == 1)
			{
				bossPatten = 2;
			}
		}
		
		

		if (hp <= 0)
		{
			if (BossType)
			{
				dynamic_cast<Player03*>(player)->SceneChange += 1;
			}
			Die();
		}
	}
	GameObject::Update();
}

void PKH::Monster03::PostRender()
{
	Vector3 hpPos = { 0.f,2.8f,0.f };


	Vector3 winPos = Camera::WorldToScreenPoint(hpPos);

	TCHAR buffer[5] = L"";
	
	wsprintf(buffer, L"%d", hp);

	if (BossType == true)
	{
		D2DRenderManager::DrawFont(buffer, winPos.x, winPos.y, D3DCOLOR_XRGB(255, MyColor, MyColor));
	}


}

