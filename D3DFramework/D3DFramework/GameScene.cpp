#include "stdafx.h"
#include "GameScene.h"

#include "Label.h"

#include "SkyBox.h"
#include "Environment.h"
#include "TestMan.h"
#include "PlayerController.h"
#include "NetPlayerController.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "NavMeshMap.h"
#include "TestGaren.h"
#include "Wall.h"
#include "Turret.h"
#include "Bush.h"

#include "Garen.h"
#include "Blitzcrank.h"
#include "Darius.h"
#include "Diana.h"
#include "Leesin.h"
#include "Missfortune.h"
#include "Leona.h"
#include "Ahri.h"
#include "Jax.h"
#include "Jinx.h"

#include "PlayerInfoPanel.h"
#include "FloatingBar.h"

#include "OrderMinionCaster.h"
#include "OrderMinionMelee.h"
#include "OrderMinionSiege.h"
#include "OrderMinionSuper.h"
#include "ChaosMinionCaster.h"
#include "ChaosMinionSiege.h"
#include "ChaosMinionSuper.h"
#include "ChaosMinionMelee.h"

#include "BlueMonster.h"
#include "RedMonster.h"
#include "Murkwolf.h"
#include "MurkwolfMini.h"
#include "Krug.h"
#include "KrugMini.h"
#include "Gromp.h"
#include "Razorbeak.h"
#include "RazorbeakMini.h"
#include "Scuttleracer.h"

#include "MinionAI.h"

int unitID = (int)UnitID::END;

GameScene::GameScene()
{
	net = Network::GetInstance();

	spawnPos[0] = { 41.74, 68.57, 46.30 };
	spawnPos[1] = { 39.85, 68.57, 46.63 };
	spawnPos[2] = { 39.60, 68.59, 48.72 };
	spawnPos[3] = { 41.30, 68.58, 49.42 };
	spawnPos[4] = { 42.58, 68.59, 47.91 };
	spawnPos[5] = { -47.68, 68.48, -43.10 };
	spawnPos[6] = { -49.23, 68.48, -41.54 };
	spawnPos[7] = { -48.35, 68.49, -39.51 };
	spawnPos[8] = { -46.34, 68.48, -39.96 };
	spawnPos[9] = { -46.01, 68.48, -41.93 };

	playerInfo = PlayerInfoPanel::GetInstance();
	ObjectManager::GetInstance()->AddObject(playerInfo, Layer::HUD);

}

void GameScene::OnLoaded()
{
	Cursor::Show();
	//ObjectManager::GetInstance()->CreateObject<Light>();

	//SkyBox::Show();
	//SkyBox::SetTexture(TextureKey::SKY_U);
	Camera::GetInstance()->SetPosition(Vector3(0.f, 1.f, -1.f));
	Camera::GetInstance()->transform->look = Vector3(0, 0, 1);

	latencyLabel = (Label*)ObjectManager::GetInstance()->CreateObject<Label>(Layer::UI);
	latencyLabel->foreColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	CreateEnvironment();
	CreateChampion();
	CreateBuilding();
	CreateMonster();
}

void GameScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void GameScene::Update()
{
	float dt = TimeManager::DeltaTime();

	NetProc();

	sendTick += dt;
	if (sendTick > sendDelay)
	{
		sendTick = 0.f;
		ReqTime();
	}

	if (InputManager::GetKey(VK_SHIFT))
	{
		if (InputManager::GetKeyDown('M'))
		{
			ReqCreateMinionCaster();
		}
	}
}

void GameScene::PacketProc(CPacket* pPacket)
{
	WORD type;
	*pPacket >> type;
	switch (type)
	{
	case GAME_RES_TIME:
		ResTime(pPacket);
		break;
	case GAME_RES_MOVE:
		ResMove(pPacket);
		break;
	case GAME_RES_ATTACK:
		ResAttack(pPacket);
		break;
	case GAME_RES_DAMAGE:
		ResDamage(pPacket);
		break;
	case GAME_RES_CREATE_MINION_CASTER:
		ResCreateMinionCaster(pPacket);
		break;
	default:
		Debug::Print("[Warning] 정의되지 않은 패킷 타입 감지\n");
		break;
	}
}

void GameScene::NetProc()
{
	Network* net = Network::GetInstance();

	while (net->packQ.size() > 0)
	{
		CPacket* pack = net->packQ.front();
		net->packQ.pop();

		PacketProc(pack);
		delete pack;
	}
}


void GameScene::ReqTime()
{
	oldTime = timeGetTime();

	CPacket* pack = new CPacket();
	pack->Clear();
	*pack << (WORD)GAME_REQ_TIME << oldTime;

	Network::SendPacket(pack);
	delete pack;
}

void GameScene::ResTime(CPacket* pack)
{
	DWORD time;
	*pack >> time;
	DWORD curTime = timeGetTime();
	DWORD elapsed = curTime - time;
	WCHAR wstr[16] = {};
	swprintf_s(wstr, L"%dms", elapsed);
	latencyLabel->text = wstr;
}

void GameScene::ResMove(CPacket* pack)
{
	INT gameID, pathCount;
	Vector3 dest;
	list<Vector3> path;
	
	*pack >> gameID >> pathCount;

	for (int i = 0; i < pathCount; i++)
	{
		*pack >> dest.x >> dest.y >> dest.z;
		path.push_back(dest);
	}

	auto find = unitMap.find(gameID);
	if (find == unitMap.end())
	{
		return;
	}
	
	//unitMap[gameID]->Move(dest);
	unitMap[gameID]->SetAttackTarget(nullptr);
	unitMap[gameID]->agent->SetStoppingDistance(0.03f);
	unitMap[gameID]->agent->SetPath(path);
}

void GameScene::ResAttack(CPacket* pack)
{
	
	INT unitID, targetID;
	*pack >> unitID >> targetID;
	Debug::PrintLine("공격패킷 받음 / 공격자 %d / 타겟 %d", unitID, targetID);

	auto find = unitMap.find(unitID);
	if (find == unitMap.end())
	{
		Debug::PrintLine("공격자가 없음");
		return;
	}
	auto find2 = unitMap.find(targetID);
	if (find2 == unitMap.end())
	{
		Debug::PrintLine("타겟이 없음");
		return;
	}
	Debug::PrintLine("공격 실행");
	unitMap[unitID]->Attack(find2->second);

}

void GameScene::ResDamage(CPacket* pack)
{
	INT unitID, targetID;
	FLOAT damage;
	*pack >> unitID >> targetID >> damage;
	Debug::PrintLine("데미지 패킷 받음 / 공격자 %d / 타겟 %d", unitID, targetID);

	auto find = unitMap.find(unitID);
	if (find == unitMap.end())
	{
		Debug::PrintLine("공격자가 없음");
		return;
	}
	auto find2 = unitMap.find(targetID);
	if (find2 == unitMap.end())
	{
		Debug::PrintLine("타겟이 없음");
		return;
	}
	unitMap[targetID]->SetLastAttacker(unitMap[unitID]);
	unitMap[targetID]->TakeDamage(damage);

}

void GameScene::ReqCreateMinionCaster()
{
	CPacket* pack = new CPacket();
	pack->Clear();
	*pack << (WORD)GAME_REQ_CREATE_MINION_CASTER;

	Network::SendPacket(pack);
	delete pack;
}

void GameScene::ResCreateMinionCaster(CPacket* pack)
{
	CreateMinionCaster();
}

//============================================================================================
void GameScene::CreateEnvironment()
{
	GameObject* obj = nullptr;
	// 오브젝트
	obj = ObjectManager::GetInstance()->CreateObject<Environment>();
	obj->transform->position = { 0,0,0 };

	// 바닥
	obj = ObjectManager::GetInstance()->CreateObject<NavMeshMap>(Layer::Ground);

	// 벽
	obj = ObjectManager::GetInstance()->CreateObject<Wall>(Layer::Wall);

	// 부쉬
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.98f,67.71f,29.14f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.90,67.71,29.87 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.84,67.71,29.55 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.50,67.71,28.95 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.90,67.71,28.73 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.70,67.71,28.37 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.39,67.71,28.22 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.01,67.71,28.06 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.71,67.71,27.92 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.41,67.71,27.83 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.99,67.71,28.52 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.54,67.71,28.44 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.68,67.71,28.77 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.15,67.71,28.61 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.00,67.71,28.84 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 6.83,67.71,28.54 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 6.99,67.71,28.18 };
}

void GameScene::CreateChampion()
{
	for (auto iter : net->users)
	{
		Layer layer = Layer::Unit;
		int userNum = iter.second.number;

		ChampionType champType = (ChampionType)iter.second.champ;
		Champion* champion = nullptr;
		switch (champType)
		{
		case ChampionType::Garen:
			champion = (Champion*)ObjectManager::GetInstance()->CreateObject<Garen>(layer);
			break;
		case ChampionType::Darius:
			champion = (Champion*)ObjectManager::GetInstance()->CreateObject<Darius>(layer);
			break;
		case ChampionType::Diana:
			champion = (Champion*)ObjectManager::GetInstance()->CreateObject<Diana>(layer);
			break;
		case ChampionType::Leona:
			champion = (Champion*)ObjectManager::GetInstance()->CreateObject<Leona>(layer);
			break;
		case ChampionType::Leesin:
			champion = (Champion*)ObjectManager::GetInstance()->CreateObject<Leesin>(layer);
			break;
		case ChampionType::Missfortune:
			champion = (Champion*)ObjectManager::GetInstance()->CreateObject<Missfortune>(layer);
			break;
		case ChampionType::Blitzcrank:
			champion = (Champion*)ObjectManager::GetInstance()->CreateObject<Blitzcrank>(layer);
			break;
		case ChampionType::Ahri:
			champion = (Champion*)ObjectManager::GetInstance()->CreateObject<Ahri>(layer);
			break;
		case ChampionType::Jax:
			champion = (Champion*)ObjectManager::GetInstance()->CreateObject<Jax>(layer);
			break;
		case ChampionType::Jinx:
			champion = (Champion*)ObjectManager::GetInstance()->CreateObject<Jinx>(layer);
			break;
		default:
			break;
		}

		if (champion != nullptr)
		{
			unitMap[userNum] = champion;
			unitMap[userNum]->SetID(userNum);

			if (userNum > 4)
			{
				unitMap[userNum]->SetTeam(Team::RED);
			}
			else
			{
				unitMap[userNum]->SetTeam(Team::BLUE);
				
			}

			if (userNum == net->number)
			{
				unitMap[userNum]->AddComponent<NetPlayerController>(L"NetPlayerController");
				Camera::main->SetTarget(unitMap[userNum]);
				playerInfo->SetTarget(champion);
			}

			unitMap[userNum]->transform->position = spawnPos[userNum];
			champion->bar->SetNickname(iter.second.nickname);
		}
	}
}

void GameScene::CreateBuilding()
{
	Unit* unit = nullptr;
	int unitID = (int)UnitID::TurretBlueBot1;
	
	
	// 블루팀 타워
	
	// bottom1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -23.15f, 67.71f, 44.17f };
	unit->transform->eulerAngles.y = D3DXToRadian(135.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// bottom2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -0.30f, 67.71f, 41.20f };
	unit->transform->eulerAngles.y = D3DXToRadian(135.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// bottom3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 16.41f, 67.87f, 42.5f };
	unit->transform->eulerAngles.y = D3DXToRadian(135.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// mid1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 6.50f, 67.71f, 10.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// mid2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 11.61f, 67.71f, 20.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// mid3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 20.51f, 67.87f, 27.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// top1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 37.42f, 67.71f, -16.f };
	unit->transform->eulerAngles.y = D3DXToRadian(45.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// top2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 34.12f, 67.71f, 8.f };
	unit->transform->eulerAngles.y = D3DXToRadian(45.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// top3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 36.36f, 67.87f, 23.f };
	unit->transform->eulerAngles.y = D3DXToRadian(45.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	
	// twin Left
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 32.35f, 68.f, 36.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// twin Right
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 29.46f, 68.f, 39.3f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;


	// 퍼플팀

	// bottom1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -44.71f,67.71f,21.98f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// bottom2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -41.30f,67.71f,-1.89f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// bottom3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -43.20f,68.f,-16.83f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// mid1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -13.30f,67.71f,-3.61f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// mid2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -18.52f,67.71f,-13.85f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// mid3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -27.21f,68.f,-20.97f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;


	// top1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 16.28f,67.71f,-37.99f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// top2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -6.93f,67.71f,-34.96f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// top3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -23.09f,68.f,-36.63f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// twin left
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -39.52f,68.00f,-29.97f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// twin right
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -36.64f,68.00f,-32.90f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
}

void GameScene::CreateMonster()
{
	Unit* unit = nullptr;
	int unitID = (int)UnitID::Red1;
	// 몬스터

	// 레드
	unit = (Unit*)(Unit*)ObjectManager::GetInstance()->CreateObject<RedMonster>(Layer::Unit);
	unit->transform->position = { -6.10,67.71,24.87 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<RedMonster>(Layer::Unit);
	unit->transform->position = { -1.88,67.71,-17.87 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// 블루
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<BlueMonster>(Layer::Unit);
	unit->transform->position = { 19.79,67.72,0.64 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<BlueMonster>(Layer::Unit);
	unit->transform->position = { -26.43,67.71,6.83 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// 늑대 위
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Murkwolf>(Layer::Unit);
	unit->transform->position = { 19.74,67.71,9.78 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::Unit);
	unit->transform->position = { 19.17,67.71,10.84 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::Unit);
	unit->transform->position = { 21.08,67.71,9.00 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// 늑대 아래
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Murkwolf>(Layer::Unit);
	unit->transform->position = { -26.72,67.72,-2.72 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::Unit);
	unit->transform->position = { -26.23,67.71,-3.57 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::Unit);
	unit->transform->position = { -27.73,67.71,-2.44 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// 두꺼비
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Gromp>(Layer::Unit);
	unit->transform->position = { 29.28,67.73,-2.82 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Gromp>(Layer::Unit);
	unit->transform->position = { -36.59,67.71,10.14 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// 쨱쨱이 위
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Razorbeak>(Layer::Unit);
	unit->transform->position = { -0.75,67.71,16.17 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -1.32,67.71,15.52 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -1.69,67.71,16.20 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -1.71,67.71,17.11 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -0.98,67.71,17.65 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { 0.08,67.71,17.21 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// 짹짹이 아래
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Razorbeak>(Layer::Unit);
	unit->transform->position = { -6.43,67.71,-10.09 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -5.53,67.71,-9.14 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -5.56,67.71,-10.09 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -5.91,67.71,-11.04 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -6.81,67.71,-10.93 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -7.31,67.71,-10.48 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;


	// 작골
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Krug>(Layer::Unit);
	unit->transform->position = { -10.05,67.71,33.49 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Krug>(Layer::Unit);
	unit->transform->position = { 3.13,67.71,-26.61 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// 바위게
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Scuttleracer>(Layer::Unit);
	unit->transform->position = { 15.68,66.91,-11.16 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Scuttleracer>(Layer::Unit);
	unit->transform->position = { -24.36,66.91,17.82 };
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
}

void GameScene::CreateMinionCaster()
{
	Minion* minion = nullptr;

	// 블루
	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionCaster>(Layer::Unit);
	minion->transform->position = { 29.47f,68.04f,41.74f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -30.88f,67.71f,40.80f };
	minion->ai->wayPoint.push_back(Vector3(-42.32f, 67.71f, 28.58f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionCaster>(Layer::Unit);
	minion->transform->position = { 30.64f,68.04f,37.51f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionCaster>(Layer::Unit);
	minion->transform->position = { 35.00f,68.04f,35.55f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { 34.58f,67.71f,-23.79f };
	minion->ai->wayPoint.push_back(Vector3(23.98f, 67.71f, -34.88f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	// 레드
	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionCaster>(Layer::Unit);
	minion->transform->position = { -43.05f,68.01f,-29.62f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -42.32f,67.71f,28.58f };
	minion->ai->wayPoint.push_back(Vector3(-30.88f, 67.71f, 40.80f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionCaster>(Layer::Unit);
	minion->transform->position = { -36.94f,68.01f,-30.35f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionCaster>(Layer::Unit);
	minion->transform->position = { -36.68f,68.01f,-36.45f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { 23.98f,67.71f,-34.88f };
	minion->ai->wayPoint.push_back(Vector3(34.58f, 67.71f, -23.79f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	

	

	
}

void GameScene::CreateMinionMelee()
{
	Minion* minion = nullptr;
	// 블루========================================================
	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionMelee>(Layer::Unit);
	minion->transform->position = { 29.47f,68.04f,41.74f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -30.88f,67.71f,40.80f };
	minion->ai->wayPoint.push_back(Vector3(-42.32f, 67.71f, 28.58f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionMelee>(Layer::Unit);
	minion->transform->position = { 30.64f,68.04f,37.51f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionMelee>(Layer::Unit);
	minion->transform->position = { 35.00f,68.04f,35.55f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { 34.58f,67.71f,-23.79f };
	minion->ai->wayPoint.push_back(Vector3(23.98f, 67.71f, -34.88f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	// 레드
	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionMelee>(Layer::Unit);
	minion->transform->position = { -43.05f,68.01f,-29.62f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -42.32f,67.71f,28.58f };
	minion->ai->wayPoint.push_back(Vector3(-30.88f, 67.71f, 40.80f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionMelee>(Layer::Unit);
	minion->transform->position = { -36.94f,68.01f,-30.35f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionMelee>(Layer::Unit);
	minion->transform->position = { -36.68f,68.01f,-36.45f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { 23.98f,67.71f,-34.88f };
	minion->ai->wayPoint.push_back(Vector3(34.58f, 67.71f, -23.79f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;
}

void GameScene::CreateMinionSiege()
{
	Minion* minion = nullptr;
	// 블루
	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionSiege>(Layer::Unit);
	minion->transform->position = { 29.47f,68.04f,41.74f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -30.88f,67.71f,40.80f };
	minion->ai->wayPoint.push_back(Vector3(-42.32f, 67.71f, 28.58f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionSiege>(Layer::Unit);
	minion->transform->position = { 30.64f,68.04f,37.51f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionSiege>(Layer::Unit);
	minion->transform->position = { 35.00f,68.04f,35.55f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { 34.58f,67.71f,-23.79f };
	minion->ai->wayPoint.push_back(Vector3(23.98f, 67.71f, -34.88f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	// 레드
	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionSiege>(Layer::Unit);
	minion->transform->position = { -43.05f,68.01f,-29.62f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -42.32f,67.71f,28.58f };
	minion->ai->wayPoint.push_back(Vector3(-30.88f, 67.71f, 40.80f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionSiege>(Layer::Unit);
	minion->transform->position = { -36.94f,68.01f,-30.35f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionSiege>(Layer::Unit);
	minion->transform->position = { -36.68f,68.01f,-36.45f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { 23.98f,67.71f,-34.88f };
	minion->ai->wayPoint.push_back(Vector3(34.58f, 67.71f, -23.79f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;
}

void GameScene::CreateMinionSuper()
{
	Minion* minion = nullptr;
	// 블루
	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionSuper>(Layer::Unit);
	minion->transform->position = { 29.47f,68.04f,41.74f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -30.88f,67.71f,40.80f };
	minion->ai->wayPoint.push_back(Vector3(-42.32f, 67.71f, 28.58f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionSuper>(Layer::Unit);
	minion->transform->position = { 30.64f,68.04f,37.51f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionSuper>(Layer::Unit);
	minion->transform->position = { 35.00f,68.04f,35.55f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { 34.58f,67.71f,-23.79f };
	minion->ai->wayPoint.push_back(Vector3(23.98f, 67.71f, -34.88f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	// 레드
	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionSuper>(Layer::Unit);
	minion->transform->position = { -43.05f,68.01f,-29.62f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -42.32f,67.71f,28.58f };
	minion->ai->wayPoint.push_back(Vector3(-30.88f, 67.71f, 40.80f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionSuper>(Layer::Unit);
	minion->transform->position = { -36.94f,68.01f,-30.35f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionSuper>(Layer::Unit);
	minion->transform->position = { -36.68f,68.01f,-36.45f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { 23.98f,67.71f,-34.88f };
	minion->ai->wayPoint.push_back(Vector3(34.58f, 67.71f, -23.79f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;
}
