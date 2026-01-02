#pragma once
#include "Item.h"
#include <vector>
#include <memory>

class Shop
{
public:
    Shop() {};

    void RunShop();
    void Initialize();
    void ShowItemList();
    void SellItem(class Character* Player);
    void BuyItem(class Character* Player);

    

private:
    std::vector<std::unique_ptr<Item>> Product_;
};

