#pragma once
#include "Creature.h"
class Monster : public Creature

{
public:
	virtual std::string GetName() = 0;
	virtual int GetHealth() = 0;
	virtual int GetAttack() = 0;
	virtual void TakeDamaged(int damage) = 0;
	virtual void Buff() = 0;
	virtual void Attack() = 0;
};

