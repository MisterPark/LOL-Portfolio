#pragma once

enum COLTYPE{PLAYER, ENEMY, PLAYER_ATTACK, PLAYER_MULTI_ATTACK, ENEMY_MULTI_ATTACK, ENEMY_ATTACK,TRIGGERBOX,ITEM, COIN, COL_NPC, END};

namespace PKH
{
	class CollisionManager
	{
	private:
		CollisionManager();
		~CollisionManager();

	public:
		static CollisionManager* GetInstance();
		static void Destroy();

	public:
		void Update();
		void ObjectDeadCheck();
		void CollisionCheck(COLTYPE srcType, COLTYPE dstType);
		void Release();

	public:
		static void RegisterObject(COLTYPE colType, GameObject* _pObj);
		void DisregisterObject(GameObject* obj);
		static void DisregisterObject(COLTYPE colType, GameObject* _pObj);
		static bool FindObject(COLTYPE colType, GameObject* _pObj);
		static bool IsCollided(GameObject* target, GameObject* other);

		list<GameObject*> objectList[COLTYPE::END];
	};
}

