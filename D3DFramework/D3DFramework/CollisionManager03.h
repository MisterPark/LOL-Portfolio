#pragma once

namespace PKH
{
	class CollisionManager03
	{
	public:
		enum OBJ03 { PLAYER, MONSTER, BOSS, PLAYER_SHIELD,PLAYER_BULLET, MONSTER_BULLET, END };
	private:
		CollisionManager03();
		~CollisionManager03();

	
	public:
		static CollisionManager03* GetInstance();
		static void Destroy();

		static void CollisionSphere(GameObject* rDstObj, GameObject* rSrcObj);
		static bool CheckSphere(GameObject* rDstObj, GameObject* rSrcObj);

		static void Update();
		static void RegisterObject(GameObject* _pObj);
		static void RegisterObject(OBJ03 _eobj,GameObject* _pObj);
		static void DisregisterObject(GameObject* _pObj);
		static bool FindObject(GameObject* _pObj);

		static bool IsCollided(GameObject* target, GameObject* other);
	private:
		list<GameObject*> objList[OBJ03::END];
		vector<GameObject*> objectList;
	};


}

