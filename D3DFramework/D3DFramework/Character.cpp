#include "stdafx.h"
#include "Character.h"
#include "Terrain.h"
#include "Environment.h"
#include "Rectangle.h"
#include "TargetInfoPanel.h"
#include "Skill.h"
#include "DamageSkin.h"
#include "Effect.h"
#include "PlayerInfoPanel.h"
#include "Coin.h"
#include "QuestManager.h"
#include "Item.h"
#include "AllItems.h"

Character::Character() :
	canMove(true)
{
	team = Team::MONSTERTEAM;
	Mesh* mesh = (Mesh*)AddComponent<PKH::Rectangle>(L"Mesh");
	mesh->SetBlendMode(BlendMode::ALPHA_TEST);
	anim = (Animation2D*)AddComponent<Animation2D>(L"Animation2D");
}

Character::~Character()
{
	if (TargetInfoPanel::GetTarget() == this)
	{
		TargetInfoPanel::SetTarget(nullptr);
		TargetInfoPanel::Hide();
	}
	Release();
	CollisionManager::GetInstance()->DisregisterObject(this);
}

void Character::Update()
{
	GameObject::Update();
	OnTerrain();
	Billboard();
	UpdateAnimation();
	CalcMoveTime();
	CalcExp();

	oldState = state;
	healEffectStack += TimeManager::DeltaTime();
}

void Character::Render()
{
	GameObject::Render();
	RenderInfomation();
}

void Character::RenderInfomation()
{
	if (infoVisible == false)return;
	if (transform->zOrder < 0.f)
	{
		return;
	}
	// 카메라와 거리
	float camDist = Vector3::Distance(Camera::GetInstance()->GetPosition(), this->transform->position);
	if (camDist < 15.f)
	{
		// 이름길이
		float len = float(name.length());
		float strW = 20;
		Vector3 namePos = Camera::WorldToScreenPoint(transform->position);
		namePos.x -= (len / 2.f) * strW;
		namePos.y -= transform->scale.y + 70 - camDist;
		RenderManager::DrawFont(name, namePos.x, namePos.y, D3DCOLOR_XRGB(255, 255, 255));

		// HP바
		Texture* hpBarTex = RenderManager::GetTexture(TextureKey::UI_HP_BAR_05);
		float hpW = (float)hpBarTex->imageInfo.Width;
		Vector3 hpPos = Camera::WorldToScreenPoint(transform->position);
		hpPos.x -= (float(hpBarTex->imageInfo.Width) / hpBarTex->colCount) * 0.5f;
		hpPos.y -= transform->scale.y + 50 - camDist;
		RenderManager::DrawUI(TextureKey::UI_HP_BAR_05, hpPos, Vector3(1, 1, 1), 0, float(stat.hp)/ stat.maxHp);
		
	}


	
}

void Character::Initialize()
{
}

void Character::Release()
{
	for (auto skill : skillSet)
	{
		if (nullptr != skill)
		{
			
			delete skill;
			skill = nullptr;
		}
	}

	skillSet.clear();
	skillSet.shrink_to_fit();
}

void Character::OnCollision(GameObject* target)
{
	
	if (isInvincible == false) // 무적이 아닐떄
	{
		if (this->team == target->team) return;

		Character* playerCharacter = Player::GetInstance()->GetCharacter();



		float error = target->stat.attack * 0.4f;
		float errorHalf = error * 0.5f;
		error = Random::Range(0.f, error);
		error -= errorHalf;
		float damageSum = target->stat.attack + error;
		stat.hp -= damageSum;

		if (stat.hp > stat.maxHp)
		{
			stat.hp = stat.maxHp;
		}

		if (damageSum < 0)
		{
			if (damageSum < -1) // 힐
			{
				DamageSkin* skin = (DamageSkin*)ObjectManager::GetInstance()->CreateObject<DamageSkin>();
				skin->transform->position = this->transform->position;
				skin->SetDamage(int(-damageSum));
				skin->SetColor(D3DCOLOR_XRGB(0, 200, 0));
			}

			if (healEffectStack > 1.f)
			{
				Vector3 pos = transform->position;

				pos.y += 0.3f;

				Effect* fx = Effect::Create(pos, transform->scale, TextureKey::BULLET_HEART1_01, TextureKey::BULLET_HEART1_05, 0.2f);
				/*fx->transform->position.y += 1.f;*/
				ObjectManager::AddObject(fx);
				healEffectStack = 0.f;
			}
		}

		// 데미지 스킨
		else if (damageSum >= 1) // 맞았을떄
		{

			//몬스터
			DamageSkin* skin = (DamageSkin*)ObjectManager::GetInstance()->CreateObject<DamageSkin>();
			skin->transform->position = this->transform->position;
			skin->SetDamage(int(damageSum));
			//플레이어
			if (this == playerCharacter)
			{
				skin->SetColor(D3DCOLOR_XRGB(200, 0, 200));
				PlayerInfoPanel::ActiveRedFilter();
				SoundManager::PlayOverlapSound(L"Hit2.wav", SoundChannel::PLAYER);
			}
			else
			{
				//몬스터일떄
				TargetInfoPanel::SetTarget(this);
				TargetInfoPanel::Show();
			}


		}

		if (damageSum > 0.f && this == playerCharacter)
		{
			PlayerInfoPanel::ActiveRedFilter();
			SoundManager::PlayOverlapSound(L"Hit2.wav", SoundChannel::PLAYER);
		}


		// 사망처리
		if (!IsDead() && stat.hp <= 0)
		{
			// 몬스터의 경우
			if (this->team == Team::MONSTERTEAM) {
				// 다음 변신할 몬스터 등록
				SoundManager::PlayOverlapSound(L"Death.wav", SoundChannel::EFFECT);

				Player::GetInstance()->ChangeNextPokemon(type, number);
				float exp = stat.totalExp * 0.25f;
				Player::GetInstance()->GetCharacter()->IncreaseEXP(exp);
				// 코인 생성
				Coin* coin = Coin::Create(this->transform->position, this->stat.money);
				ObjectManager::AddObject(coin);
				CollisionManager::RegisterObject(COLTYPE::COIN, coin);
				// 아이템 드랍
				Item* item = Item::CreateRandom();
				if (item != nullptr)
				{
					item->transform->position = this->transform->position;
					ObjectManager::AddObject(item);
				}

				// 퀘스트 몬스터 킬수
				if (this->monsterAI != nullptr) {
					QuestManager::GetInstance()->AddMonsterKill(monsterAI->type);
				}

				TargetInfoPanel::SetTarget(nullptr);
				TargetInfoPanel::Hide();

			}
			
			//공통 사망
			stat.hp = 0;
			if (dontDestroy == true) return;

			Die();
			if (nullptr == spawner)
				return;
			spawner->monsterCount--;
			return;

		}

		// 상대가 플레이어면서 몬스터일때 해당
		if (damageSum < 0)return;

		if (playerCharacter == this) return;
		
	}
	else // 무적일 떄
	{
		return;
	}
		
}

void Character::Die()
{
	if (Team::MONSTERTEAM == team)
	{
		Player* player = Player::GetInstance();
		if (nullptr != player)
		{
			Character* character = player->GetCharacter();
			if (nullptr != character)
			{
				
			}
		}
	}

	if (dontDestroy) return;
	isDead = true;
}

void Character::CalcMoveTime()
{
	if (!canMove)
	{
		moveStopTime -= TimeManager::DeltaTime();

		if (0.f > moveStopTime)
		{
			canMove = true;
			moveStopTime = 0.f;
		}
	}
}

void Character::CalcExp()
{
	while (stat.exp >= stat.totalExp)
	{
		stat.exp -= stat.totalExp;
		LevelUp();
	}
}

void Character::OnTerrain()
{
	GameObject* obj = ObjectManager::GetInstance()->FindObject<Environment>();
	if (obj == nullptr)
	{
		transform->position.y = offsetY;
		return;
	}
	Terrain* mesh = (Terrain*)obj->GetComponent(L"Mesh");
	if(mesh == nullptr)
	{
		transform->position.y = offsetY;
		return;
	}
	
	float y;
	bool onTerrain = mesh->GetYFromPoint(&y, transform->position.x, transform->position.z);
	if (onTerrain)
		transform->position.y = y + offsetY;
	else
	{
		transform->position.y = offsetY;
	}
}

float Character::GetAngleFromCamera()
{
	Vector3 camPos = Camera::GetPosition();

	Vector3 toRealCam = camPos - transform->position;
	Vector3 toCam = toRealCam;
	toCam.y = 0;
	Vector3 myDir = direction;

	D3DXVec3Normalize(&toCam, &toCam);
	D3DXVec3Normalize(&toRealCam, &toRealCam);
	D3DXVec3Normalize(&myDir, &myDir);

	float radian = acos(D3DXVec3Dot(&toCam, &myDir));
	float degree = D3DXToDegree(radian);

	Vector3 cross;
	D3DXVec3Cross(&cross, &toRealCam, &myDir);

	Vector3 empty = { 0, 0, 0 };

	if (cross == empty)
		int i = 0;

	Vector3 up = transform->up;

	float upDot = D3DXVec3Dot(&cross, &up);

	if (0 > upDot)
	{
		degree = 360 - degree;
	}

	return degree;
}

void Character::UpdateAnimation()
{
	float angle = GetAngleFromCamera();

	angle += 22.5f;

	int index = int(angle / 45.f);

	index %= 8;

	if (oldState != state)
	{
		anim->SetSprite(startArray[(int)state][index], endArray[(int)state][index]);
	}
	else
	{
		int curIndex = ((int)anim->GetEndSprite() - (int)anim->GetCurrentSprite());

		anim->SetSprite(startArray[(int)state][index], endArray[(int)state][index]);
		curIndex = (int)endArray[(int)state][index] - curIndex;
		anim->SetCurrentSprite((TextureKey)curIndex);
	}
}

void Character::SetDir(const Vector3 & dir)
{
	if (canMove)
		D3DXVec3Normalize(&direction, &dir);
}

void Character::SetLV(const int & lv)
{
	stat.level = lv;

	SetStatByLevel();
}

void Character::LevelUp()
{
	++stat.level;

	SoundManager::PlayOverlapSound(L"LevelUp.wav", SoundChannel::PLAYER_EFFECT, 0.8f);

	Vector3 pos = transform->position;

	pos.y += 0.5f;

	Effect * fx = Effect::Create(pos, { 0.2f, 0.2f, 0.2f }, TextureKey::BELL_EFFECT_01, TextureKey::BELL_EFFECT_20, 0.05f);
	ObjectManager::AddObject(fx);

	SetStatByLevel();
}

void Character::SetStatByLevel()
{
	int lv = stat.level;
	stat.attack = (increaseAttack * (lv - 1)) + defaultAttack;
	stat.maxHp = (increaseMaxHp * (lv - 1)) + defaultMaxHp;
	stat.hp = stat.maxHp;
	stat.totalExp = (increaseTotalExp * (lv - 1)) + defaultTotalExp;
}

void Character::MoveForward()
{
	if(canMove) Move(direction);
}

void Character::ChangeState(State nextState)
{
	if (team == Team::PLAYERTEAM) {
		if (nextState != state)
		{
			state = nextState;
		}
	}
}

float Character::GetSkillCoolTime(int num)
{
	if (skillSet.size() >= (UINT)num) return -5.f;

	return skillSet[num]->GetCoolTime();
}

bool Character::Attack(const Vector3 & dir, const int & attackType)
{
	if ((UINT)attackType >= skillSet.size()) return false;

	if (skillSet[attackType]->Active(this))
	{
		canMove = skillSet[attackType]->GetCanMove();
		moveStopTime = skillSet[attackType]->GetMoveStopTime();
		return true;
	}

	return false;
}

void Character::HealMyself(float _recovery)
{
	if (stat.hp < stat.maxHp)
	{
		SoundManager::PlayOverlapSound(L"Heal.wav", SoundChannel::EFFECT);
		stat.hp += _recovery;
		if (stat.hp > stat.maxHp)
		{
			stat.hp = stat.maxHp;
		}
	}
}

bool Character::IsNotAlliance(GameObject * a, GameObject * b)
{
	Character* cb = dynamic_cast<Character*>(b);
	if (cb == nullptr) return false;
	return (a->team != b->team);
}



void Character::SetTexture(State _state, TextureKey _beginTextureKey, int _aniFrame, int _endFrame) {
	for (int i = 0; i < 8; i++)
	{
		startArray[(int)_state][(int)Direction::D + i] = (TextureKey)((int)_beginTextureKey + (i * _aniFrame));
		if (-1 == _endFrame)
			endArray[(int)_state][(int)Direction::D + i] = (TextureKey)((int)_beginTextureKey + (i * _aniFrame) + (_aniFrame - 1));
		else
			endArray[(int)_state][(int)Direction::D + i] = (TextureKey)((int)_beginTextureKey + (i * _aniFrame) + (_endFrame - 1));
	}
}