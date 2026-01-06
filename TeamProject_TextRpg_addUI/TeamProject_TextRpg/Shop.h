#pragma once
#include "Item.h"
#include <vector>
#include <memory>


class Character;

// TODO: [UI] UIManager 전방 선언
class UIManager;

class Shop
{
public:
    Shop() : bIsExit_(false) {};

    // TODO: 기존 runshop 주석처리
    // void RunShop(Character* Player);
    
    // TODO: [UI] UIManager 포인터 추가
    void RunShop(Character* player, UIManager* ui);

    void Initialize();
    void ShowItemList();
    void SellItem(class Character* Player);
    void BuyItem(class Character* Player);

    // TODO: [UI] UI 전용 구매 메뉴 함수 선언
    void BuyMenu(Character* player, UIManager* ui);

    

private:
    std::vector<std::unique_ptr<Item>> Product_;
    bool bIsExit_;
};

