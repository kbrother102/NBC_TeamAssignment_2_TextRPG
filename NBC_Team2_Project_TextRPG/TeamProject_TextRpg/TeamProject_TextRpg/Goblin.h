#pragma once
#include "Monster.h"

class ChangMinKong : public Monster
{
public:

	ChangMinKong() : name_("창민튜터님"),
		health_(0), attack_(0), bIsAlive_(false),
		exp_(0), gold_(0) {
	}

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

	~ChangMinKong()
	{
		std::cout << "고생하셨습니다 Zep에서 뵈어요!" << std::endl;
	}
private:
	std::string name_;
	int health_;
	int attack_;
	bool bIsAlive_;
	int exp_;
	int gold_;
};

