#include "Action.h"
#include "Monster.h"
#include "Character.h"
#include "Item.h"
#include "Creature.h"
#include "Inventory.h"
#include <string>
#include <random>


//공격.
void Action::Attack()
{
    // 몬스터가 타깃일 때
    //if (monster)
    //{
        //monster->TakeDamage(dmg);
    //}
    // 캐릭터가 타깃일 때
    //else if (character)
    //{
        //character->TakeDamage(dmg);
    //}
    // 타깃 없음
    //else
    //{
        //return;
    //}
    //로그 공격했다 구현
    //Log();
}


//아이템 획득.
void Action::RandUseItem(Item* item, Inventory* inventory)
{
    std::uniform_int_distribution<int> dist(0, 99);
    std::default_random_engine engine((unsigned int)time(nullptr));
    int r = dist(engine);
    //인벤토리에 있는 아이템 사용
    if (inventory && item)
    {
        //30% 확률로 아이템 사용,로그 구현;
        if (r < 30)
        {
            //inventory->UseItem(item);
            //Log();
        }
    }
}



//아이템 획득.

void Action::AddItem(Item* item)
{
    // 인벤토리에 아이템 추가.
  //inventory->AddItem(item);
}

void Action::TakeDamage(int dmg)
{

}
