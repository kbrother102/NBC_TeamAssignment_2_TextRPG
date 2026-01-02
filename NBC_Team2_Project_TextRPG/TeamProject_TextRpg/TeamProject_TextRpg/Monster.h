#pragma once
#include "Creature.h"
#include <string>

class Action;

class Monster : public Creature
{
public:
	virtual std::string GetName() const = 0;
	virtual int GetHealth() = 0;
	virtual int GetAttack() = 0;
	virtual int GetGold() = 0;
	virtual int GetExp() = 0;
	virtual void TakeDamage(int dmg) = 0;
	virtual void SpawnMob(int level) = 0;
	virtual void UseSkill() = 0;
	virtual StatComponent* GetStatComponent() = 0;
private:
	Action* MonAct_;
};