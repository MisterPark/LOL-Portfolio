#pragma once



namespace PKH
{
	enum class PathFinderType
	{
		None,
		Dijkstra,
		Astar,
	};


	class PathFinder
	{
	public:
		struct Node
		{
		public:
			Node* parent;
			Vector3 position;
			vector<Node*> adjacency;
			Node* destination;

			Node();
			Node(PathFinder::Node* parent, Vector3 position);
			virtual ~Node();

			virtual int G();
			virtual int H(Node* dest);
			virtual int F(Node* dest);

		};

		PathFinder();
		virtual ~PathFinder();

		virtual bool Search(const Vector3& start, const Vector3& dest) PURE;
	protected:
		// Search 전에 해줘야 할 것들 (매번)
		PKH::PathFinder::Node* FindStartNode(const Vector3& startPos);
		PKH::PathFinder::Node* FindDestinationNode(const Vector3& destPos);
		void SetDestination(PathFinder::Node* dest);
		
	public:
		// 외부에서 세팅 해줄것 (한번만)
		void AddNode(PathFinder::Node* pNode);
		void LinkNode(DWORD srcIndex, DWORD destIndex);

	public:
		// getter setter
		PathFinderType GetType();

		// 길찾기가 성공할 경우
		// resultNode 는 destNode 이고
		// resultNode 의 parent를 타고 타고 가다보면 출발지가 나옴
		// 연결되어있는 모든 노드는 경로임.
		// p.s 결과가 true인데 resultNode의 parent가 nullptr이면 이미 도착지인것
		PKH::PathFinder::Node* GetResultNode();
		
	protected:
		// 멤버
		vector<Node*> nodes;
		PathFinderType type = PathFinderType::None;
		
		
		PathFinder::Node* resultNode = nullptr;
	};


}
