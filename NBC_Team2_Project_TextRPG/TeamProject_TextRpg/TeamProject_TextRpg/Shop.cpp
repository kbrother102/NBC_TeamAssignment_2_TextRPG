#include "Shop.h"
#include "HealthPotion.h"
#include "Logger.h"
#include "Console.h"
#include "Character.h"
void Shop::Initialize()
{
    
    Product_[0] = std::make_unique<class HealthPotion>();
    //Product_[1] = std::make_unique<class AttackBoost>();
}

void Shop::ShowItemList()
{
    Logger::Add("============================");
    Logger::Add("물품 목록");
    Logger::Add("1. 힐링포션");
    Logger::Add("2. 공격력증가물약");
    Logger::Add("3. 판매");
    Logger::Add("4. 나가기");
    Logger::Add("=============================");
   
}

void Shop::SellItem(Character* Player)
{
    int select = 0;
    Console::Input(select);
    switch (select)
    {
    case 1 :
        if (Product_ != nullptr)
        {
            //TODO :GetInVectory() 생기면 해제
            //Player->GetInvectory()->AddItem(move(Product_[0]));
            Product_[0] = nullptr;
        }
        else
        {
            
        }
    }
}

void Shop::BuyItem(Character* Player)
{
}


void Shop::RunShop()
{
    int select = 0;
    Initialize();
    ShowItemList();
    BuyItem();
    

}