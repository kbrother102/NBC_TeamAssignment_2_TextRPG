#include "Action.h"
#include "Monster.h"
#include "Character.h"
#include "Item.h"
#include "Creature.h"
#include "Inventory.h"
#include <string>
//#include "Random.h"


//공격.
void Action::Attack(Creature* target)
{
    //없으면 종료
    //if(owner_ == nullptr)
  //{
  //    return;
  //}
   
    // 
	//타겟의 체력에서 공격자의 공격력만큼 차감
	//taget->TakeDamage(owner_->GetDamage());
    
	

   
    //로그 공격했다 구현
    //Log();

    //std::cout << owner_->GetName() << "가 " << target->GetName() << "을(를) 공격했다!" << std::endl;
    //std::cout << "데미지 : " << owner_->GetDamage() << std::endl; 

}


//아이템 획득.
void Action::RandUseItem(Item* item, Inventory* inventory)
{
    //int r = GetRandInt(0, 99);
	
    //인벤토리에 없고 인벤 사이즈가 0이면 종료
//if (!inventory || inventory->GetSize() == 0)
// {
  //   return;
// }

    //30% 확률로 아이템 사용
    //if (r < 30)
    //{

   //인벤토리에서 랜덤으로 아이템 선택
   //int random=GetRandInt(0, inventory->GetSize()-1);
   //item = inventory->GetItemAt(random);
   // 후 사용
   // item->UseItem(owner_);  
   // 인벤토리에서 아이템 제거
   // inventory->RemoveItem(item);
   //
 
   //로그 아이템을 사용했다 구현
   //Log();
   // std::cout << owner_->GetName() << "가 " << item->GetName() << "을(를) 사용했다!" << std::endl;
   // if(item->GetName() == "HpPotion")
   // {
   //   std::cout << "체력이 회복되었다!" << std::endl;
   // }
   // if(item->GetName() == "AttackPotion")
   // {
   //   std::cout << "공격력이 상승했다!" << std::endl;
   // }
        
    //}
   
}






void Action::TakeDamage(int dmage)
{
	//없으면 종료
    //if(owner_ == nullptr)
    //{
    //    return;
	//}
    // //데미지가 실제로 들어가는 부분
	//  owner_->SetHp(owner_->GetHp() - damage);
	//if (owner_->GetHp() <= 0)
    // {
	//  owner_->SetHp(0);
    // };
}
