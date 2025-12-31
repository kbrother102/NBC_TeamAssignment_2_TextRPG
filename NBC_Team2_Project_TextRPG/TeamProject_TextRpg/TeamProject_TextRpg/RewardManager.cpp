#include "RewardManager.h"
#include "Random.h"
#include "Item.h"
#include "Creature.h"
#include "Monster.h"
#include "Character.h"

void RewardManager::ProcessReward(Monster* Monster, Character* Player)
{
    //몬스터 스탯 컴포넌트에서 경험치, 돈을 가져옴
    //GetExp() 는 몬스터의 경험치를 출력해주는 함수, component의 getexp()를 출력
    //int MonsterExp = Monster->GetExp();
   //int MOnsterGold = Monster->GetGold();
    
     
    //플레이어에게 추가
    //set함수라면
    Player->SetExp(Player->GetExp() + MonsterExp);
    //add함수라면
    Player->AddExp(MonsterExp);
    
   // set함수라면
    Player->SetGold(Player->GetGold() + MonsterGold);
    //add함수라면
    Player->AddGold(MonsterGold);

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
