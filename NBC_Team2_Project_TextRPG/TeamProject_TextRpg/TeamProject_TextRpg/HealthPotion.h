#pragma once
#include "Item.h"

class HealthPotion :
    public Item
{
public:
    HealthPotion() : Item("회복 포션", 18) {}
    bool Use(StatComponent& stats) override;
};