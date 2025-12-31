#pragma once
#include "Creature.h"
#include <iostream>
#include <random>
#include <string>

class Monster : public Creature
{
public:
	virtual std::string GetName() = 0;
	virtual int GetHealth() = 0;
	virtual int GetAttack() = 0;
	virtual void TakeDamaged(int damage) = 0;
	virtual void SpawnMob(int level) = 0;
	virtual void DieMob() = 0;
};