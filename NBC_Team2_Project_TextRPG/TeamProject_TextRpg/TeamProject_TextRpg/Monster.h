#pragma once
#include "Creature.h"
#include <string>

class Monster : public Creature
{
public:
	virtual std::string GetName() = 0;
	virtual int GetHealth() = 0;
	virtual int GetAttack() = 0;
	virtual int GetGold() = 0;
	virtual int GetExp() = 0;
	virtual void TakeDamage(int dmg) = 0;
	virtual void SpawnMob(int level) = 0;
	virtual void DieMob() = 0;
};