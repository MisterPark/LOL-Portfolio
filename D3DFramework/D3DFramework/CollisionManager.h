#pragma once

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

		static void Update();
		static void RegisterObject(GameObject* _pObj);
		static void DisregisterObject(GameObject* _pObj);
		static bool FindObject(GameObject* _pObj);

		static bool IsCollided(GameObject* target, GameObject* other);

		vector<GameObject*> objectList;
	};


}

