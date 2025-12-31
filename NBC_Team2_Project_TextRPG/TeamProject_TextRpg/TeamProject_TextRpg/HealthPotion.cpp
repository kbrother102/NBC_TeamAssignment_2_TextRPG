#include "HealthPotion.h"
#include "StatComponent.h"

HealthPotion::HealthPotion() : Item("체력 포션", 18) {}

//회복 포션 사용 설정 - 스텟에서 회복 관련 함수 필요
//void HealthPotion::Use(StatComponent* stats)
//{	//효과 부여
//	stats.Heal(50);
//}