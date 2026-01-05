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
	//getter
		//string
	virtual std::string GetName() const = 0;
		//int
	virtual int GetHealth() const = 0;
	virtual int GetAttack() const = 0;
	virtual int GetGold() const = 0;
	virtual int GetExp() const = 0;
		//bool
	virtual bool GetIsDead() const = 0;
		//component
	virtual StatComponent* GetStatComponent() = 0;
	virtual Action* GetActionComponent() = 0;

	virtual void TakeDamage(int dmg) = 0;
	virtual void SpawnMob(int level) = 0;
	virtual void UseSkill() = 0;

	~Monster()
	{
		delete monStat_;
	}

protected:
	StatComponent* monStat_ = new StatComponent();

};