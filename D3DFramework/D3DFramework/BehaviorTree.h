#pragma once
#include "IComponent.h"
#include <iostream>
using namespace std;

namespace Engine
{
	class BehaviorTree : public IComponent
	{
	public:
		enum class Status : int
		{
			Success,
			Failure,
			Running,
		};
	public:
		class Node
		{
		public:
			Node();
			virtual ~Node();
			virtual BehaviorTree::Status Update() = 0;
		};

	public:
		explicit BehaviorTree(GameObject* owner);
		explicit BehaviorTree(const BehaviorTree& rhs);
		virtual ~BehaviorTree();

		virtual void Update() override;
		virtual IComponent* Clone() override;

		void SetRoot(BehaviorTree::Node* _root);

	protected:
		BehaviorTree::Node* root = nullptr;

		
	};

	class CompositeNode : public BehaviorTree::Node
	{
	public:
		CompositeNode();
		virtual ~CompositeNode();
		void AddChild(BehaviorTree::Node* _node);
	protected:
		list<BehaviorTree::Node*> children;
	};

	class DecoratorNode : public BehaviorTree::Node
	{
	public:
		DecoratorNode();
		virtual ~DecoratorNode();
		BehaviorTree::Node* GetChild();
		void SetChild(BehaviorTree::Node* _node);
	protected:
		BehaviorTree::Node* child = nullptr;
	};

	class SequenceNode final : public CompositeNode
	{
	public:
		SequenceNode();
		virtual BehaviorTree::Status Update() override;
	};

	class SelectorNode : public CompositeNode
	{
	public:
		SelectorNode();
		virtual BehaviorTree::Status Update() override;
	};

	class RepeatNode final : public DecoratorNode
	{
	public:
		RepeatNode(int _count);
		virtual BehaviorTree::Status Update() override;
	private:
		int numRepeats = 0;
		int repeatCount = 0;
	};

	template<class T>
	class ConditionNode final : public DecoratorNode
	{
	public:
		ConditionNode();
		virtual BehaviorTree::Status Update() override;

		void SetCondition(T** _pInstance, bool (T::*_Func)());

	private:
		T** pInstance = nullptr;
		bool (T::*Func)() = nullptr;
	};

	template<class T>
	inline ConditionNode<T>::ConditionNode()
	{
	}

	template<class T>
	inline BehaviorTree::Status ConditionNode<T>::Update()
	{
		if(pInstance == nullptr) return BehaviorTree::Status::Failure;
		if (Func == nullptr) return BehaviorTree::Status::Failure;
		if (((*pInstance)->*Func)() == false) return BehaviorTree::Status::Failure;

		return child->Update();
	}

	template<class T>
	inline void ConditionNode<T>::SetCondition(T** _pInstance, bool(T::* _Func)())
	{
		this->pInstance = _pInstance;
		this->Func = _Func;
	}

	template<class T>
	class ActionNode final : public BehaviorTree::Node
	{
	public:
		ActionNode();
		virtual BehaviorTree::Status Update() override;

		void SetAction(T** _instance, void (T::* _Func)());

	private:
		T** instance = nullptr;
		void (T::* Func)() = nullptr;
	};

	template<class T>
	inline ActionNode<T>::ActionNode()
	{
	}

	template<class T>
	inline BehaviorTree::Status ActionNode<T>::Update()
	{
		if (Func == nullptr) return BehaviorTree::Status::Failure;
		((*instance)->*Func)();
		return BehaviorTree::Status::Success;
	}

	template<class T>
	inline void ActionNode<T>::SetAction(T** _instance, void(T::* _Func)())
	{
		this->instance = _instance;
		this->Func = _Func;
	}

}
