#pragma once
#include "Monster.h"
class BongJaeKong : public Monster
{
public:

	BongJaeKong() {}

	void SpawnMob(int level);
	void DieMob();
	void TakeDamage(int dmg);

	//게터함수
	std::string GetType() { return Type_; }
	std::string GetName() { return name_; }
	int GetHealth() { return health_; }
	int GetAttack() { return attack_; }
	int GetExp() { return exp_; }
	int GetGold() { return gold_; }
	bool GetAlive() { return bIsAlive_; }
	bool GetIsBoss() { return bIsBoss_; }

	~BongJaeKong()
	{
		//소멸자
	}
private:
	std::string name_ = "mob2";
	int health_ = 0;
	int attack_ = 0;
	int exp_ = 0;
	int gold_ = 0;
	bool bIsAlive_ = false;
	bool bIsBoss_ = false;
};

