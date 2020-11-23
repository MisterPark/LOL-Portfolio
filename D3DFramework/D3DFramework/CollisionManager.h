#pragma once

namespace PKH
{
	class Collider;
	class BoxCollider;
	class SphereCollider;

	class CollisionManager
	{
	private:
		CollisionManager();
		~CollisionManager();

		void Release();
	public:
		static CollisionManager* GetInstance();
		static void Destroy();

	public:
		void Update();
		void CollisionCheck(Layer srcType, Layer dstType);
		

	public:
		static void RegisterObject(Layer colType, Collider* _pObj);
		void DisregisterObject(Collider* obj);
		static void DisregisterObject(Layer colType, Collider* _pObj);
		static bool FindObject(Layer colType, Collider* _pObj);
		static bool IsCollided(Collider* target, Collider* other);

		static bool CheckSphereCollision(SphereCollider* src, SphereCollider* dest);
		static bool CheckAABBCollision(BoxCollider* src, BoxCollider* dest);
		static bool CheckOBBCollision(BoxCollider* src, BoxCollider* dest);

		list<Collider*> objectList[MaxOfEnum<Layer>()];
	};
}

