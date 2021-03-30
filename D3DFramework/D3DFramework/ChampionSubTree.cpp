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

	ActionNode<Unit>* skillAction = new ActionNode<Unit>();
	skillAction->SetAction((Unit**)&champ, &Unit::StartNextSkill);
	rangeCondition->SetChild(skillAction);

	ActionNode<Unit>* chaseAction = new ActionNode<Unit>();
	chaseAction->SetAction((Unit**)&champ, &Unit::ChaseTarget);
	targetSelector->AddChild(chaseAction);

	//R
	ConditionNode<Skill>* skillRCondition = new ConditionNode<Skill>();
	skillRCondition->SetCondition((Skill**)&champ->skillList[(int)SkillIndex::R], &Skill::IsActive);
	this->AddChild(skillRCondition);

	ActionNode<Skill>* skillRAction = new ActionNode<Skill>();
	skillRAction->SetAction((Skill**)&champ->skillList[(int)SkillIndex::R], &Skill::Active);
	skillRCondition->SetChild(skillRAction);

	// E
	ConditionNode<Skill>* skillECondition = new ConditionNode<Skill>();
	skillECondition->SetCondition((Skill**)&champ->skillList[(int)SkillIndex::E], &Skill::IsActive);
	this->AddChild(skillECondition);

	ActionNode<Skill>* skillEAction = new ActionNode<Skill>();
	skillEAction->SetAction((Skill**)&champ->skillList[(int)SkillIndex::E], &Skill::Active);
	skillECondition->SetChild(skillEAction);

	// W
	ConditionNode<Skill>* skillWCondition = new ConditionNode<Skill>();
	skillWCondition->SetCondition((Skill**)&champ->skillList[(int)SkillIndex::W], &Skill::IsActive);
	this->AddChild(skillWCondition);

	ActionNode<Skill>* skillWAction = new ActionNode<Skill>();
	skillWAction->SetAction((Skill**)&champ->skillList[(int)SkillIndex::W], &Skill::Active);
	skillWCondition->SetChild(skillWAction);

	// Q
	ConditionNode<Skill>* skillQCondition = new ConditionNode<Skill>();
	skillQCondition->SetCondition((Skill**)&champ->skillList[(int)SkillIndex::Q], &Skill::IsActive);
	this->AddChild(skillQCondition);

	ActionNode<Skill>* skillQAction = new ActionNode<Skill>();
	skillQAction->SetAction((Skill**)&champ->skillList[(int)SkillIndex::Q], &Skill::Active);
	skillQCondition->SetChild(skillQAction);
	//

	ConditionNode<NavMeshAgent>* moveCondition = new ConditionNode<NavMeshAgent>();
	moveCondition->SetCondition((NavMeshAgent**)&champ->agent, &NavMeshAgent::IsPathRemain);
	this->AddChild(moveCondition);

	ActionNode<Unit>* moveAction = new ActionNode<Unit>();
	moveAction->SetAction((Unit**)&champ, &Unit::MoveAction);
	moveCondition->SetChild(moveAction);

	SelectorNode* attackSelector = new SelectorNode();
	this->AddChild(attackSelector);

	ConditionNode<Unit>* attackCondition = new ConditionNode<Unit>();
	attackCondition->SetCondition((Unit**)&champ, &Unit::HasAttackTarget);
	attackSelector->AddChild(attackCondition);

	ActionNode<Skill>* attackAction = new ActionNode<Skill>();
	attackAction->SetAction((Skill**)&champ->skillList[(int)SkillIndex::Attack], &Skill::Active);
	attackCondition->SetChild(attackAction);

	ActionNode<Unit>* idleAction = new ActionNode<Unit>();
	idleAction->SetAction((Unit**)&champ, &Unit::IdleAction);
	this->AddChild(idleAction);
}

ChampionSubTree::~ChampionSubTree()
{
}