#pragma once
#include "Creature.h"
#include "Action.h"
#include "StatComponent.h"
#include <string>

class Action;
class StatComponent;

class Monster : public Creature
{
public:
	virtual std::string GetName() const = 0;
	virtual int GetHealth() = 0;
	virtual int GetAttack() = 0;
	virtual int GetGold() = 0;
	virtual int GetExp() = 0;
	virtual bool GetIsDead() = 0;
	virtual void TakeDamage(int dmg) = 0;
	virtual void SpawnMob(int level) = 0;
	virtual void UseSkill() = 0;
	virtual StatComponent* GetStatComponent() = 0;
	virtual Action* GetActionComponent() = 0;
protected:
	StatComponent* monStat_ = new StatComponent();
	//Action* monAct_ = new Action();
};