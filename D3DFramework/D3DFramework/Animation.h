#pragma once
#include "IComponent.h"

class EnemyUnit;
enum class UnitState;

namespace PKH
{
	class Animation :
		public IComponent
	{
	public:
		struct Node
		{
			UINT index = 0;
			string name;
			bool isLoop = false;
		};

		explicit Animation(GameObject* owner);
		explicit Animation(const Animation& rhs);
		virtual ~Animation();

		virtual void PostUpdate();
		virtual IComponent* Clone() override;

	public:
		void AttachToDynamicMesh(DynamicMesh* dmesh);
		string GetNameByState(UnitState state);

		void SetLoop(UnitState state, bool loop);

	private:
		EnemyUnit* unit = nullptr;
		DynamicMesh* dmesh = nullptr;
		
		UINT currentAnim = 0;
		map<UINT, Animation::Node> animsets;
	};
}


