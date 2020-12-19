#pragma once
#include "IComponent.h"
namespace PKH
{
	class Animation :
		public IComponent
	{
	public:
		explicit Animation(GameObject* owner);
		explicit Animation(const Animation& rhs);
		virtual ~Animation();

		virtual void Update();
		virtual IComponent* Clone() override;

	};
}


