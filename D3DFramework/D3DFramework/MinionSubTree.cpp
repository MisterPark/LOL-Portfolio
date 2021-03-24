#include "stdafx.h"
#include "MinionSubTree.h"

MinionSubTree::MinionSubTree(Minion* owner)
{
	minion = owner;

	ConditionNode<Unit>* deathCondition = new ConditionNode<Unit>();
	deathCondition->SetCondition((Unit**)&minion, &Unit::IsDead);
	this->AddChild(deathCondition);

	ActionNode<Unit>* deathAction = new ActionNode<Unit>();
	deathAction->SetAction((Unit**)&minion, &Unit::DeadAction);
	deathCondition->SetChild(deathAction);

	ConditionNode<NavMeshAgent>* moveCondition = new ConditionNode<NavMeshAgent>();
	moveCondition->SetCondition((NavMeshAgent**)&minion->agent, &NavMeshAgent::IsPathRemain);
	this->AddChild(moveCondition);

	ActionNode<Unit>* moveAction = new ActionNode<Unit>();
	moveAction->SetAction((Unit**)&minion, &Unit::MoveAction);
	moveCondition->SetChild(moveAction);

	SelectorNode* attackSelector = new SelectorNode();
	this->AddChild(attackSelector);

	ConditionNode<Unit>* attackCondition = new ConditionNode<Unit>();
	attackCondition->SetCondition((Unit**)&minion, &Unit::HasAttackTarget);
	attackSelector->AddChild(attackCondition);

	ActionNode<Unit>* attackAction = new ActionNode<Unit>();
	attackAction->SetAction((Unit**)&minion, &Unit::AttackAction);
	attackCondition->SetChild(attackAction);

	ConditionNode<Unit>* countAttackCondition = new ConditionNode<Unit>();
	countAttackCondition->SetCondition((Unit**)&minion, &Unit::HasLastAttacker);
	attackSelector->AddChild(countAttackCondition);

	ActionNode<Unit>* countAttackAction = new ActionNode<Unit>();
	countAttackAction->SetAction((Unit**)&minion, &Unit::CounterAttack);
	countAttackCondition->SetChild(countAttackAction);

	ActionNode<Unit>* idleAction = new ActionNode<Unit>();
	idleAction->SetAction((Unit**)&minion, &Unit::IdleAction);
	this->AddChild(idleAction);
}

MinionSubTree::~MinionSubTree()
{
}
