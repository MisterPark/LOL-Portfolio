#pragma once
#include "IComponent.h"

class Unit;

namespace PKH
{
	class NavMeshMap;

	class NavMeshAgent : public IComponent
	{
	public:
		explicit NavMeshAgent(GameObject* owner);
		explicit NavMeshAgent(const NavMeshAgent& rhs);
		virtual ~NavMeshAgent();

		virtual void Update();

		// IComponent을(를) 통해 상속됨
		virtual IComponent* Clone() override;

	public:
		bool Search(const Vector3& dest, list<Vector3>* outPath);
		bool SetDestination(const Vector3& target, bool noSearch = false);
		void Stop();
		void Resume();
		void Move(const Vector3& offset);
		void ResetPath();
		void SetStoppingDistance(float _dist);
		void SetPath(list<Vector3>& _path);
		// 경유지 임의 삽입
		void PushLayover(const Vector3& _point);
		void SetSpeed(float _speed);

	private:
		Unit* unit = nullptr;
		NavMeshMap* navMeshMap = nullptr;
		list<Vector3> path;
		Vector3 nextPosition;
		bool isDestination = true;

		float stoppingDistance = 0.1f;
		Vector3 destination;
		float radius = 0.f;
		float speed = 5.f;
		
		bool isMoving = true;

	};
}


