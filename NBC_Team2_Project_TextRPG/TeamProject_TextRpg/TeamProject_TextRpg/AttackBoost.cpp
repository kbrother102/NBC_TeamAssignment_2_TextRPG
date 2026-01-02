#include "AttackBoost.h"
#include "StatComponent.h"

bool AttackBoost::Use(StatComponent& stats)
{
    // 공격력 +10 (전투 동안 유지)
    //stats.ApplyAttackBoost(10);
    return true;
}