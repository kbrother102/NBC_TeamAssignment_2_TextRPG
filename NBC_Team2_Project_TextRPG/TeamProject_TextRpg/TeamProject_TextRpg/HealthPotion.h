#pragma once
#include "Item.h"

class HealthPotion :
    public Item
{
public:
    HealthPotion();
    void Use(StatComponent& stats) override;
};