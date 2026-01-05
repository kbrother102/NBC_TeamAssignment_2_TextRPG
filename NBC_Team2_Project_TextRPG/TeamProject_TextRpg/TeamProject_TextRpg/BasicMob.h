#pragma once
#include "Monster.h"

enum class TuterName
{
	SEUNGHYEONSUN,
	GEUKMINKONG,
	EUNILPERK,
	CHANGMINKONG,
	BONGJAEKONG,
	JOEUNKONG,
	HOYOUNGJOU
};

class BasicMob : public Monster
{
public:
	BasicMob()
	{
		monStat_->SetIsDead(true);
		bIsBoss_ = false;
	}
	~BasicMob() override {}
	//override
	void SpawnMob(int Level);
	void TakeDamage(int dmg);
	void UseSkill();

	//getter
	bool GetIsDead() const { return monStat_->GetIsDead(); }
	int GetDamage() const { return monStat_->GetAttack(); }
	std::string GetName() const { return name_; }
	std::string GetType() { return monStat_->GetType(); }

	//memberFunc
	void SetStat(int Level);
	void SetStatBoss(int Level);
	void SetStatHoYoung(int Level);
	void SetStatHoYoungBoss(int Level);

	class StatComponent* GetStatComponent() { return monStat_; }
	//class Action* GetActionComponent() { return monAct_; }

protected:
	std::string name_;
	bool bIsBoss_;
};

