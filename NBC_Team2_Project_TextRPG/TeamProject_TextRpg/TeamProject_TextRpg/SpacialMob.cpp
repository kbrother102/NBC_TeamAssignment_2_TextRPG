#include "SpacialMob.h"
#include "Random.h"
#include "Logger.h"

void HoYeongJou::SpawnMob(int level)
{
	// 몬스터가 살아있는지 체크
	if (monasterStat_->GetIsDead() == true)
	{
		if (level > 9 && bIsBoss_ == true)
		{
			//보스 몬스터 특수객체 풀무장한 호영튜터님
			name_ = "풀무장한 호영튜터님";
			monasterStat_->SetType("SpacialBoss");
			monasterStat_->SetHp(level * Random::GetRandInt(40, 60));
			monasterStat_->SetAttack(level * Random::GetRandInt(10, 20));
			monasterStat_->SetGold(11111);
			monasterStat_->SetExp(11111);
			monasterStat_->SetIsDead(false);
			bIsBoss_ = true;
			Logger::Add(LogType::WARNING, "자자 여러분 화이팅 여러분은 할 수 있습니다!!");
		}
		else
		{
			//일반몬스터 특수객체 호영튜터님
			//전달받은 캐릭터의 레벨에따라 범위안에 능력치 랜덤부여
			name_ = "호영튜터님";
			monasterStat_->SetType("SpacialMob");
			monasterStat_->SetHp(level * Random::GetRandInt(30, 45));
			monasterStat_->SetAttack(level * Random::GetRandInt(7, 17));
			monasterStat_->SetGold(Random::GetRandInt(50, 100));
			monasterStat_->SetExp(200);
			monasterStat_->SetIsDead(false);
			bIsBoss_ = true;
			Logger::Add(LogType::WARNING, "안녕하세요 여러분 조호영튜텁니다!!!");
		}
	}
	else return;
}

void HoYeongJou::UseSkill()
{

}

void HoYeongJou::TakeDamage(int dmg)
{
	monasterStat_->SetHp(monasterStat_->GetHp() - dmg);
	if (monasterStat_->GetHp() <= 0)
		monasterStat_->SetIsDead(true);
}