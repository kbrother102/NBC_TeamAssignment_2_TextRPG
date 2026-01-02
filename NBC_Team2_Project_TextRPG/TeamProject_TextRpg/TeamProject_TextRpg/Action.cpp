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
	Logger::Add(LogType::COMBAT, target->GetName() + "의 남은 체력 : " + std::to_string(target->GetStatComponent()->GetHp()));
    
    
}


//아이템 획득.
void Action::RandUseItem()
{
    
    Character* player = dynamic_cast<Character*>(owner_);
	//플레이어가 아니면 종료
    if (!player)
    {
        return;
    }
    // 인벤토리 없으면 종료
    /*Inventory* inventory = player->GetInventory();
    if(inventory == nullptr)
    {
        return;
	}
    */
	//아이템 개수가 0인지 체크
    //if (inventory->GetItemCount() == 0)   
    // {
    //      return;
    // }
	//TODO: 30% 확률로 아이템 사용한 뒤 로그 출력
	//0~99까지 일정한 확률 랜덤 생성
    int r = Random::GetRandInt(0, 99);
    if (r < 30)
    {

        //인벤토리에서 0~에서 인벤토리 사이즈만큼의 랜덤을 돌려 아이템 선택;
       //TODO :int random = Random::GetRandInt(0, inventory->>GetItemCount());
        //아이템을 랜덤으로 선택한것을 저장.
       /*TODO Item* item = inventory->GetItemAt(random);

        if(!item)
        {
            return;
		}
        if(owner_->GetStatComponent()->GetMaxHp() == owner_->GetStatComponent()->GetHp() && item->ItemType() == "HealthPotion")
        {
            return;
		}
        inventory->UseItem(random, *owner_->GetStatComponent());*/



        /*로그 아이템을 사용했다 구현
        if (item->ItemType() == "HealthPotion")
        {
			Logger::Add(LogType::INFO, "체력이 회복되었다!" );
			Logger::Add(LogType::INFO, std::to_string(owner_->GetStatComponent()->GetMaxHp() +" : " + std::to_string(owner_->GetStatComponent()->GetHp()));
        }
        if (item->ItemType() == "AttackBoost")
        {
		   Logger::Add(LogType::INFO, "공격력" +item->미정()  + "이 상승했다!" );
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
    Logger::Add(LogType::INFO, owner_->GetName() + "튜터님의 과제를 완료했다.");
}





