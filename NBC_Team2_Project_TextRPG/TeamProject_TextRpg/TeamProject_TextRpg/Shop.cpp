#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Logger.h"
#include "Console.h"
#include "Character.h"
#include "Inventory.h"
#include "StatComponent.h"

void Shop::Initialize()
{
    bIsExit_ = false;
    Product_.resize(2);
    Product_[0] = std::make_unique<class HealthPotion>();
    Product_[1] = std::make_unique<class AttackBoost>();
}

void Shop::ShowItemList()
{
    Logger::Add("============================");
    Logger::Add("물품 목록");


    if (Product_[0] == nullptr)
        Logger::Add("1. 품절 되었습니다.");
    else
        Logger::Add("1. 힐링포션");

    if (Product_[1] == nullptr)
        Logger::Add("2. 품절 되었습니다.");
    else
        Logger::Add("2. 공격력증가물약");
    Logger::Add("3. 판매");
    Logger::Add("4. 나가기");
    Logger::Add("=============================");



}

void Shop::SellItem(Character* Player)
{
    //TODO : 인벤토리의 내용물 출력
    int select = 0;

    if (Player->GetInventory()->GetItemCount() == 0)
    {
        Logger::Add("아무것도 없습니다.");
        return;
    }
    Logger::Add("아이템 목록");
    for (int i = 0; i < Player->GetInventory()->GetItemCount();i++)
    {
        const Item* PlayerItem = Player->GetInventory()->GetItem(i);
        if (PlayerItem != nullptr)
        {
            Logger::Add(std::to_string(i + 1) + "번칸 : " + PlayerItem->GetName());
        }
        else if (PlayerItem == nullptr)
        {
            Logger::Add(std::to_string(i + 1) + "번칸 : 비어있습니다.");
        }

    }
    Logger::Add("판매할 품목을 골라주세요.");
    Console::Input(select);
    select--;
    if (Player->GetInventory()->GetItem(select) != nullptr)
    {
        const Item* SelectItem = Player->GetInventory()->GetItem(select);

        //TODO ::ChangeGold 나오면 주석해제  / 지금 내장꺼내쓰는거라 나중에수정할수도
        Player->GetStatComponent()->ChangeGold(Player->GetInventory()->GetItem(select)->GetPrice());


        Logger::Add("아이템" + SelectItem->GetName() + "을 판매하고" + std::to_string(SelectItem->GetPrice()) + "를 얻었습니다.");
        // TODO : 아이템 변경 함수 필요 - 인벤토리에서 하던가 플레이어에게 요청 
        //Player->GetInventory()->GetItem(select) = nullptr;


    }
    else
    {
        Logger::Add(WARNING, "아이템이 존재하지 않습니다.");
    }

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
            if (Player->GetGold() >= Product_[0].get()->GetPrice())
            {
                
                Player->ChangeGold(-(Product_[0].get()->GetPrice()));
                Player->GetInventory()->AddItem(move(Product_[0]));
                Product_[0] = nullptr;
            }
            else
            {
                Logger::Add(LogType::WARNING, "돈이 부족합니다.");
            }
        }
        else
        {
            Logger::Add(LogType::WARNING, "품절 되었습니다!");
        }
        break;
    case 2:
        if (Product_[1] != nullptr)
        {
            if (Player->GetGold() >= Product_[1].get()->GetPrice())
            {
                
                Player->ChangeGold(-(Product_[1].get()->GetPrice()));
                Player->GetInventory()->AddItem(move(Product_[1]));
                Product_[1] = nullptr;
            }
            else
            {
                Logger::Add(LogType::WARNING, "돈이 부족합니다.");
            }
        }
        else
        {
            Logger::Add(LogType::WARNING, "품절 되었습니다!");
        }
        break;
    case 3:
        SellItem(Player);
        break;
    case 4:
        bIsExit_ = true;
        break;
    }
}


void Shop::RunShop(Character* Player)
{
    int select = 0;
    Initialize();

    while (!bIsExit_)
    {
        ShowItemList();
        BuyItem(Player);
    }

}