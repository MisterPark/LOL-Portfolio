#pragma once
#include "PathFinder.h"

namespace Engine
{
	struct ComparePFNode
	{
		bool operator()(PathFinder::Node* a, PathFinder::Node* b)
		{
			return a->F(a->destination) > b->F(b->destination);
		}
	};

	class Astar : public PathFinder
	{
	public:
		Astar();
		virtual ~Astar();

		virtual bool Search(const Vector3& start, const Vector3& end) override;
	};

}

