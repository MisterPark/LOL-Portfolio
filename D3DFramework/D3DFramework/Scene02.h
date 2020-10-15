#pragma once
#include "IScene.h"

using namespace PKH;

class Player02;
class Boss02;

class Scene02 :
	public IScene
{
public:
	// IScene을(를) 통해 상속됨
	virtual void OnLoaded() override;
	virtual void OnUnloaded() override;
	virtual void Update() override;

	bool IsEndScene();

	void SpawnByTime();

	void SpawnEnemy01(Vector3 pos, Vector3 look = Vector3::DOWN);
	void SpawnEnemy02(Vector3 pos, Vector3 look = Vector3::DOWN);
	void SpawnBoss(Vector3 pos, Vector3 look = Vector3::DOWN);

private:
	Player02* myPlayer = nullptr;
	Boss02* myBoss = nullptr;
	bool isBossSpawn = false;
	bool isEnd = false;

	float playTime = 0.f;

	int spawnType = 0;
	int spawnType2 = 0;

	float spawnTime = 0.f;
	float spawnTime2 = 0.f;
	float endCount = 0.f;
};

