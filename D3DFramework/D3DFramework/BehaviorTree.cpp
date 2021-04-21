#include "stdafx.h"
#include "BehaviorTree.h"

Engine::BehaviorTree::Node::Node()
{

}

Engine::BehaviorTree::Node::~Node()
{

}

Engine::BehaviorTree::BehaviorTree(GameObject* owner) : IComponent(owner)
{
}

Engine::BehaviorTree::BehaviorTree(const BehaviorTree& rhs) : IComponent(rhs)
{
    this->root = rhs.root;
}

Engine::BehaviorTree::~BehaviorTree()
{
    if (root != nullptr)
    {
        delete root;
        root = nullptr;
    }
}

void Engine::BehaviorTree::Update()
{
    if (enable == false) return;
    if (root == nullptr) return;
    root->Update();
}

IComponent* Engine::BehaviorTree::Clone()
{
    return new BehaviorTree(*this);
}

void Engine::BehaviorTree::SetRoot(BehaviorTree::Node* _root)
{
    this->root = _root;
}


Engine::CompositeNode::CompositeNode()
{
}

//===================================================
Engine::CompositeNode::~CompositeNode()
{
    for (auto& child : children)
    {
        delete child;
    }
    children.clear();
}

void Engine::CompositeNode::AddChild(BehaviorTree::Node* _node)
{
    children.push_back(_node);
}

Engine::DecoratorNode::DecoratorNode()
{
}

//===================================================
Engine::DecoratorNode::~DecoratorNode()
{
    if (child != nullptr)
    {
        delete child;
        child = nullptr;
    }
}

Engine::BehaviorTree::Node* DecoratorNode::GetChild()
{
    return child;
}

void Engine::DecoratorNode::SetChild(BehaviorTree::Node* _node)
{
    child = _node;
}


//===================================================
Engine::SequenceNode::SequenceNode()
{
}

Engine::BehaviorTree::Status SequenceNode::Update()
{
    for (auto& child : children)
    {
        BehaviorTree::Status status = child->Update();
        if (status != BehaviorTree::Status::Success)
        {
            return status;
        }
    }
    return BehaviorTree::Status::Success;
}

//===================================================
Engine::SelectorNode::SelectorNode()
{
}

Engine::BehaviorTree::Status SelectorNode::Update()
{
    for (auto& child : children)
    {
        BehaviorTree::Status status = child->Update();
        if (status != BehaviorTree::Status::Failure)
        {
            return status;
        }
    }
    return BehaviorTree::Status::Failure;
}

//===================================================
Engine::RepeatNode::RepeatNode(int _count)
{
    numRepeats = _count;
}

Engine::BehaviorTree::Status RepeatNode::Update()
{
    if (child == nullptr) return BehaviorTree::Status::Failure;
    
    if (repeatCount == numRepeats) return BehaviorTree::Status::Success;
    child->Update();
    repeatCount++;

    return BehaviorTree::Status::Running;
}
