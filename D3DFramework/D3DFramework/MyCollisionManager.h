#pragma once

namespace PKH
{
	class GameObject;
	class Transform;
}

class MyCollisionManager
{
public:
	enum OBJTAG { PLAYER, ENEMY, BOSS, PLAYER_BULLET, ENEMY_BULLET, END };

private:
	MyCollisionManager();
	~MyCollisionManager();

public:
	static MyCollisionManager* GetInstance();
	static void DestroyInstance();

public:
	void RegisterObject(OBJTAG tag, GameObject* obj);
	void UnListObject(OBJTAG tag, GameObject* obj);
	void Collide(OBJTAG dst, OBJTAG src);
	void Collide2(OBJTAG dst, OBJTAG src);
	void CullingBullet(OBJTAG tag);
	void CullingEnemy();
	bool IsCollision(Transform* dst, Transform* src);

private:
	void Release();

private:
	static MyCollisionManager* instance;
	list<GameObject*> objList[OBJTAG::END];
};

