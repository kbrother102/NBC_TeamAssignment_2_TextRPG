#pragma once
#include "Monster.h"
#include "StatComponent.h"
#include "Action.h"

class GeukMinKong : public Monster
{
public:

	GeukMinKong()
	{
		monStat_ = new StatComponent();
		monAct_ = new Action();
	}

	void SpawnMob(int level);
	void TakeDamage(int dmg);
	StatComponent* GetStatComponent() { return monStat_; }
	Action* GetActionComponent() { return monAct_; }
	void UseSkill();

	//게터함수
	//string
	std::string GetType() { return monStat_->GetType(); }
	std::string GetName() const { return name_; }

	//int
	int GetHealth() { return monStat_->GetHp(); }
	int GetAttack() { return monStat_->GetAttack(); }
	int GetExp() { return monStat_->GetExp(); }
	int GetGold() { return monStat_->GetGold(); }

	//bool
	bool GetIsDead() { return monStat_->GetIsDead(); }
	bool GetIsBoss() { return bIsBoss_; }

	~GeukMinKong()
	{
		//소멸자
		delete monStat_;
		delete monAct_;
	}

private:
	class StatComponent* monStat_;
	std::string name_ = "mob5";
	bool bIsBoss_ = false;
};

