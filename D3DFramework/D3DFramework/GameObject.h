#pragma once

using namespace PKH;

namespace PKH
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();


		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Die();
		virtual void OnCollision(GameObject* target);

		Transform transform;
		bool isDead = false;
		bool isVisible = true;
		bool isEnable = true;
	};
}


