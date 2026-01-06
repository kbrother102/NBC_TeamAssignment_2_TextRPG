#pragma once
#include "Item.h"

class AttackBoost : public Item
{
public:
    AttackBoost() : Item("핫식스", 30) {}

    bool Use(StatComponent& stats) override;
};