#include "HealthPotion.h"
#include "StatComponent.h"

bool HealthPotion::Use(StatComponent& stats)
{	//체력 50 회복
    
    int currentHp = stats.GetHp();
    int healAmount = 50;

    stats.SetHp(currentHp + healAmount);
    if (stats.GetHp() > stats.GetMaxHp())
    {
        stats.SetHp(stats.GetMaxHp());
    }
    return true;
}