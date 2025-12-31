#pragma once
#include "Monster.h"

class ChangMinKong : public Monster
{
public:
	ChangMinKong(int level) : name_("ChangMin TuterNim")
	{
		std::srand((unsigned int)time(NULL));

		bIsBuff = false;
		health_ = (level * ((rand() % 11) + 20)); //체력 
		attack_ = (level * ((rand() % 6) + 5));

		std::cout << "Health : " << health_ << " ATK : " << attack_ << " Name : " << name_ << std::endl;
	}

	void TakeDamaged(int damage);
	void Buff();
	void Attack();

	std::string GetName() { return name_; }
	int GetHealth() { return health_; }
	int GetAttack() { return attack_; }

	~ChangMinKong()
	{
		std::cout << "고생하셨습니다 Zep에서 뵈어요!" << std::endl;
	}
private:
	std::string name_;
	int health_;
	int attack_;
	bool bIsBuff;
};

