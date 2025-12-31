#include "Action.h"
#include "Character.h"
#include "Monster.h"
#include "Item.h"
#include "Inventory.h"
#include "string"

//공격. TODO : 공격자 매개변수, 타겟 매개변수
void Action::Attack(mosnter player)
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



void Action::UseItem(Item* Item, Character* character)
{
    //TODO :  '아이템'의 Use 기능('누군가'에게 사용)을 사용한다
}



    



//아이템 획득.

    // 인벤토리에 아이템 추가.
	//inventory->AddItem(item);

