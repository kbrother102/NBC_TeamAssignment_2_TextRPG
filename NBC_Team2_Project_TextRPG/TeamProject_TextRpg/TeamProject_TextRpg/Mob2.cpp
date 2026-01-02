#include "Mob2.h"
#include "Random.h"

void BongJaeKong::SpawnMob(int level)
{
	// 몬스터가 살아있는지 체크
	if (monStat_->GetIsDead() == true)
	{
		if (level > 9 && bIsBoss_ == true)
		{
			//보스 몬스터 모자를 벗은 봉재튜터님
			name_ = "모자를 벗은 봉재튜터님";
			monStat_->SetType("Boss");
			monStat_->SetHp(level * Random::GetRandInt(50, 70));
			monStat_->SetAttack(level * Random::GetRandInt(8, 15));
			monStat_->SetGold(9999);
			monStat_->SetExp(9999);
			monStat_->SetIsDead(false);
			bIsBoss_ = true;
		}
		else
		{
			//일반몬스터 일반 봉재튜터님
			//전달받은 캐릭터의 레벨에따라 범위안에 능력치 랜덤부여
			name_ = "봉재튜터님";
			monStat_->SetType("Monster");
			monStat_->SetHp(level * Random::GetRandInt(40, 50));
			monStat_->SetAttack(level * Random::GetRandInt(5, 10));
			monStat_->SetGold(Random::GetRandInt(10, 20));
			monStat_->SetExp(50);
			monStat_->SetIsDead(false);
			bIsBoss_ = true;
		}
	}
	else return;
}

void BongJaeKong::UseSkill()
{

}

void BongJaeKong::TakeDamage(int dmg)
{
	monStat_->SetHp(monStat_->GetHp() - dmg);
	if (monStat_->GetHp() <= 0)
		monStat_->SetIsDead(true);
}