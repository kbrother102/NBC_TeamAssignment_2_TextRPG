#include "Action.h"
#include "Monster.h"
#include "Character.h"
#include "Item.h"
#include "Inventory.h"
#include "string"

//공격.
void Action::Attack()
{
    // 몬스터가 타깃일 때
    if (monster)         
    {
        //monster->TakeDamage(dmg);
    }
    // 캐릭터가 타깃일 때
    else if (character)   
    {
        //character->TakeDamage(dmg); 
    }
    // 타깃 없음
    else
    {
        return; 
    }
    //로그 공격했다 구현
    //Log();
}


//아이템 획득.
void Action::PickUpItem(Item* item)
{
    // 인벤토리에 아이템 추가.
	//inventory->AddItem(item);
}
