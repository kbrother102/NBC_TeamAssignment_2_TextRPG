#include "RewardManager.h"
#include "Random.h"
#include "Monster.h"
#include "Character.h"
#include "HealthPotion.h"
#include "Inventory.h"
#include <memory>

void RewardManager::ProcessReward(Monster* Monster, Character* Player)
{
    //몬스터 스탯 컴포넌트에서 경험치, 돈을 가져옴
    //GetExp() 는 몬스터의 경험치를 출력해주는 함수, component의 getexp()를 출력
    //int MonsterExp = Monster->GetExp();
   //int MOnsterGold = Monster->GetGold();

    //플레이어에게 추가
    Player->GainExp(Monster->GetExp());
   //TODO : Character에 GainGold 있으면 주석해제
    //Player->GainGold(Monster->GetGold())

    if (isItemDrop() == true)
    {
        int select = Random::GetRandInt(0, 1);
        ItemType ItemT = static_cast<ItemType>(select);

        switch (ItemT)
        {
        
        case ItemType::HealthPotion:
        {
            std::unique_ptr<class HealthPotion> potion = std::make_unique<class HealthPotion>();
            // TODO : GetInvetory()함수가 있으면 주석해제
            //Player->GetInventory()->AddItem(std::move(potion));
            break;
        }
        case ItemType::AttackBoost:
        {
            //TODO : AttackBoost 구현시 주석해제
            //std::unique_ptr<class AttackBoost> potion = std::make_unique<class AttackBoost>();
            // TODO : GetInvetory()함수가 있으면 주석해제
            //Player->GetInventory()->AddItem(std::move(potion));
            break;
        }
        }
        
    }

}

RewardManager& RewardManager::GetInstance()
{
    static RewardManager instance;
    return instance;
}
//사용법 RewardManager::GetInstance().ProcessReward(매개변수)
//RewardManager& RM = RewardManager::GetInstance() ; 으로 짧게 이름 바꿀수도잇음

bool RewardManager::isItemDrop()
{
    if (Random::GetRandFloat() < 0.3)
    {
        return true;
    }
 
    return false;
}
