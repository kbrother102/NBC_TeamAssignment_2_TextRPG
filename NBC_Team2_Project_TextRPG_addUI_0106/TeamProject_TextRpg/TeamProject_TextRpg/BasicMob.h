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
		bUseSkill_ = false;
		mobNum_ = 10;
	}
	~BasicMob() override
	{
		delete monAct_;
	}
	//--------------override-------------
	void SpawnMob(int Level);
	void TakeDamage(int dmg);
	void UseSkill();
	void GetDie();
	void PlayerKillText();


	//getter
		//string
	std::string GetName() const { return name_; }

	//int
	int GetAttack() const { return monStat_->GetAttack(); }
	int GetHealth() const { return monStat_->GetHp(); }
	
	//TODO : MaxHealth 추가
	int GetMaxHealth() const { return monStat_->GetMaxHp(); }

	int GetGold() const { return monStat_->GetGold(); }
	int GetExp() const { return monStat_->GetExp(); }




	//bool
	bool GetIsDead() const { return monStat_->GetIsDead(); }

	//component
	class StatComponent* GetStatComponent() { return monStat_; }
	class Action* GetActionComponent() { return monAct_; }

	//=========memberFunc================
	void SetStat(int Level);
	void SetStatBoss(int Level);
	void SetStatHoYoung(int Level);
	void SetStatHoYoungBoss(int Level);
	std::string GetType() { return monStat_->GetType(); }


protected:
	std::string name_;
	int mobNum_;
	bool bIsBoss_;
	bool bUseSkill_;
	Action* monAct_ = new Action(this);
};

