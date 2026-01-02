#include "Mob1.h"
#include "Random.h"

void ChangMinKong::SpawnMob(int level)
{
	// 몬스터가 살아있는지 체크
	if (bIsAlive_ == false)
	{
		if (level > 9 && bIsBoss_ == false)
		{
			//보스 몬스터 카페인충전한 창민튜터님
			health_ = (level * Random::GetRandInt(30, 45));
			attack_ = (level * Random::GetRandInt(8, 15));
			bIsAlive_ = true;
			bIsBoss_ = true;
		}
		else
		{
			//전달받은 캐릭터의 레벨에따라 범위안에 능력치 랜덤부여
			health_ = (level * Random::GetRandInt(20,30));
			attack_ = (level * Random::GetRandInt(5,10));
			bIsAlive_ = true;
			bIsBoss_ = false;
		}
	}
	else return;
}

void ChangMinKong::DieMob()
{

	if (bIsAlive_ == true)
	{
		bIsAlive_ = false;
		//몬스터처치 메세지 출력
	}
	else return;
}

void ChangMinKong::TakeDamage(int dmg)
{
	health_ -= dmg;
	if (health_ <= 0);
}