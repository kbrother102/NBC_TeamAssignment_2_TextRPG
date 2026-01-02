#include "Action.h"
#include "Monster.h"
#include "Character.h"
#include "Item.h"
#include "Creature.h"
#include "Inventory.h"
#include "StatComponent.h"
#include "Random.h"
#include "Logger.h"
#include <string>



//공격.
void Action::Attack(Creature* target)
{
    //없으면 종료
    
    if(owner_ == nullptr || target == nullptr)
  {
      return;
  }
	//타겟의 체력에서 공격자의 공격력만큼 차감//여기 대미지 계산확실하게
	target->TakeDamage(owner_->GetStatComponent()->GetAttack());
    
    //로그 공격했다 구현
    Logger::Add(LogType::COMBAT, owner_->GetName()+ "가"+ target->GetName()+ "을(를) 공격했다!");
    Logger::Add(LogType::COMBAT, "데미지 : " + owner_->GetStatComponent()->GetAttack());
    
}


//아이템 획득.
void Action::RandUseItem(Inventory* inventory)
{
    int r = Random::GetRandInt(0, 99);

    //인벤토리에 없고 인벤 사이즈가 0이면 종료
    if (!inventory || !owner_)
    {
        return;
    }

	//TODO: 아이템 개수 체크
    //  if (inventory->GetItemCount() == 0)   return;
    //30% 확률로 아이템 사용
    if (r < 30)
    {

        //인벤토리에서 랜덤으로 아이템 선택 , 0, inventory->GetSize()-1);
       //TODO :int random = Random::GetRandInt(0, inventory.());
        //아이템을 랜덤으로 선택한것을 저장.
       /*TODO Item* item = inventory->GetItemAt(random);

        if(!item)
        {
            return;
		}
 
        inventory->UseItem(random, *owner_->GetStatComponent());*/



        /*로그 아이템을 사용했다 구현
        if (item->GetName() == "HpPotion")
        {
            std::cout << "체력이 회복되었다!" << std::endl;
        }
        if (item->GetName() == "AttackPotion")
        {
            std::cout << "공격력이 상승했다!" << std::endl;
        }
        Logger::Add(LogType::INFO, owner_->GetName() + "가 " + item->GetName() + "을(를) 사용했다!");
        */

    }
}
//죽음.
void Action::Die()
{
    //없으면 종료
    if(owner_ == nullptr)
    {
        return;
    }
    //사망.
	owner_->GetStatComponent()->SetIsDead(true);

	//로그 사망했다 구현
    Logger::Add(LogType::INFO, owner_->GetName() + "이(가) 사망했다!");
}





