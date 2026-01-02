#pragma once
#include "Item.h"

class AttackBoost : public Item
{
public:
    AttackBoost() : Item("공격력 증폭제", 30) {}

    bool Use(StatComponent& stats) override;
};