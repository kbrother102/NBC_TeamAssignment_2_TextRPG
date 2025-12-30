#pragma once
#include "Item.h"

class HealthPotion :
    public Item
{

    std::string GetName() override;
    void Use(class Character* character) override;
private:
    std::string Name_;
    int healthRestore_;
    //TODO : 변수 초기화하기
};

