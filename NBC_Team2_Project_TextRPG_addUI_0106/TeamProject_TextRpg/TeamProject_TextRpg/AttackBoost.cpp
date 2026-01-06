#include "AttackBoost.h"
#include "StatComponent.h"

bool AttackBoost::Use(StatComponent& stats)
{
	// 공격력 +10 (전투 동안 유지[희망사항])
	int currentAttack = stats.GetAttack();
	int addAttack = 10;
	stats.SetAttack(currentAttack + addAttack);
	return true;
}