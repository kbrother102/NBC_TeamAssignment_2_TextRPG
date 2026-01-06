#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Logger.h"
#include "Console.h"
#include "Character.h"
#include "Inventory.h"
#include "StatComponent.h"

#include "UIManager.h" // TODO: [UI] UIManager 기능 사용을 위해 포함

#include <string>

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
    {
        Logger::Add("1. 품절 되었습니다.");
    }
    else
    {
        Logger::Add("1. 힐링포션 " + std::to_string(Product_[0]->GetPrice()) + "Point");
    }

    if (Product_[1] == nullptr)
    {
        Logger::Add("2. 품절 되었습니다.");
    }
    else
    {
        Logger::Add("2. 공격력증가물약 "+ std::to_string(Product_[1]->GetPrice()) + "Point");
    }
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
        Player->GetStatComponent()->ChangeGold((int)(SelectItem->GetPrice()*0.6));


        Logger::Add(INFO, "아이템" + SelectItem->GetName() + "을 판매하고 " + std::to_string((int)(SelectItem->GetPrice()*0.6)) + "를 얻었습니다.");
        // TODO : 아이템 변경 함수 필요 - 인벤토리에서 하던가 플레이어에게 요청 
        Player->GetInventory()->RemoveItem(select);
        


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



// TODO: 기존 runshop 주석처리
/*
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
*/


// TODO: [UI] UI 매니저용 runshoop 수정
void Shop::RunShop(Character* player, UIManager* ui)
{
    // TODO: !!!!!! [핵심 수정] 상점 시작 시 물건 목록을 초기화(생성)해야 합니다. !!!!
    // 이걸 안 하면 Product_ 벡터가 비어있어서 접근 시 오류가 납니다.
    Initialize();

    while (true)
    {
        // 1. 화면 갱신 (메인 패널에 상점 메뉴 띄우기)
        ui->RenderShopMenu();

        // (선택사항) 중앙에 상점 주인 그림 출력
        // ui->RenderMonsterArt("shopkeeper.txt"); 

        // 로그창 갱신 (안내 메시지)
        Logger::Add(LogType::INFO, "어서오세요! 무엇을 도와드릴까요?");
        ui->RenderLogs();

        // 2. 입력 받기
        std::string input = ui->InputString("선택하세요: ");
        if (input.empty()) continue;

        int choice = std::stoi(input);

        if (choice == 1)
        {
            // 구매 화면으로 이동 (여기서도 ui 사용)
            BuyMenu(player, ui);
        }
        else if (choice == 2)
        {
            // 판매 화면 (구현 필요 시 비슷한 방식으로)
            Logger::Add(LogType::INFO, "아직 준비 중입니다.");
        }
        else if (choice == 3)
        {
            Logger::Add(LogType::INFO, "안녕히 가세요.");
            break;
        }
        else
        {
            Logger::Add(LogType::WARNING, "잘못된 선택입니다.");
        }
    }
}

// TODO: [UI] UI 매니저용 buymenu 추가
void Shop::BuyMenu(Character* player, UIManager* ui)
{
    // 물품 초기화 (만약 상점 들어올 때마다 리필하고 싶다면 RunShop에서 호출)
    // Initialize(); (필요시 주석 해제)

    while (true)
    {
        // 1. 판매 목록 UI 구성
        std::vector<std::string> items;

        // (1) 힐링포션 상태 확인
        if (Product_[0] == nullptr)
            items.push_back("1. 힐링포션 [품절]");
        else
            items.push_back("1. 힐링포션 (" + std::to_string(Product_[0]->GetPrice()) + "G)");

        // (2) 공격력 물약 상태 확인
        if (Product_[1] == nullptr)
            items.push_back("2. 공격력 물약 [품절]");
        else
            items.push_back("2. 공격력 물약 (" + std::to_string(Product_[1]->GetPrice()) + "G)");

        items.push_back("3. 뒤로가기");

        // 2. 화면 그리기 (메인 패널 + 로그)
        ui->RenderMainPanel(" BUY ITEMS ", items);

        // 현재 골드 보여주기
        Logger::Add(LogType::INFO, "현재 보유 골드: " + std::to_string(player->GetGold()) + " G");
        ui->RenderLogs(); // 로그창 갱신

        // 3. 입력 받기
        std::string input = ui->InputString("구매할 번호 입력: ");
        if (input.empty()) continue;

        int choice = 0;
        try { choice = std::stoi(input); }
        catch (...) { continue; }

        if (choice == 3) break; // 뒤로가기

        // 4. 구매 로직 (기존 BuyItem 로직 이식)
        int idx = choice - 1; // 배열 인덱스는 0부터

        if (idx >= 0 && idx < 2) // 유효한 인덱스인지
        {
            if (Product_[idx] != nullptr)
            {
                int price = Product_[idx]->GetPrice();
                if (player->GetGold() >= price)
                {
                    player->ChangeGold(-price);
                    player->GetInventory()->AddItem(std::move(Product_[idx])); // 아이템 인벤토리로 이동
                    Product_[idx] = nullptr; // 상점에서는 품절 처리

                    Logger::Add(LogType::REWARD, "구매 성공!");
                }
                else
                {
                    Logger::Add(LogType::WARNING, "골드가 부족합니다.");
                }
            }
            else
            {
                Logger::Add(LogType::WARNING, "이미 품절된 상품입니다.");
            }
        }
        else
        {
            Logger::Add(LogType::WARNING, "잘못된 번호입니다.");
        }
    }
}