#include "BasicMob.h"
#include "Logger.h"
#include "Random.h"

void BasicMob::SpawnMob(int Level)
{
	int num = Random::GetRandInt(0, 6);
	if ((monStat_->GetIsDead() == true))
	{
		switch ((TuterName)num)
		{
		case TuterName::SEUNGHYEONSUN:
			if (Level > 9)
			{
				SetStatBoss(Level);
				name_ = "마이크가 불안정한 승현튜터님";
				bIsBoss_ = true;
			}
			else
			{
				SetStat(Level);
				name_ = "포인터 강의해주시는 승현튜터님";
			}
			break;
		case TuterName::GEUKMINKONG:
			if (Level > 9)
			{
				SetStatBoss(Level);
				name_ = "코드리뷰를 시작한 극민튜터님";
				bIsBoss_ = true;
			}
			else
			{
				SetStat(Level);
				name_ = "튜터링 해주시는 극민튜터님";
			}
			break;
		case TuterName::EUNILPERK:
			if (Level > 9)
			{
				SetStatBoss(Level);
				name_ = "기대를 안하는 은일튜터님";
				bIsBoss_ = true;
			}
			else
			{
				SetStat(Level);
				name_ = "공룡을 탄 은일튜터님";
			}
			break;
		case TuterName::CHANGMINKONG:
			if (Level > 9)
			{
				SetStatBoss(Level);
				name_ = "카페인충전한 창민튜터님";
				bIsBoss_ = true;
			}
			else
			{
				SetStat(Level);
				name_ = "삶은계란 먹방중인 창민튜터님";
			}
			break;
		case TuterName::BONGJAEKONG:
			if (Level > 9)
			{
				SetStatBoss(Level);
				name_ = "모자를 벗은 봉재튜터님";
				bIsBoss_ = true;
			}
			else
			{
				SetStat(Level);
				name_ = "모자를 쓴 봉재튜터님";
			}
			break;
		case TuterName::JOEUNKONG:
			if (Level > 9)
			{
				SetStatBoss(Level);
				name_ = "팔당으로 점프하신 조은튜터님";
				bIsBoss_ = true;
			}
			else
			{
				SetStat(Level);
				name_ = "가상배경의 조은튜터님";
			}
			break;

		case TuterName::HOYOUNGJOU:
			if (Level > 9)
			{
				SetStatHoYoung(Level);
				name_ = "풀무장한 호영튜터님";
				bIsBoss_ = true;
			}
			else
			{
				SetStatHoYoungBoss(Level);
				name_ = "새천년 건강체조를 시작한 호영튜터님";
			}
			break;
		}
	}
	else
	{
		Logger::Add(LogType::WARNING, "Monster Has Already Spawn.");
		return;
	}
}

void BasicMob::UseSkill()
{

}

void BasicMob::SetStat(int Level)
{
	monStat_->SetMaxHp(Level * Random::GetRandInt(20, 30));
	monStat_->SetAttack(Level * Random::GetRandInt(5, 10));
	monStat_->SetHp(monStat_->GetMaxHp());
	monStat_->SetIsDead(false);
	monStat_->SetType("Monster");
	monStat_->SetLevel(Level);
	monStat_->SetExp(50);
	monStat_->SetGold(Random::GetRandInt(10, 20));
}

void BasicMob::SetStatBoss(int Level)
{
	monStat_->SetMaxHp(Level * Random::GetRandInt(60, 90));
	monStat_->SetAttack(Level * Random::GetRandInt(15, 30));
	monStat_->SetHp(monStat_->GetMaxHp());
	monStat_->SetIsDead(false);
	monStat_->SetType("Boss");
	monStat_->SetLevel(Level);
	monStat_->SetExp(2026);
	monStat_->SetGold(2026);
}

void BasicMob::SetStatHoYoung(int Level)
{
	monStat_->SetMaxHp(Level * Random::GetRandInt(40, 60));
	monStat_->SetAttack(Level * Random::GetRandInt(10, 20));
	monStat_->SetHp(monStat_->GetMaxHp());
	monStat_->SetIsDead(false);
	monStat_->SetType("SpacialMob");
	monStat_->SetLevel(Level + 10);
	monStat_->SetExp(250);
	monStat_->SetGold(Random::GetRandInt(50, 100));
}

void BasicMob::SetStatHoYoungBoss(int Level)
{
	monStat_->SetMaxHp(Level * Random::GetRandInt(100, 150));
	monStat_->SetAttack(Level * Random::GetRandInt(25, 50));
	monStat_->SetHp(monStat_->GetMaxHp());
	monStat_->SetIsDead(false);
	monStat_->SetType("SpacialBoss");
	monStat_->SetLevel(Level + 999);
	monStat_->SetExp(9999);
	monStat_->SetGold(9999);
}

void BasicMob::TakeDamage(int dmg)
{
	monStat_->SetHp(monStat_->GetHp() - dmg);
	if (monStat_->GetHp() <= 0)
	{
		monStat_->SetIsDead(true);
	}
	else return;
}