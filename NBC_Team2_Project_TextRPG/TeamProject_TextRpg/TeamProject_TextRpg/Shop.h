#pragma once
#include "Item.h"
#include <vector>
#include <memory>


class Character;

class Shop
{
public:
    Shop() : bIsExit_(false) {};

    void RunShop(Character* Player);
    void Initialize();
    void ShowItemList();
    void SellItem(class Character* Player);
    void BuyItem(class Character* Player);

    

private:
    std::vector<std::unique_ptr<Item>> Product_;
    bool bIsExit_;
};

