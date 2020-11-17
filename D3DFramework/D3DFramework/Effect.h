#pragma once
#include "GameObject.h"

class Effect:
	public GameObject
{
public:
	Effect();
	Effect(const Vector3 & pos, const Vector3& size, TextureKey start, TextureKey end, float delay, bool plane, bool isBillY, float radianY, bool loop, float lifeTime, bool isMove, float speed, const Vector3 & dir, bool onTerrain, float _offsetY, Character* _tar);
	virtual ~Effect();

public:
	// GameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	bool IsDie();
	// 지형 타기
	void OnTerrain();

public:
	/*
	start : 텍스쳐 시작 번지, end : 텍스쳐 끝 번지
	delay : 애니메이션 프레임 사이의 딜레이 값, plane : 눕힌 이펙트로 할 것인지
	isBillY : billboardYaw를 사용할 것인지, loop : 반복되는 이펙트인지
	lifeTime : 반복되는 이펙트라면 몇 초 동안 존재하는지, isMove : 움직이는 이펙트인지
	speed : 움직이는 속도, dir : 움직이는 방향
	*/
	static Effect* Create(
		const Vector3& pos,
		const Vector3& size,
		TextureKey start,
		TextureKey end,
		float delay,
		bool plane = false,
		bool isBillY = true,
		float radianY = 0.f,
		bool loop = false,
		float lifeTime = 0.f,
		bool isMove = false,
		float speed = 0.f,
		const Vector3& dir = { 0.f, 0.f, 1.f },
		bool isOnTerrain = false,
		float _offsetY = 0.f,
		Character* _target = nullptr
	);
	Animation2D* anim;
private:
	Character* target;
	Vector3 direction;

	float animSpeed;
	float lifeTime;

	TextureKey startKey;
	TextureKey endKey;

	bool isBillboardY;
	bool isMove;
	bool isLoop;
	bool isEnd;
	bool isPlane;
	bool isOnTerrain;
	float offsetY;
};