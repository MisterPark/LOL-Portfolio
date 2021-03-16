﻿#include "stdafx.h"
#include "ChampionSubTree.h"
#include "Unit.h"
#include "Skill.h"

ChampionSubTree::ChampionSubTree(Champion* owner)
{

	ConditionNode<Unit>* deathCondition = new ConditionNode<Unit>();
	deathCondition->SetCondition(owner, &Unit::IsDead);
	this->AddChild(deathCondition);

	ActionNode<Unit>* deathAction = new ActionNode<Unit>();
	deathAction->SetAction(owner, &Unit::DeadAction);
	deathCondition->SetChild(deathAction);

	//R
	ConditionNode<Skill>* skillRCondition = new ConditionNode<Skill>();
	skillRCondition->SetCondition(owner->skillList[(int)SkillIndex::R], &Skill::IsActive);
	this->AddChild(skillRCondition);

	ActionNode<Skill>* skillRAction = new ActionNode<Skill>();
	skillRAction->SetAction(owner->skillList[(int)SkillIndex::R], &Skill::Active);
	skillRCondition->SetChild(skillRAction);

	// E
	ConditionNode<Skill>* skillECondition = new ConditionNode<Skill>();
	skillECondition->SetCondition(owner->skillList[(int)SkillIndex::E], &Skill::IsActive);
	this->AddChild(skillECondition);

	ActionNode<Skill>* skillEAction = new ActionNode<Skill>();
	skillEAction->SetAction(owner->skillList[(int)SkillIndex::E], &Skill::Active);
	skillECondition->SetChild(skillEAction);

	// W
	ConditionNode<Skill>* skillWCondition = new ConditionNode<Skill>();
	skillWCondition->SetCondition(owner->skillList[(int)SkillIndex::W], &Skill::IsActive);
	this->AddChild(skillWCondition);

	ActionNode<Skill>* skillWAction = new ActionNode<Skill>();
	skillWAction->SetAction(owner->skillList[(int)SkillIndex::W], &Skill::Active);
	skillWCondition->SetChild(skillWAction);

	// Q
	ConditionNode<Skill>* skillQCondition = new ConditionNode<Skill>();
	skillQCondition->SetCondition(owner->skillList[(int)SkillIndex::Q], &Skill::IsActive);
	this->AddChild(skillQCondition);

	ActionNode<Skill>* skillQAction = new ActionNode<Skill>();
	skillQAction->SetAction(owner->skillList[(int)SkillIndex::Q], &Skill::Active);
	skillQCondition->SetChild(skillQAction);
	//

	ConditionNode<NavMeshAgent>* moveCondition = new ConditionNode<NavMeshAgent>();
	moveCondition->SetCondition(owner->agent, &NavMeshAgent::IsPathRemain);
	this->AddChild(moveCondition);

	ActionNode<Unit>* moveAction = new ActionNode<Unit>();
	moveAction->SetAction(owner, &Unit::MoveAction);
	moveCondition->SetChild(moveAction);

	SelectorNode* attackSelector = new SelectorNode();
	this->AddChild(attackSelector);

	ConditionNode<Unit>* attackCondition = new ConditionNode<Unit>();
	attackCondition->SetCondition(owner, &Unit::HasAttackTarget);
	attackSelector->AddChild(attackCondition);

	ActionNode<Unit>* attackAction = new ActionNode<Unit>();
	attackAction->SetAction(owner, &Unit::AttackAction);
	attackCondition->SetChild(attackAction);

	ConditionNode<Unit>* countAttackCondition = new ConditionNode<Unit>();
	countAttackCondition->SetCondition(owner, &Unit::HasLastAttacker);
	attackSelector->AddChild(countAttackCondition);

	ActionNode<Unit>* countAttackAction = new ActionNode<Unit>();
	countAttackAction->SetAction(owner, &Unit::CounterAttack);
	countAttackCondition->SetChild(countAttackAction);

	ActionNode<Unit>* idleAction = new ActionNode<Unit>();
	idleAction->SetAction(owner, &Unit::IdleAction);
	this->AddChild(idleAction);
}

ChampionSubTree::~ChampionSubTree()
{
}