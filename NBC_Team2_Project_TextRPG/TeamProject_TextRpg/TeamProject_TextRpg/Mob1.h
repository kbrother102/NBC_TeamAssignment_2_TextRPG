#pragma once
#include "Monster.h"
#include "Action.h"
#include "StatComponent.h"


class ChangMinKong : public Monster
{
public:

	ChangMinKong()
	{
		monStat_ = new StatComponent();
		monAct_ = new Action();
	}

	//몬스터 고유 함수
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

	~ChangMinKong()
	{
		//소멸자
		delete monStat_;
		delete monAct_;
	}

private:
	//TODO : 공통된 변수 몬스터(Monster.h)에 넣기
	std::string name_ = "mob1";
	bool bIsBoss_ = false;
};

