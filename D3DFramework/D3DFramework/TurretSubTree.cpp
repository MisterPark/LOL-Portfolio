#include "stdafx.h"
#include "TurretSubTree.h"

TurretSubTree::TurretSubTree(Turret* owner)
{
	turret = owner;

	ConditionNode<Unit>* deathCondition = new ConditionNode<Unit>();
	deathCondition->SetCondition((Unit**)&turret, &Unit::IsDead);
	this->AddChild(deathCondition);

	ActionNode<Unit>* deathAction = new ActionNode<Unit>();
	deathAction->SetAction((Unit**)&turret, &Unit::DeadAction);
	deathCondition->SetChild(deathAction);

	ConditionNode<NavMeshAgent>* moveCondition = new ConditionNode<NavMeshAgent>();
	moveCondition->SetCondition((NavMeshAgent**)&turret->agent, &NavMeshAgent::IsPathRemain);
	this->AddChild(moveCondition);

	ActionNode<Unit>* moveAction = new ActionNode<Unit>();
	moveAction->SetAction((Unit**)&turret, &Unit::MoveAction);
	moveCondition->SetChild(moveAction);

	SelectorNode* attackSelector = new SelectorNode();
	this->AddChild(attackSelector);

	ConditionNode<Unit>* attackCondition = new ConditionNode<Unit>();
	attackCondition->SetCondition((Unit**)&turret, &Unit::HasAttackTarget);
	attackSelector->AddChild(attackCondition);

	ActionNode<Unit>* attackAction = new ActionNode<Unit>();
	attackAction->SetAction((Unit**)&turret, &Unit::AttackAction);
	attackCondition->SetChild(attackAction);

	ConditionNode<Unit>* countAttackCondition = new ConditionNode<Unit>();
	countAttackCondition->SetCondition((Unit**)&turret, &Unit::HasLastAttacker);
	attackSelector->AddChild(countAttackCondition);

	ActionNode<Unit>* countAttackAction = new ActionNode<Unit>();
	countAttackAction->SetAction((Unit**)&turret, &Unit::CounterAttack);
	countAttackCondition->SetChild(countAttackAction);

	ActionNode<Unit>* idleAction = new ActionNode<Unit>();
	idleAction->SetAction((Unit**)&turret, &Unit::IdleAction);
	this->AddChild(idleAction);
}

TurretSubTree::~TurretSubTree()
{
}
