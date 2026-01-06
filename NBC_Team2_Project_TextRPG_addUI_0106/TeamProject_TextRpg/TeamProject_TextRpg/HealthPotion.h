#pragma once
#include "Item.h"

class HealthPotion :
    public Item
{
public:
    HealthPotion() : Item("홍삼 스틱", 18) {}
    bool Use(StatComponent& stats) override;
};