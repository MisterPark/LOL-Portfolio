#pragma once
#include "IComponent.h"

class Unit;
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
			float period = 0.f;
			float speed = 1.f;
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
		void SetSpeed(UnitState state, float speed);
		bool IsFrameEnd();

	private:
		Unit* unit = nullptr;
		DynamicMesh* dmesh = nullptr;
		
		UINT currentAnim = 0;
	public:
		map<UINT, Animation::Node> animsets;
	};
}


