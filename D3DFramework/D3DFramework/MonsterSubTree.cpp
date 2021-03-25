#include "stdafx.h"
#include "MonsterSubTree.h"


MonsterSubTree::MonsterSubTree(Monster* owner)
{
	monster = owner;

	ConditionNode<Unit>* deathCondition = new ConditionNode<Unit>();
	deathCondition->SetCondition((Unit**)&monster, &Unit::IsDead);
	this->AddChild(deathCondition);

	ActionNode<Unit>* deathAction = new ActionNode<Unit>();
	deathAction->SetAction((Unit**)&monster, &Unit::DeadAction);
	deathCondition->SetChild(deathAction);

	ConditionNode<NavMeshAgent>* moveCondition = new ConditionNode<NavMeshAgent>();
	moveCondition->SetCondition((NavMeshAgent**)&monster->agent, &NavMeshAgent::IsPathRemain);
	this->AddChild(moveCondition);

	ActionNode<Unit>* moveAction = new ActionNode<Unit>();
	moveAction->SetAction((Unit**)&monster, &Unit::MoveAction);
	moveCondition->SetChild(moveAction);

	ConditionNode<Unit>* attackCondition = new ConditionNode<Unit>();
	attackCondition->SetCondition((Unit**)&monster, &Unit::HasAttackTarget);
	this->AddChild(attackCondition);

	SelectorNode* attackSelector = new SelectorNode();
	attackCondition->SetChild(attackSelector);

	ConditionNode<Skill>* rangeCondition = new ConditionNode<Skill>();
	rangeCondition->SetCondition((Skill**)&monster->skillList[(int)SkillIndex::Attack], &Skill::InRange);
	attackSelector->AddChild(rangeCondition);

	ActionNode<Skill>* attackAction = new ActionNode<Skill>();
	attackAction->SetAction((Skill**)&monster->skillList[(int)SkillIndex::Attack], &Skill::Active);
	rangeCondition->SetChild(attackAction);

	ActionNode<Unit>* chaseAction = new ActionNode<Unit>();
	chaseAction->SetAction((Unit**)&monster, &Unit::ChaseTarget);
	attackSelector->AddChild(chaseAction);

	ConditionNode<Unit>* countAttackCondition = new ConditionNode<Unit>();
	countAttackCondition->SetCondition((Unit**)&monster, &Unit::HasLastAttacker);
	attackSelector->AddChild(countAttackCondition);

	ActionNode<Unit>* countAttackAction = new ActionNode<Unit>();
	countAttackAction->SetAction((Unit**)&monster, &Unit::CounterAttack);
	countAttackCondition->SetChild(countAttackAction);

	ActionNode<Unit>* idleAction = new ActionNode<Unit>();
	idleAction->SetAction((Unit**)&monster, &Unit::IdleAction);
	this->AddChild(idleAction);
}

MonsterSubTree::~MonsterSubTree()
{
}
