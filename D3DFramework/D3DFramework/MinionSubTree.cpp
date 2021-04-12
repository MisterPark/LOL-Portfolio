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

	ConditionNode<Unit>* attackCondition = new ConditionNode<Unit>();
	attackCondition->SetCondition((Unit**)&minion, &Unit::HasAttackTarget);
	this->AddChild(attackCondition);

	SelectorNode* attackSelector = new SelectorNode();
	attackCondition->SetChild(attackSelector);

	ConditionNode<Unit>* rangeCondition = new ConditionNode<Unit>();
	rangeCondition->SetCondition((Unit**)&minion, &Unit::IsTargetInAttackRange);
	attackSelector->AddChild(rangeCondition);

	//ConditionNode<Skill>* rangeCondition = new ConditionNode<Skill>();
	//rangeCondition->SetCondition((Skill**)&minion->skillList[(int)SkillIndex::Attack], &Skill::InRange);
	//attackSelector->AddChild(rangeCondition);

	ActionNode<Skill>* attackAction = new ActionNode<Skill>();
	attackAction->SetAction((Skill**)&minion->skillList[(int)SkillIndex::Attack], &Skill::Active);
	rangeCondition->SetChild(attackAction);

	ActionNode<Unit>* chaseAction = new ActionNode<Unit>();
	chaseAction->SetAction((Unit**)&minion, &Unit::ChaseTarget);
	attackSelector->AddChild(chaseAction);

	//ConditionNode<Unit>* countAttackCondition = new ConditionNode<Unit>();
	//countAttackCondition->SetCondition((Unit**)&minion, &Unit::HasLastAttacker);
	//attackSelector->AddChild(countAttackCondition);

	//ActionNode<Unit>* countAttackAction = new ActionNode<Unit>();
	//countAttackAction->SetAction((Unit**)&minion, &Unit::CounterAttack);
	//countAttackCondition->SetChild(countAttackAction);

	ConditionNode<NavMeshAgent>* moveCondition = new ConditionNode<NavMeshAgent>();
	moveCondition->SetCondition((NavMeshAgent**)&minion->agent, &NavMeshAgent::IsPathRemain);
	this->AddChild(moveCondition);

	ActionNode<Unit>* moveAction = new ActionNode<Unit>();
	moveAction->SetAction((Unit**)&minion, &Unit::MoveAction);
	moveCondition->SetChild(moveAction);

	ActionNode<Unit>* idleAction = new ActionNode<Unit>();
	idleAction->SetAction((Unit**)&minion, &Unit::IdleAction);
	this->AddChild(idleAction);
}

MinionSubTree::~MinionSubTree()
{
}
