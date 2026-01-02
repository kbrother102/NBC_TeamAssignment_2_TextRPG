#pragma once
#include "Monster.h"
#include "StatComponent.h"

class EunIlPerk : public Monster
{
public:

	EunIlPerk()
	{
		monasterStat_ = new StatComponent();
	}

	void SpawnMob(int level);
	void TakeDamage(int dmg);
	StatComponent* GetStatComponent() { return monasterStat_; }
	void UseSkill();

	//게터함수
	//string
	std::string GetType() { return monasterStat_->GetType(); }
	std::string GetName() const { return name_; }

	//int
	int GetHealth() { return monasterStat_->GetHp(); }
	int GetAttack() { return monasterStat_->GetAttack(); }
	int GetExp() { return monasterStat_->GetExp(); }
	int GetGold() { return monasterStat_->GetGold(); }

	//bool
	bool GetAlive() { return monasterStat_->GetIsDead(); }
	bool GetIsBoss() { return bIsBoss_; }

	~EunIlPerk()
	{
		//소멸자
		delete monasterStat_;
	}

private:
	class StatComponent* monasterStat_;
	std::string name_ = "mob4";
	bool bIsBoss_ = false;
};

