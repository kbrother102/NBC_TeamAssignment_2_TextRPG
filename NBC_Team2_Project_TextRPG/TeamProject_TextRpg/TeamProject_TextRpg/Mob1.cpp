#include "Mob1.h"
#include "Random.h"

void ChangMinKong::SpawnMob(int level)
{
	// 몬스터가 살아있는지 체크
	if (monStat_->GetIsDead() == true)
	{
		if (level > 9 && bIsBoss_ == true)
		{
			//보스 몬스터 카페인충전한 창민튜터님
			name_ = "카페인충전한 키부츠지 창민튜터님";
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
			//일반몬스터 일반 창민튜터님
			//전달받은 캐릭터의 레벨에따라 범위안에 능력치 랜덤부여
			name_ = "창민튜터님";
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

void ChangMinKong::UseSkill()
{
	//Logger::Add(LogType::Battle, "아 배고파서 잠시 삶은달걀 먹방을 좀 해보겠습니다~");
	
}

void ChangMinKong::TakeDamage(int dmg)
{
	monStat_->SetHp(monStat_->GetHp() - dmg);
	if (monStat_->GetHp() <= 0)
	{
		monStat_->SetIsDead(true);
		monAct_->Die();
	}
	else return;
}