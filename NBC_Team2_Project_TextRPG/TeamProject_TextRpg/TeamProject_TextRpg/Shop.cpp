#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Logger.h"
#include "Console.h"
#include "Character.h"
#include "Inventory.h"

void Shop::Initialize()
{
    
    Product_[0] = std::make_unique<class HealthPotion>();
    Product_[1] = std::make_unique<class AttackBoost>();
}

void Shop::ShowItemList()
{
    Logger::Add("============================");
    Logger::Add("물품 목록");
    
    Logger::Add("1. 힐링포션");
    if (Product_[0] == nullptr)
        Logger::Add("ㄴ 품절 되었습니다.");
    Logger::Add("2. 공격력증가물약");
    if (Product_[1] == nullptr)
        Logger::Add("ㄴ 품절 되었습니다.");
    Logger::Add("3. 판매");
    Logger::Add("4. 나가기");
    Logger::Add("=============================");
    

   
}

void Shop::SellItem(Character* Player)
{
    //TODO : 인벤토리의 내용물 출력
}

void Shop::BuyItem(Character* Player)
{
    int select = 0;
    Console::Input(select);
    switch (select)
    {
    case 1:
        if (Product_[0] != nullptr)
        {
            Player->GetInventory()->AddItem(move(Product_[0]));
            Product_[0] = nullptr;
        }
        else
        {
            Logger::Add(LogType::WARNING, "품절 되었습니다!");
        }
        break;
    case 2:
        if (Product_[1] != nullptr)
        {
            Player->GetInventory()->AddItem(move(Product_[1]));
            Product_[1] = nullptr;
        }
        else
        {
            Logger::Add(LogType::WARNING, "품절 되었습니다!");
        }
        break;
     case 3:
         SellItem(Player);
         break;
         
    }
}


void Shop::RunShop(Character* Player)
{
    int select = 0;
    Initialize();
    
    ShowItemList();
    BuyItem(Player);
    

}