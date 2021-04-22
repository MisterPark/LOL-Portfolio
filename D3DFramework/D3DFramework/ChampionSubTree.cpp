#include "stdafx.h"
#include "ChampionSubTree.h"
#include "Unit.h"
#include "Skill.h"

ChampionSubTree::ChampionSubTree(Champion* owner)
{
	champ = owner;

	ConditionNode<Unit>* deathCondition = new ConditionNode<Unit>();
	deathCondition->SetCondition((Unit**)&champ, &Unit::IsDead);
	this->AddChild(deathCondition);

	ActionNode<Unit>* deathAction = new ActionNode<Unit>();
	deathAction->SetAction((Unit**)&champ, &Unit::DeadAction);
	deathCondition->SetChild(deathAction);


	ConditionNode<Unit>* skillCondition = new ConditionNode<Unit>();
	skillCondition->SetCondition((Unit**)&champ, &Unit::HasNextSkill);
	this->AddChild(skillCondition);

	SelectorNode* targetSelector = new SelectorNode();
	skillCondition->SetChild(targetSelector);

	ConditionNode<Skill>* rangeCondition = new ConditionNode<Skill>();
	rangeCondition->SetCondition((Skill**)&champ->nextSkill, &Skill::InRange);
	targetSelector->AddChild(rangeCondition);

	ActionNode<Unit>* nextSkillAction = new ActionNode<Unit>();
	nextSkillAction->SetAction((Unit**)&champ, &Unit::StartNextSkill);
	rangeCondition->SetChild(nextSkillAction);

	ActionNode<Unit>* chaseAction = new ActionNode<Unit>();
	chaseAction->SetAction((Unit**)&champ, &Unit::ChaseTarget);
	targetSelector->AddChild(chaseAction);


	ConditionNode<Unit>* skillsCondition = new ConditionNode<Unit>();
	skillsCondition->SetCondition((Unit**)&champ, &Unit::BehaviorTreeSkillSet);
	this->AddChild(skillsCondition);

	ActionNode<Skill>* skillAction = new ActionNode<Skill>();
	skillAction->SetAction((Skill**)&champ->behaviorTreeSkill, &Skill::Active);
	skillsCondition->SetChild(skillAction);
	//

	SelectorNode* attackSelector = new SelectorNode();
	this->AddChild(attackSelector);

	ConditionNode<Unit>* attackCondition = new ConditionNode<Unit>();
	attackCondition->SetCondition((Unit**)&champ, &Unit::HasAttackTarget);
	attackSelector->AddChild(attackCondition);

	ConditionNode<Skill>* attackRangeCondition = new ConditionNode<Skill>();
	attackRangeCondition->SetCondition((Skill**)&champ->skillList[(int)SkillIndex::Attack], &Skill::InRange);
	attackCondition->SetChild(attackRangeCondition);

	ActionNode<Skill>* attackAction = new ActionNode<Skill>();
	attackAction->SetAction((Skill**)&champ->skillList[(int)SkillIndex::Attack], &Skill::Active);
	attackRangeCondition->SetChild(attackAction);

	ConditionNode<NavMeshAgent>* moveCondition = new ConditionNode<NavMeshAgent>();
	moveCondition->SetCondition((NavMeshAgent**)&champ->agent, &NavMeshAgent::IsPathRemain);
	this->AddChild(moveCondition);

	ActionNode<Unit>* moveAction = new ActionNode<Unit>();
	moveAction->SetAction((Unit**)&champ, &Unit::MoveAction);
	moveCondition->SetChild(moveAction);


	ActionNode<Unit>* idleAction = new ActionNode<Unit>();
	idleAction->SetAction((Unit**)&champ, &Unit::IdleAction);
	this->AddChild(idleAction);
}

ChampionSubTree::~ChampionSubTree()
{
}