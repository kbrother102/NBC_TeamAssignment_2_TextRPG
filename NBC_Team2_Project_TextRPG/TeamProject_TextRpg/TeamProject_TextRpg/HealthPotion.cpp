#include "HealthPotion.h"
#include "StatComponent.h"

bool HealthPotion::Use(StatComponent& stats)
{	//AddHp 생성 필요함
	//stats.AddHp(50);
	//return true;
}

//회복 포션 사용 설정 - 스텟에서 회복 관련 함수 필요
//void HealthPotion::Use(StatComponent* stats)
//{	//효과 부여
//	stats.Heal(50);
//}