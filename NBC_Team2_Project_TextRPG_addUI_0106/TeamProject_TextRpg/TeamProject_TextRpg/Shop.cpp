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
        Logger::Add("1. 홍삼 스틱 " + std::to_string(Product_[0]->GetPrice()) + "Point");
    }

    if (Product_[1] == nullptr)
    {
        Logger::Add("2. 품절 되었습니다.");
    }
    else
    {
        Logger::Add("2. 핫식스 "+ std::to_string(Product_[1]->GetPrice()) + "Point");
    }
    Logger::Add("3. 판매");
    Logger::Add("4. 나가기");
    Logger::Add("=============================");



}

// TODO: 기존 sellitem 주석처리 / ui출력으로 변경
/* 
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
*/
// =================================================

// TODO : 기존 buyitem 주석처리 / ui출력으로 변경
/*
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
                Logger::Add(LogType::WARNING, "포인트가 부족합니다.");
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
                Logger::Add(LogType::WARNING, "포인트가 부족합니다.");
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
*/
// =================================================

// TODO: 기존 runshop 주석처리 / ui출력으로 변경
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
// =================================================


// TODO:  [UI] 기존 로그출력에서 - UI 매니저 출력으로 변경함 / run, sell, buy
void Shop::RunShop(Character* player, UIManager* ui)
{
    // 상점 시작 시 물건 목록 초기화
    Initialize();

    while (true)
    {
        // 1. 화면 갱신
        ui->RenderShopMenu();
        Logger::Add(LogType::INFO, "어서오세요! 무엇을 도와드릴까요?");
        ui->RenderLogs();

        // 2. 입력 받기
        std::string input = ui->InputString("선택하세요: ");

        // 엔터만 쳤을 경우 무시
        if (input.empty()) continue;

        int choice = 0;

        // =========================================================
        // [핵심 수정] try-catch로 감싸서 프로그램 터짐 방지
        // =========================================================
        try
        {
            choice = std::stoi(input); // 여기서 문자가 들어오면 에러를 던짐 -> catch로 이동
        }
        catch (...) // 어떤 에러가 나더라도 여기로 옴
        {
            Logger::Add(LogType::WARNING, "숫자만 입력해 주세요!");
            continue; // 루프의 처음(화면 갱신)으로 돌아감
        }
        // =========================================================

        if (choice == 1)
        {
            BuyItem(player, ui);
        }
        else if (choice == 2)
        {
            SellItem(player, ui);
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

void Shop::SellItem(Character* player, UIManager* ui)
{
    while (true)
    {
        Inventory* inv = player->GetInventory();
        int invSize = inv->GetItemCount(); // items_ 벡터의 전체 크기

        std::vector<std::string> displayList;
        bool bHasAnyItem = false;

        // 1. 인벤토리 전체 순회 (동적 목록 생성)
        for (int i = 0; i < invSize; ++i)
        {
            const Item* item = inv->GetItem(i);

            if (item != nullptr)
            {
                bHasAnyItem = true;
                // 가격의 60% 계산
                int sellPrice = static_cast<int>(item->GetPrice() * 0.6f);

                // [형식] 1. 홍삼 스틱 (판매가: 10G) <- 이렇게 자동으로 이름과 가격을 가져옵니다.
                std::string line = std::to_string(i + 1) + ". " + item->GetName() +
                    " (판매가: " + std::to_string(sellPrice) + " Point)";
                displayList.push_back(line);
            }
            else
            {
                // 인벤토리 중간에 구멍(nullptr)이 뚫려있을 경우 인덱스 유지를 위해 표시
                displayList.push_back(std::to_string(i + 1) + ". [ 비어있음 ]");
            }
        }

        // 인벤토리 자체가 비어있거나 모든 슬롯이 nullptr인 경우
        if (invSize == 0 || !bHasAnyItem)
        {
            if (displayList.empty()) displayList.push_back("   [ 가방이 비어있습니다 ]");
        }

        displayList.push_back(" ");
        displayList.push_back("0. 뒤로가기");

        // 2. UI 렌더링
        ui->RenderMainPanel(" SELL ITEMS ", displayList);
        Logger::Add(LogType::INFO, "판매할 아이템 번호를 입력하세요.");
        ui->RenderLogs();

        // 3. 입력
        std::string input = ui->InputString("선택: ");
        if (input.empty()) continue;

        int choice = -1;
        try { choice = std::stoi(input); }
        catch (...) { continue; }

        if (choice == 0) return; // 뒤로가기

        // 4. 판매 처리 로직
        int idx = choice - 1; // 입력값(1~N)을 인덱스(0~N-1)로 변환

        // 인덱스 유효성 검사
        if (idx >= 0 && idx < invSize)
        {
            const Item* itemToSell = inv->GetItem(idx);

            // 실제 아이템이 존재하는지 확인 (빈 슬롯 선택 방지)
            if (itemToSell != nullptr)
            {
                int price = static_cast<int>(itemToSell->GetPrice() * 0.6f);
                std::string name = itemToSell->GetName(); // 삭제 전 이름 저장

                // 골드 지급
                player->ChangeGold(price);

                // 아이템 삭제 (Inventory 클래스의 RemoveItem 호출 -> reset)
                inv->RemoveItem(idx);

                Logger::Add(LogType::INFO, name + " 판매 완료! (+" + std::to_string(price) + " Point)");
            }
            else
            {
                Logger::Add(LogType::WARNING, "빈 슬롯입니다.");
            }
        }
        else
        {
            Logger::Add(LogType::WARNING, "잘못된 번호입니다.");
        }
    }
}

void Shop::BuyItem(Character* player, UIManager* ui)
{
    while (true)
    {
        std::vector<std::string> items;

        // 상품 목록 생성
        if (Product_[0] == nullptr) items.push_back("1. [ 품절 ]");
        else items.push_back("1. " + Product_[0]->GetName() + " (" + std::to_string(Product_[0]->GetPrice()) + " Point)");

        if (Product_.size() > 1)
        { // 안전 장치
            if (Product_[1] == nullptr) items.push_back("2. [ 품절 ]");
            else items.push_back("2. " + Product_[1]->GetName() + " (" + std::to_string(Product_[1]->GetPrice()) + " Point)");
        }

        items.push_back(" ");
        items.push_back("0. 뒤로가기");

        // UI 출력
        ui->RenderMainPanel(" BUY ITEMS ", items);
        Logger::Add(LogType::INFO, "현재 포인트: " + std::to_string(player->GetGold()) + " Point");
        ui->RenderLogs();

        // 입력
        std::string input = ui->InputString("구매할 번호: ");
        if (input.empty()) continue;

        int choice = -1;
        try { choice = std::stoi(input); }
        catch (...) { continue; }

        if (choice == 0) return; // 뒤로가기

        // 인덱스 보정 (1번 선택 -> 0번 인덱스)
        int idx = choice - 1;

        if (idx >= 0 && idx < Product_.size())
        {
            if (Product_[idx] != nullptr)
            {
                int price = Product_[idx]->GetPrice();
                if (player->GetGold() >= price)
                {
                    player->ChangeGold(-price);
                    // move로 소유권 이전
                    player->GetInventory()->AddItem(std::move(Product_[idx]));
                    Product_[idx] = nullptr; // 상점에서는 제거(품절)

                    Logger::Add(LogType::REWARD, "구매 성공!");
                }
                else
                {
                    Logger::Add(LogType::WARNING, "포인트가 부족합니다.");
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
