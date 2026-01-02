#include "Mob2.h"
#include "Random.h"

void BongJaeKong::SpawnMob(int level)
{
	// 몬스터가 살아있는지 체크
	if (monasterStat_->GetIsDead() == true)
	{
		if (level > 9 && bIsBoss_ == true)
		{
			//보스 몬스터 모자를 벗은 봉재튜터님
			name_ = "모자를 벗은 봉재튜터님";
			monasterStat_->SetType("Boss");
			monasterStat_->SetHp(level * Random::GetRandInt(30, 45));
			monasterStat_->SetAttack(level * Random::GetRandInt(8, 15));
			monasterStat_->SetGold(9999);
			monasterStat_->SetExp(9999);
			monasterStat_->SetIsDead(false);
			bIsBoss_ = true;
		}
		else
		{
			//일반몬스터 일반 봉재튜터님
			//전달받은 캐릭터의 레벨에따라 범위안에 능력치 랜덤부여
			name_ = "봉재튜터님";
			monasterStat_->SetType("Monster");
			monasterStat_->SetHp(level * Random::GetRandInt(20, 30));
			monasterStat_->SetAttack(level * Random::GetRandInt(5, 10));
			monasterStat_->SetGold(Random::GetRandInt(10, 20));
			monasterStat_->SetExp(50);
			monasterStat_->SetIsDead(false);
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
	monasterStat_->SetHp(monasterStat_->GetHp() - dmg);
	if (monasterStat_->GetHp() <= 0)
		monasterStat_->SetIsDead(true);
}