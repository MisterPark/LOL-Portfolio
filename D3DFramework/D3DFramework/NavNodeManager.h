#pragma once

class NavNode;

class NavNodeManager
{
private:
	NavNodeManager();
	~NavNodeManager();

public:
	static NavNodeManager* GetInstance();
	static void Destroy();


	static void Save();
	static void Load();
	static void LoadDebug();

	static void AddNode(NavNode* node);
	static void DeleteNode(NavNode* node);
	
	static void DeleteSelectedNodes();
	static NavNode* FindNode(int id);

	static void SelectNode(NavNode* node);
	static void LinkNode();
	static void ClearSelectedNodes();
	static void ClearAll();

	// 모든 노드 자동링크 (벽감지)
	static void LinkAll();
private:
	map<int,NavNode*> nodes;
	list<NavNode*> selectedNodes;

};

