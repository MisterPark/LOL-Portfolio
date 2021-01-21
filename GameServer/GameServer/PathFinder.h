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
		PKH::PathFinder::Node* FindStartNode(const Vector3& startPos, float radius = INFINITY);
		PKH::PathFinder::Node* FindDestinationNode(const Vector3& destPos, float radius = INFINITY);
		void SetDestination(PathFinder::Node* dest);
		// 탐색 완료시 경로 리스트에 저장
		void SetPath();
		// 경로 탐색 완료시 경로중에 시작노드 후보가 있는지 체크
		void OptimizeStartNode();
		void OptimizeDestinationNode(const Vector3& destPos);
		void Optimize();
	public:
		// 외부에서 세팅 해줄것 (한번만)
		void AddNode(DWORD index, PathFinder::Node* pNode);
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
		list<PKH::PathFinder::Node*>* GetPath();
		
	protected:
		// 멤버
		map<int, PKH::PathFinder::Node*> nodes;
		PathFinderType type = PathFinderType::None;
		PKH::PathFinder::Node* resultNode = nullptr;
		list<PathFinder::Node*> path;

		// 시작노드 후보
		// 시작노드 탐색시 가장 가까운 노드를 선택하지만
		// 그 노드가 최적의 길이 아닐 수도 있음.
		// 때문에 시작노드 후보자들을 넣어놓고
		// 최종 경로에서 경유지에 시작노드의 후보가 있다면
		// 그 후보 노드를 시작노드로 변경해야함.
		// key = dist ( 거리에 따른 정렬 )  
		map<int, Node*> candidatesStart;
		map<int, Node*> candidatesDest;
	};


}
